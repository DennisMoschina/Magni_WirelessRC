/*
    config.h

    Author: Leonardo Schoch
    E-Mail: leonardo.schoch@student.kit.edu

    This header file contains all configurable parameters of the remote control
    board, as for example its pinout.
    
*/


#ifndef CONFIG_H_
#define CONFIG_H_

#include <Arduino.h>

static const uint32_t UART_BAUDRATE = 38400;
static const uint8_t UART_CONFIG    = SERIAL_8N1;      // 8 data-bits, no parity bit, 1 stop bit

static const char* DEVICE_NAME = "Magni RC";
static const char* BLE_SERVICE_UUID = "4fafc201-1fb5-459e-8fcc-c5c9c331914b";

static const char* NEAREST_WALL_CHARACTERISTIC_UUID = "beb5483e-36e1-4688-b7f5-ea07361b26a8";
static const char* BATTERY_VOLTAGE_CHARACTERISTIC_UUID = "beb5483e-36e1-4688-b7f5-ea07361b26a9";
static const char* ERROR_CODE_CHARACTERISTIC_UUID = "beb5483e-36e1-4688-b7f5-ea07361b26aa";
static const char* MOTOR_PWM_CHARACTERISTIC_UUID = "beb5483e-36e1-4688-b7f5-ea07361b26ab";
static const char* MOTOR_DIRECTION_CHARACTERISTIC_UUID = "beb5483e-36e1-4688-b7f5-ea07361b26ac";
static const char* MOTOR_BRAKE_CHARACTERISTIC_UUID = "beb5483e-36e1-4688-b7f5-ea07361b26ad";
static const char* ENGINE_ENABLED_REG_CHARACTERISTIC_UUID = "beb5483e-36e1-4688-b7f5-ea07361b26ae";

static const char* JOYSTICK_FORWARD_CHARACTERISTIC_UUID = "beb5483e-36e1-4688-b7f5-ea07361b26af";
static const char* JOYSTICK_RIGHT_CHARACTERISTIC_UUID = "beb5483e-36e1-4688-b7f5-ea07361b26b0";
static const char* DEBUG_MODE_CHARACTERISTIC_UUID = "beb5483e-36e1-4688-b7f5-ea07361b26b1";
static const char* ENABLE_ENGINE_CHARACTERISTIC_UUID = "beb5483e-36e1-4688-b7f5-ea07361b26b2";

#endif  // CONFIG_H_