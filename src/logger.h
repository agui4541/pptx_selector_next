/**
 * ============================================================================
 *  logger.h - 日志系统
 *  PPTX 智能打开器
 * ============================================================================
 *  轻量级文件日志，按行写入，自动补时间戳。
 *  通过 Config 初始化；禁用时所有写操作为空操作。
 * ============================================================================
 */
#pragma once

#include <windows.h>

namespace pptx_selector {

class Logger {
public:
    /// 默认构造：禁用日志，无文件。
    Logger();

    /// 按配置初始化日志器。enableLog=false 时所有写操作静默。
    Logger(bool enableLog, const char* logFile);

    /// 创建日志文件所在目录（若启用且目录不存在）。
    void initDir() const;

    /// 写入一行日志，自动添加时间戳与换行。禁用时为空操作。
    void write(const char* format, ...) const;

private:
    bool enabled_;
    char file_[MAX_PATH];
};

}  // namespace pptx_selector
