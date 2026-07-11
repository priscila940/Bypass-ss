@echo off
setlocal enabledelayedexpansion

:: Compile C++ files
g++ -Wall -O2 -mwindows -c anti_share_bypass.cpp -o anti_share_bypass.obj

:: Link
g++ -Wall -O2 -mwindows anti_share_bypass.obj -o anti_share_bypass.exe -lShlwapi -lAdvapi32

:: Clean up
del anti_share_bypass.obj

echo Build completed successfully!
