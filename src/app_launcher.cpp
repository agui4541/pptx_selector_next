/**
 * ============================================================================
 *  app_launcher.cpp - 外部程序启动实现
 * ============================================================================
 */
#include "app_launcher.h"

#include <cstdio>
#include <windows.h>
#include <shellapi.h>

namespace pptx_selector {

bool appExists(const char* exePath) {
    return GetFileAttributesA(exePath) != INVALID_FILE_ATTRIBUTES;
}

bool launchApp(const char* exePath, const char* filePath) {
    char quoted[MAX_PATH + 4];
    _snprintf_s(quoted, sizeof(quoted), _TRUNCATE, "\"%s\"", filePath);

    // ShellExecuteA 返回值 > 32 表示成功。
    auto r = reinterpret_cast<intptr_t>(
        ShellExecuteA(nullptr, "open", exePath, quoted, nullptr, SW_SHOWNORMAL));

    return r > 32;
}

}  // namespace pptx_selector
