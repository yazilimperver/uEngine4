@echo off
echo %time% < nul
ninja -t clean
ninja
echo %time% < nul