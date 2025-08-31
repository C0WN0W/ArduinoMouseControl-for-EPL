#pragma once
#pragma once
#include "Includes/ArduinoMouseController.h"

extern "C" {
    __declspec(dllexport) bool InitDevice(const char* portName, DWORD baudRate = 115200);
    __declspec(dllexport) void Move(int x, int y, int width, int height, int speedModifier = 0);
    __declspec(dllexport) void Click(int speedModifier = 0);
    __declspec(dllexport) void Press();
    __declspec(dllexport) void Release();
    __declspec(dllexport) void RightClick();
    __declspec(dllexport) void Close();
}