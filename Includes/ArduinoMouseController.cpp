#include "ArduinoMouseController.h"
#include <iostream>

#include <atlbase.h>
#include <atlconv.h>

ArduinoMouseController::ArduinoMouseController() : isConnected(false), hSerial(INVALID_HANDLE_VALUE) {}

ArduinoMouseController::~ArduinoMouseController() {
    close();
}

LPCWSTR ConvertToLPCWSTR(const char* narrowStr) {
    return CA2W(narrowStr, CP_UTF8); // CP_UTF8 或 CP_ACP
}

bool ArduinoMouseController::initDevice(const char* portName, DWORD baudRate) {
    hSerial = CreateFile(ConvertToLPCWSTR(portName), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hSerial == INVALID_HANDLE_VALUE) {
        std::cerr << "无法连接到串口 " << portName << std::endl;
        return false;
    }

    DCB serialParams = { 0 };
    serialParams.DCBlength = sizeof(serialParams);
    GetCommState(hSerial, &serialParams);
    serialParams.BaudRate = baudRate;
    serialParams.ByteSize = 8;
    serialParams.StopBits = ONESTOPBIT;
    serialParams.Parity = NOPARITY;
    SetCommState(hSerial, &serialParams);

    isConnected = true;
    return true;
}

void ArduinoMouseController::move(int relX, int relY, int width, int height, int speedModifier) {
    if (isConnected) {
        std::string command = std::to_string(relX) + "," + std::to_string(relY) + ",0," + std::to_string(speedModifier) + "\n";
        DWORD bytesSent;
        WriteFile(hSerial, command.c_str(), command.size(), &bytesSent, NULL);
    }
}

void ArduinoMouseController::click(int speedModifier) {
    if (isConnected) {
        std::string command = "0,0,1," + std::to_string(speedModifier) + "\n";
        DWORD bytesSent;
        WriteFile(hSerial, command.c_str(), command.size(), &bytesSent, NULL);
    }
}

void ArduinoMouseController::press() {
    if (isConnected) {
        std::string command = "0,0,2\n";
        DWORD bytesSent;
        WriteFile(hSerial, command.c_str(), command.size(), &bytesSent, NULL);
    }
}

void ArduinoMouseController::release() {
    if (isConnected) {
        std::string command = "0,0,3\n";
        DWORD bytesSent;
        WriteFile(hSerial, command.c_str(), command.size(), &bytesSent, NULL);
    }
}

void ArduinoMouseController::rightClick() {
    if (isConnected) {
        std::string command = "0,0,4\n";
        DWORD bytesSent;
        WriteFile(hSerial, command.c_str(), command.size(), &bytesSent, NULL);
    }
}

void ArduinoMouseController::close() {
    if (isConnected) {
        CloseHandle(hSerial);
        isConnected = false;
    }
}