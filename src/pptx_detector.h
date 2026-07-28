/**
 * ============================================================================
 *  pptx_detector.h - PPTX 创建者检测
 *  PPTX 智能打开器
 * ============================================================================
 *  PPTX 本质是 ZIP 包，内部 docProps/app.xml 的 <Application> 标签记录
 *  创建软件。本模块在内存中解析 ZIP 并提取该信息。
 * ============================================================================
 */
#pragma once

#include <cstddef>
#include <string>

namespace pptx_selector {

/// PPTX 文件的创建软件类型。
enum class AppCreator {
    Unknown,         ///< 未能识别
    WPS,             ///< WPS 演示（含 Kingsoft）
    MicrosoftOffice, ///< Microsoft PowerPoint
};

/// 检测结果。
struct DetectionResult {
    AppCreator  creator     = AppCreator::Unknown;
    std::string application;  ///< <Application> 原始内容，便于日志展示
};

/// 在内存中检测 PPTX 文件的创建软件。
/// @param data  PPTX 文件完整内容（ZIP 格式）
/// @param size  数据字节数
/// @return 检测结果；解析失败时 creator 为 Unknown。
DetectionResult detectPptxCreator(const void* data, std::size_t size);

}  // namespace pptx_selector
