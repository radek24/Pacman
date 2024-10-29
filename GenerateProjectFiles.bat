@echo off
REM Navigate to the project root directory (optional)
cd /d %~dp0

REM Run Premake to generate the Visual Studio 2022 project
vendor\bin\premake5.exe vs2022

REM Check if Premake was successful
if %errorlevel% neq 0 (
    echo "Failed to generate Visual Studio 2022 project file."
    exit /b %errorlevel%
) else (
    echo "Project file successfully generated."
)

pause