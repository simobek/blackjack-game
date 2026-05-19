@echo off
g++ web_main.cpp -o web_blackjack.exe -Iinclude -DASIO_STANDALONE -lws2_32 -lmswsock -O2 -std=c++17
if %errorlevel% neq 0 (
    echo Compilation failed
    exit /b %errorlevel%
)
echo Compilation successful
