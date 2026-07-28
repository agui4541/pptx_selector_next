# ============================================================
#  PPTX 智能打开器 - PowerShell 编译脚本
#  用法: powershell -ExecutionPolicy Bypass -File compile.ps1
# ============================================================
$ErrorActionPreference = "Stop"

Write-Host "============================================" -ForegroundColor Cyan
Write-Host "  PPTX 智能打开器 - 编译脚本" -ForegroundColor Cyan
Write-Host "============================================" -ForegroundColor Cyan
Write-Host ""

# 1. 编译资源文件
Write-Host "[1/2] 编译资源文件..." -ForegroundColor Yellow
windres resources/resource.rc -o resource.o
if ($LASTEXITCODE -ne 0) {
    Write-Host "[失败] 资源编译出错" -ForegroundColor Red
    exit 1
}

# 2. 编译主程序
Write-Host "[2/2] 编译主程序..." -ForegroundColor Yellow
g++ src/main.cpp src/config.cpp src/logger.cpp src/pptx_detector.cpp src/app_launcher.cpp `
    third_party/miniz.c resource.o `
    -o pptx_selector.exe `
    -Isrc -Ithird_party -lshell32 `
    -O2 -mwindows -static -static-libgcc -static-libstdc++ -s

if ($LASTEXITCODE -eq 0) {
    Write-Host ""
    Write-Host "[成功] 编译完成: pptx_selector.exe" -ForegroundColor Green
    Write-Host ""
    Write-Host "使用方法: pptx_selector.exe `"path\to\file.pptx`""
    Write-Host "配置文件: config.ini"
} else {
    Write-Host ""
    Write-Host "[失败] 编译出错" -ForegroundColor Red
    exit 1
}
