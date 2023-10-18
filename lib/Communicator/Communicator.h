#ifndef _COMMUNICATOR_H_
#define _COMMUNICATOR_H_

#include <stdint.h>

class Communicator {
public:
    virtual int8_t getJoystickRightVal() = 0;
    virtual int8_t getJoystickForwardVal() = 0;
    virtual bool getEngineEnabled() = 0;
    virtual bool isDebugModeEnabled() = 0;

    virtual void setNearestWall(uint8_t direction, uint8_t distance) = 0;
    virtual void setBatteryVoltage(uint16_t voltage) = 0;
    virtual void setErrorCode(uint8_t errorCode) = 0;
    virtual void setMotorPWM(uint8_t left, uint8_t right) = 0;
    virtual void setMotorBrake(bool left, bool right) = 0;
    virtual void setMotorDirection(bool left, bool right) = 0;
    virtual void setEngineEnabled(bool enabled) = 0;
};

#endif  // _COMMUNICATOR_H_