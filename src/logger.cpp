/**
 * ============================================================================
 *  logger.cpp - 日志系统实现
 * ============================================================================
 */
#include "logger.h"

#include <cstdarg>
#include <cstdio>
#include <cstring>

namespace pptx_selector {

Logger::Logger() : enabled_(false) {
    file_[0] = '\0';
}

Logger::Logger(bool enableLog, const char* logFile) : enabled_(enableLog) {
    if (logFile) {
        strncpy_s(file_, logFile, _TRUNCATE);
    } else {
        file_[0] = '\0';
    }
}

void Logger::initDir() const {
    if (!enabled_ || file_[0] == '\0') return;

    char dir[MAX_PATH];
    strncpy_s(dir, file_, _TRUNCATE);
    char* last = strrchr(dir, '\\');
    if (last) {
        *last = '\0';
        CreateDirectoryA(dir, nullptr);
    }
}

void Logger::write(const char* format, ...) const {
    if (!enabled_ || file_[0] == '\0') return;

    FILE* fp = nullptr;
    if (fopen_s(&fp, file_, "a") != 0 || !fp) return;

    SYSTEMTIME st;
    GetLocalTime(&st);
    fprintf(fp, "[%04d-%02d-%02d %02d:%02d:%02d] ",
        st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);

    va_list args;
    va_start(args, format);
    vfprintf(fp, format, args);
    va_end(args);

    fprintf(fp, "\n");
    fclose(fp);
}

}  // namespace pptx_selector
