#include "ArduinoMouseExports.h"

static ArduinoMouseController mouseController;

extern "C" {
    __declspec(dllexport) bool InitDevice(const char* portName, DWORD baudRate) {
        return mouseController.initDevice(portName, baudRate);
    }

    __declspec(dllexport) void Move(int x, int y, int width, int height, int speedModifier) {
        mouseController.move(x, y, width, height, speedModifier);
    }

    __declspec(dllexport) void Click(int speedModifier) {
        mouseController.click(speedModifier);
    }

    __declspec(dllexport) void Press() {
        mouseController.press();
    }

    __declspec(dllexport) void Release() {
        mouseController.release();
    }

    __declspec(dllexport) void RightClick() {
        mouseController.rightClick();
    }

    __declspec(dllexport) void Close() {
        mouseController.close();
    }
}