@echo off
setlocal enabledelayedexpansion
echo ============================================
echo   PPTX 智能打开器 - 编译脚本
echo ============================================
echo.

set "SRC=src\main.cpp src\config.cpp src\logger.cpp src\pptx_detector.cpp src\app_launcher.cpp"
set "THIRD=third_party\miniz.c"
set "INC=-Isrc -Ithird_party"
set "LIBS=-lshell32"
set "FLAGS=-O2 -mwindows -static -static-libgcc -static-libstdc++ -s"

echo [1/2] 编译资源文件...
windres resources\resource.rc -o resource.o
if %errorlevel% neq 0 (
    echo [失败] 资源编译出错
    pause
    exit /b 1
)

echo [2/2] 编译主程序...
g++ %SRC% %THIRD% resource.o -o pptx_selector.exe %INC% %LIBS% %FLAGS%
if %errorlevel% equ 0 (
    echo.
    echo [成功] 编译完成: pptx_selector.exe
    echo.
    echo 使用方法: pptx_selector.exe "path\to\file.pptx"
    echo 配置文件: config.ini
) else (
    echo.
    echo [失败] 编译出错
)
pause
