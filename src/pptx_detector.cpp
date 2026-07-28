/**
 * ============================================================================
 *  pptx_detector.cpp - PPTX 创建者检测实现
 * ============================================================================
 */
#include "pptx_detector.h"

#include <cstring>
#include <string>

#define MINIZ_NO_TIME
#define MINIZ_NO_ARCHIVE_WRITING_APIS
#define MINIZ_IMPLEMENTATION
#include "miniz.h"

namespace pptx_selector {

namespace {

/// RAII 守护，确保 mz_zip_archive 在所有退出路径上正确释放。
struct ZipGuard {
    mz_zip_archive& z;
    bool valid;
    explicit ZipGuard(mz_zip_archive& archive) : z(archive), valid(false) {}
    ~ZipGuard() { if (valid) mz_zip_reader_end(&z); }
};

/// 提取 <tag>...</tag> 之间的内容。
std::string extractTag(const char* src, std::size_t len, const char* tag) {
    if (!src || len == 0 || !tag) return {};

    char sTag[128], eTag[128];
    _snprintf_s(sTag, sizeof(sTag), _TRUNCATE, "<%s>",  tag);
    _snprintf_s(eTag, sizeof(eTag), _TRUNCATE, "</%s>", tag);

    const char* p = strstr(src, sTag);
    if (!p) return {};
    p += strlen(sTag);

    const char* e = strstr(p, eTag);
    if (!e) return {};

    return std::string(p, static_cast<std::size_t>(e - p));
}

/// 根据 <Application> 文本判断创建软件类型。
AppCreator classifyApp(const std::string& appName) {
    if (appName.find("WPS")       != std::string::npos ||
        appName.find("Kingsoft")  != std::string::npos) {
        return AppCreator::WPS;
    }
    if (appName.find("Microsoft") != std::string::npos ||
        appName.find("PowerPoint") != std::string::npos) {
        return AppCreator::MicrosoftOffice;
    }
    return AppCreator::Unknown;
}

}  // namespace

DetectionResult detectPptxCreator(const void* data, std::size_t size) {
    DetectionResult result;

    if (!data || size == 0) return result;

    mz_zip_archive zip = {};
    ZipGuard guard(zip);

    if (!mz_zip_reader_init_mem(&zip, data, size,
            MZ_ZIP_FLAG_DO_NOT_SORT_CENTRAL_DIRECTORY)) {
        return result;  // ZIP 解析失败，creator 保持 Unknown
    }
    guard.valid = true;

    int idx = mz_zip_reader_locate_file(&zip, "docProps/app.xml", nullptr, 0);
    if (idx < 0) return result;

    std::size_t sz = 0;
    char* pXml = static_cast<char*>(
        mz_zip_reader_extract_to_heap(&zip, idx, &sz, 0));
    if (!pXml) return result;

    result.application = extractTag(pXml, sz, "Application");
    result.creator     = classifyApp(result.application);

    mz_free(pXml);
    return result;
}

}  // namespace pptx_selector
