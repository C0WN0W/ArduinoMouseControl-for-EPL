#pragma once
#pragma once
#include <vector>
#include <string>

struct SerialPortInfo {
    std::string portName;
    std::string description;
    bool isArduino;
};

std::vector<SerialPortInfo> autoDetectArduinoPorts();