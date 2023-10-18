/*
    remoteControl.h

    Author: Leonardo Schoch
    E-Mail: leonardo.schoch@student.kit.edu
    
*/


#ifndef REMOTECONTROL_H_
#define REMOTECONTROL_H_

#include <Arduino.h>
#include <stdbool.h>
#include <stdint.h>

#include "config.h"
#include "communication.h"
#include "globaltime.hpp"
#include "UserInterface.h"

class RemoteControl {
public:
    RemoteControl(GlobalTime& time, UserInterface& ui, Communication& com);

    /**
     * @brief Create tasks for reading user input and controlling the car.
     */
    void startControlling();
    void stopControlling();

    void controlLoop();
    void uiLoop();

private:
    static const uint32_t COMMUNICATION_TIMEOUT_MS = 5000;
    
    GlobalTime* time;
    UserInterface* ui;
    Communication com;

    TaskHandle_t* controlLoopTaskHandle;
    TaskHandle_t* uiLoopTaskHandle;

    // communication
    uint32_t lastStatusPacketTimestamp = 0;
    uint32_t lastErrorPacketTimestamp = 0;

    /// Status data (received)
    struct {
        bool dirRight = false;
        bool dirLeft = false;
        bool brakeRight = false;
        bool brakeLeft = false;
        bool engineEnabled = false;
        uint8_t pwmLeft = 0;
        uint8_t pwmRight = 0;
        uint8_t errorCode = 0;
        uint16_t batteryVoltage = 0;
        uint8_t directionToNearestWall = 0;
        uint8_t distanceToNearestWall = 0;
    } status_data;
    bool newStatusDataAvailable = false;

    /// Control data (to send)
    struct {
        int8_t joystickRightVal = 0;
        int8_t joystickForwardVal = 0;
        bool engineEnabled = false;
        bool debugModeEnabled = false;
    } control_data;
    
    void uartSend();
    void uartReceive();
};


#endif  // REMOTECONTROL_H_