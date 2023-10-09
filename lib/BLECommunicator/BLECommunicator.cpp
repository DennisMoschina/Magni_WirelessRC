#include "BLECommunicator.h"

BLECommunicator::BLECommunicator(const char* deviceName) {
    this->deviceName = deviceName;

    NimBLEDevice::init(this->deviceName);
    this->server = NimBLEDevice::createServer();
    this->service = this->server->createService(BLE_SERVICE_UUID);

    this->nearestWallCharacteristic = this->service->createCharacteristic(
        NEAREST_WALL_CHARACTERISTIC_UUID,
        NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY
    );
    this->batteryVoltageCharacteristic = this->service->createCharacteristic(
        BATTERY_VOLTAGE_CHARACTERISTIC_UUID,
        NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY
    );
    this->errorCodeCharacteristic = this->service->createCharacteristic(
        ERROR_CODE_CHARACTERISTIC_UUID,
        NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY
    );
    this->motorPWMCharacteristic = this->service->createCharacteristic(
        MOTOR_PWM_CHARACTERISTIC_UUID,
        NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY
    );
    this->motorDirectionCharacteristic = this->service->createCharacteristic(
        MOTOR_DIRECTION_CHARACTERISTIC_UUID,
        NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY
    );
    this->motorBrakeCharacteristic = this->service->createCharacteristic(
        MOTOR_BRAKE_CHARACTERISTIC_UUID,
        NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY
    );
    this->engineEnabledCharacteristic = this->service->createCharacteristic(
        ENGINE_ENABLED_CHARACTERISTIC_UUID,
        NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY
    );


}

void BLECommunicator::advertise() {
}