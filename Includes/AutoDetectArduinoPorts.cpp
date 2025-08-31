#include "AutoDetectArduinoPorts.h"
#include <windows.h>
#include <setupapi.h>
#include <devguid.h>
#include <iostream>

#pragma comment(lib, "setupapi.lib")

std::vector<SerialPortInfo> autoDetectArduinoPorts() {
    std::vector<SerialPortInfo> arduinoPorts;

    HDEVINFO hDevInfo = SetupDiGetClassDevs(&GUID_DEVCLASS_PORTS, NULL, NULL, DIGCF_PRESENT);
    if (hDevInfo == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to get device info!" << std::endl;
        return arduinoPorts;
    }

    SP_DEVINFO_DATA devInfoData = { 0 };
    devInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

    for (DWORD i = 0; SetupDiEnumDeviceInfo(hDevInfo, i, &devInfoData); i++) {
        char portName[256] = { 0 };
        char desc[256] = { 0 };

        // Get Device Name
        SetupDiGetDeviceRegistryProperty(hDevInfo, &devInfoData, SPDRP_FRIENDLYNAME, NULL, (BYTE*)portName, sizeof(portName), NULL);
        SetupDiGetDeviceRegistryProperty(hDevInfo, &devInfoData, SPDRP_DEVICEDESC, NULL, (BYTE*)desc, sizeof(desc), NULL);

        bool isArduino = (strstr(desc, "Arduino") || strstr(desc, "CH340") || strstr(desc, "FTDI") || strstr(desc, "USB Serial") || strstr(desc, "ACM") || strstr(desc, "leonardo") || strstr(desc, "micro"));

        arduinoPorts.push_back({ portName, desc, isArduino });
    }

    SetupDiDestroyDeviceInfoList(hDevInfo);
    return arduinoPorts;
}