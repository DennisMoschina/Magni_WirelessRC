#include "BLECommunicator.h"
#include <config.h>

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
    this->engineEnabledRegCharacteristic = this->service->createCharacteristic(
        ENGINE_ENABLED_REG_CHARACTERISTIC_UUID,
        NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY
    );

    this->joystickForwardCharacteristic = this->service->createCharacteristic(
        JOYSTICK_FORWARD_CHARACTERISTIC_UUID,
        NIMBLE_PROPERTY::WRITE | NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY
    );
    this->joystickRightCharacteristic = this->service->createCharacteristic(
        JOYSTICK_RIGHT_CHARACTERISTIC_UUID,
        NIMBLE_PROPERTY::WRITE | NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY
    );
    this->debugModeCharacteristic = this->service->createCharacteristic(
        DEBUG_MODE_CHARACTERISTIC_UUID,
        NIMBLE_PROPERTY::WRITE | NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY
    );
    this->enableEngineCharacteristic = this->service->createCharacteristic(
        ENABLE_ENGINE_CHARACTERISTIC_UUID,
        NIMBLE_PROPERTY::WRITE | NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY
    );

    this->service->start();

    this->advertising = NimBLEDevice::getAdvertising();
    this->advertising->addServiceUUID(BLE_SERVICE_UUID);
}

void BLECommunicator::advertise() {
    this->advertising->start();
}

void BLECommunicator::stopAdvertising() {
    this->advertising->stop();
}


bool BLECommunicator::isConnected() {
    return this->server->getConnectedCount() > 0;
}

int8_t BLECommunicator::getJoystickRightVal() {
    return this->joystickRightCharacteristic->getValue<int8_t>();
}
int8_t BLECommunicator::getJoystickForwardVal() {
    return this->joystickForwardCharacteristic->getValue<int8_t>();
}
bool BLECommunicator::getEngineEnabled() {
    //TODO: add extra characteristic for enabling engines
    return true;
}
bool BLECommunicator::isDebugModeEnabled() {
    return this->debugModeCharacteristic->getValue<bool>();
}

void BLECommunicator::setNearestWall(uint8_t direction, uint8_t distance) {
    uint16_t value = (uint16_t)direction << 8 | distance;
    this->nearestWallCharacteristic->setValue(value);
    this->nearestWallCharacteristic->notify();
}
void BLECommunicator::setBatteryVoltage(uint16_t voltage) {
    this->batteryVoltageCharacteristic->setValue(voltage);
    this->batteryVoltageCharacteristic->notify();
}
void BLECommunicator::setErrorCode(uint8_t errorCode) {
    this->errorCodeCharacteristic->setValue(errorCode);
    this->errorCodeCharacteristic->notify();
}
void BLECommunicator::setMotorPWM(uint8_t left, uint8_t right) {
    uint16_t value = (uint16_t)left << 8 | right;
    this->motorPWMCharacteristic->setValue(value);
    this->motorPWMCharacteristic->notify();
}
void BLECommunicator::setMotorBrake(bool left, bool right) {
    uint8_t value = (uint8_t)left << 1 | right;
    this->motorBrakeCharacteristic->setValue(value);
    this->motorBrakeCharacteristic->notify();
}
void BLECommunicator::setMotorDirection(bool left, bool right) {
    uint8_t value = (uint8_t)left << 1 | right;
    this->motorDirectionCharacteristic->setValue(value);
    this->motorDirectionCharacteristic->notify();
}
void BLECommunicator::setEngineEnabled(bool enabled) {
    this->engineEnabledRegCharacteristic->setValue(enabled);
    this->engineEnabledRegCharacteristic->notify();
}