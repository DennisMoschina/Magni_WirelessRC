#include "UserInterface.h"

void UserInterface::setNearestWall(uint8_t direction, uint8_t distance) {
    this->nearestWallDirection = direction;
    this->nearestWallDistance = distance;
}

void UserInterface::setBatteryVoltage(uint16_t voltage) {
    this->batteryVoltage = voltage;
}

void UserInterface::setErrorCode(uint8_t errorCode) {
    this->errorCode = errorCode;
}

void UserInterface::setMotorPWM(uint8_t left, uint8_t right) {
    this->motorPWMLeft = left;
    this->motorPWMRight = right;
}

void UserInterface::setMotorBrake(bool left, bool right) {
    this->motorBrakeLeft = left;
    this->motorBrakeRight = right;
}

void UserInterface::setMotorDirection(bool left, bool right) {
    this->motorDirectionLeft = left;
    this->motorDirectionRight = right;
}

void UserInterface::setRegEngineEnabled(bool enabled) {
    this->engineEnabled = enabled;
}

void UserInterface::enableDebugMode(bool enabled) {
    this->debugModeEnabled = enabled;
}

int8_t UserInterface::getJoystickRightVal() {
    return this->joystickRightVal;
}

int8_t UserInterface::getJoystickForwardVal() {
    return this->joystickForwardVal;
}

bool UserInterface::getEngineEnabled() {
    return this->engineEnabled;
}

bool UserInterface::isDebugModeEnabled() {
    return this->debugModeEnabled;
}