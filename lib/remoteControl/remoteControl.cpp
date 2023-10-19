#include "remoteControl.h"
#include <ctype.h>

void controlLoopExternal(void* param) {
    RemoteControl* rc = (RemoteControl*) param;

    while(true) {
        rc->controlLoop();
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}

void uiLoopExternal(void* param) {
    RemoteControl* rc = (RemoteControl*) param;

    while(true) {
        rc->uiLoop();
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}

RemoteControl::RemoteControl(GlobalTime& time, UserInterface& ui, Communication& com) {
    this->time = &time;
    this->ui = &ui;
    this->com = com;

    com.init(UART_BAUDRATE, UART_CONFIG, time);
}

/**
 * @brief Send new values via UART to the control board.
 * 
 */
void RemoteControl::uartSend() {
    Communication::packet_control_t control;
    control.flags = 0;
    control.flags |= (control_data.debugModeEnabled << 7);
    control.flags |= (control_data.engineEnabled << 6);

    control.joystickRight = control_data.joystickRightVal;
    control.joystickForward = control_data.joystickForwardVal;

    com.sendPacket(control);
}

/**
 * @brief Recieve new values via UART from the control board
 * 
 */
void RemoteControl::uartReceive() {
    com.pollChannel();

    uint32_t rxStatusTimestamp = 0;
    Communication::packet_status_t status;
    com.getLastPacket(status, rxStatusTimestamp);

    if(rxStatusTimestamp != lastStatusPacketTimestamp) {
        lastStatusPacketTimestamp = rxStatusTimestamp;

        status_data.dirRight                = status.flags & (1 << 7);
        status_data.dirLeft                 = status.flags & (1 << 6);
        status_data.brakeRight              = status.flags & (1 << 5);
        status_data.brakeLeft               = status.flags & (1 << 4);
        status_data.engineEnabled           = status.flags & (1 << 3);

        status_data.pwmLeft                 = status.pwmLeft;
        status_data.pwmRight                = status.pwmRight;

        status_data.batteryVoltage          = status.batteryVoltage * 2;
        status_data.directionToNearestWall  = status.directionToNearestWall;
        status_data.distanceToNearestWall   = status.distanceToNearestWall;

        newStatusDataAvailable = true;
    }


    uint32_t rxErrorTimestamp = 0;
    Communication::packet_error_t error;
    com.getLastPacket(error, rxErrorTimestamp);

    if(rxErrorTimestamp != lastErrorPacketTimestamp) {
        lastErrorPacketTimestamp = rxErrorTimestamp;
        // TODO: Handle error
    }


    if(min(time->getTimeMS() - lastErrorPacketTimestamp, time->getTimeMS() - lastStatusPacketTimestamp) > COMMUNICATION_TIMEOUT_MS) {
        // Communication time out since no packet was received.
        // TODO: Handle error
        this->ui->setErrorCode(0x2);
    }
}

void RemoteControl::startControlling() {
    log_i("Starting control loop");

    xTaskCreate(controlLoopExternal, "RC Control Loop", 2048, this, 1, this->controlLoopTaskHandle);
    xTaskCreate(uiLoopExternal, "RC UI Loop", 2048, this, 1, this->uiLoopTaskHandle);

    log_d("Control loop started");
}

void RemoteControl::stopControlling() {
    vTaskDelete(this->controlLoopTaskHandle);
    vTaskDelete(this->uiLoopTaskHandle);
}

void RemoteControl::controlLoop() {
    this->ui->readUserIntput();
    this->control_data.joystickForwardVal = this->ui->getJoystickForwardVal();
    this->control_data.joystickRightVal = this->ui->getJoystickRightVal();
    this->control_data.engineEnabled = this->ui->getEngineEnabled();
    this->control_data.debugModeEnabled = this->ui->isDebugModeEnabled();
    this->uartSend();
}

void RemoteControl::uiLoop() {
    this->uartReceive();

    if (!this->newStatusDataAvailable) {
        return;
    }

    this->ui->setMotorPWM(this->status_data.pwmLeft, this->status_data.pwmRight);
    this->ui->setBatteryVoltage(this->status_data.batteryVoltage);
    this->ui->setErrorCode(this->status_data.errorCode);
    this->ui->setNearestWall(this->status_data.directionToNearestWall, this->status_data.distanceToNearestWall);
    this->ui->setMotorBrake(this->status_data.brakeLeft, this->status_data.brakeRight);
    this->ui->setMotorDirection(this->status_data.dirLeft, this->status_data.dirRight);
    this->ui->setRegEngineEnabled(this->status_data.engineEnabled);

    this->newStatusDataAvailable = false;
    this->ui->show();
}