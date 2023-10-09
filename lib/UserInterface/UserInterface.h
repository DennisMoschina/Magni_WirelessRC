#ifndef _USER_INTERFACE_H_
#define _USER_INTERFACE_H_

#include <stdint.h>

class UserInterface {
public:
    void setNearestWall(uint8_t direction, uint8_t distance);
    void setBatteryVoltage(uint16_t voltage);
    void setErrorCode(uint8_t errorCode);
    void setMotorPWM(uint8_t left, uint8_t right);
    void setMotorBrake(bool left, bool right);
    void setMotorDirection(bool left, bool right);
    void setEngineEnabled(bool enabled);

    void enableDebugMode(bool enabled = true);

    int8_t getJoystickRightVal();
    int8_t getJoystickForwardVal();
    bool getEngineEnabled();
    bool isDebugModeEnabled();

    virtual void show() = 0;
    virtual void readUserIntput() = 0;

protected:
    uint8_t nearestWallDirection = 0;
    uint8_t nearestWallDistance = 0;
    uint16_t batteryVoltage = 0;
    uint8_t errorCode = 0;
    uint8_t motorPWMLeft = 0;
    uint8_t motorPWMRight = 0;
    bool motorBrakeLeft = false;
    bool motorBrakeRight = false;
    bool motorDirectionLeft = false;
    bool motorDirectionRight = false;
    bool engineEnabled = false;

private:
    int8_t joystickRightVal = 0;
    int8_t joystickForwardVal = 0;
    bool engineEnabled = false;
    bool debugModeEnabled = false;
};

#endif  // _USER_INTERFACE_H_