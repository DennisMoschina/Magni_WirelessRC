#ifndef _BLE_COMMUNICATOR_H_
#define _BLE_COMMUNICATOR_H_

#include <stdint.h>
#include <NimBLEDevice.h>
#include "config.h"
#include "Communicator.h"

class BLECommunicator: public Communicator {
public:
    BLECommunicator(const char* deviceName);
    void advertise();
    void stopAdvertising();

    int8_t getJoystickRightVal();
    int8_t getJoystickForwardVal();
    bool getEngineEnabled();
    bool isDebugModeEnabled();

    void setNearestWall(uint8_t direction, uint8_t distance);
    void setBatteryVoltage(uint16_t voltage);
    void setErrorCode(uint8_t errorCode);
    void setMotorPWM(uint8_t left, uint8_t right);
    void setMotorBrake(bool left, bool right);
    void setMotorDirection(bool left, bool right);
    void setEngineEnabled(bool enabled);

private:
    const char* deviceName;

    NimBLEServer* server;
    NimBLEService* service;

    NimBLECharacteristic* nearestWallCharacteristic;
    NimBLECharacteristic* batteryVoltageCharacteristic;
    NimBLECharacteristic* engineEnabledRegCharacteristic;
    NimBLECharacteristic* errorCodeCharacteristic;
    NimBLECharacteristic* motorPWMCharacteristic;
    NimBLECharacteristic* motorDirectionCharacteristic;
    NimBLECharacteristic* motorBrakeCharacteristic;

    NimBLECharacteristic* joystickForwardCharacteristic;
    NimBLECharacteristic* joystickRightCharacteristic;
    NimBLECharacteristic* debugModeCharacteristic;
    NimBLECharacteristic* enableEngineCharacteristic;

    NimBLEAdvertising* advertising;
};

#endif  // _BLE_COMMUNICATOR_H_
