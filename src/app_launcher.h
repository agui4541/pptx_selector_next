/**
 * ============================================================================
 *  app_launcher.h - 外部程序启动
 *  PPTX 智能打开器
 * ============================================================================
 *  封装 ShellExecuteA，负责以指定 exe 打开 PPTX 文件。
 * ============================================================================
 */
#pragma once

namespace pptx_selector {

/// 检查指定路径的可执行文件是否存在。
bool appExists(const char* exePath);

/// 以 exe 打开 filePath。返回是否启动成功。
/// @param exePath  可执行文件路径
/// @param filePath 要打开的 PPTX 文件路径
bool launchApp(const char* exePath, const char* filePath);

}  // namespace pptx_selector
