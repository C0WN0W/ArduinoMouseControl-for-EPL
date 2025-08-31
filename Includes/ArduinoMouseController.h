#pragma once
#include <windows.h>
#include <string>

class ArduinoMouseController {
private:
    HANDLE hSerial;
    bool isConnected;

public:
    ArduinoMouseController();
    ~ArduinoMouseController();
    std::wstring ConvertToWideString(const char* narrowStr);
    bool initDevice(const char* portName, DWORD baudRate = 115200);
    void move(int x, int y, int width, int height, int speedModifier = 0);
    void click(int speedModifier = 0);
    void press();
    void release();
    void rightClick();
    void close();
};