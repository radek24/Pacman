@echo off
title Project Setup

:menu
cls
echo ======================================================
echo.               Welcome to the Build Setup Script
echo ======================================================
echo.
echo Select the platform for which you want to generate project files:
echo.
echo 1. GNU Make (gmake)
echo 2. Visual Studio 2022 (vs2022)
echo.
set /p choice="Enter your choice (1 or 2): "

if "%choice%"=="1" goto gmake
if "%choice%"=="2" goto vs2022
echo Invalid selection! Please enter 1 or 2.
pause
goto menu

:gmake
cls
echo ======================================================
echo.               Generating project files for GNU Make
echo ======================================================
echo.
echo [*] Running premake5 for gmake...
vendor\bin\premake5.exe gmake
goto end

:vs2022
cls
echo ======================================================
echo.          Generating project files for Visual Studio 2022
echo ======================================================
echo.
echo [*] Running premake5 for Visual Studio 2022...
vendor\bin\premake5.exe vs2022
goto end

:end
echo ======================================================
echo.                Setup complete! You can now build.
echo ======================================================
pause
exit