#ifndef _BLE_COMMUNICATOR_H_
#define _BLE_COMMUNICATOR_H_

#include <stdint.h>
#include <NimBLEDevice.h>
#include "../config.h"

class BLECommunicator {
public:
    BLECommunicator(const char* deviceName);
    void advertise();

private:
    const char* deviceName;

    NimBLEServer* server;
    NimBLEService* service;

    NimBLECharacteristic* nearestWallCharacteristic;
    NimBLECharacteristic* batteryVoltageCharacteristic;
    NimBLECharacteristic* engineEnabledCharacteristic;
    NimBLECharacteristic* errorCodeCharacteristic;
    NimBLECharacteristic* motorPWMCharacteristic;
    NimBLECharacteristic* motorDirectionCharacteristic;
    NimBLECharacteristic* motorBrakeCharacteristic;

    NimBLECharacteristic* joystickForwardCharacteristic;
    NimBLECharacteristic* joystickRightCharacteristic;
    NimBLECharacteristic* debugModeCharacteristic;
};

#endif  // _BLE_COMMUNICATOR_H_
