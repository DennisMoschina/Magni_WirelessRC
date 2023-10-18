#include "CommunicatorUI.h"

CommunicatorUI::CommunicatorUI(Communicator* com) {
    this->com = com;
}

void CommunicatorUI::show() {
    this->com->setNearestWall(this->nearestWallDirection, this->nearestWallDistance);
    this->com->setBatteryVoltage(this->batteryVoltage);
    this->com->setErrorCode(this->errorCode);
    this->com->setMotorPWM(this->motorPWMLeft, this->motorPWMRight);
    this->com->setMotorBrake(this->motorBrakeLeft, this->motorBrakeRight);
    this->com->setMotorDirection(this->motorDirectionLeft, this->motorDirectionRight);
    this->com->setEngineEnabled(this->regEngineEnabled);
}
void CommunicatorUI::readUserIntput() {
    this->joystickRightVal = this->com->getJoystickRightVal();
    this->joystickForwardVal = this->com->getJoystickForwardVal();
    this->engineEnabled = this->com->getEngineEnabled();
    this->debugModeEnabled = this->com->isDebugModeEnabled();
}