#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <Arduino.h>
#include <stdbool.h>
#include <stdint.h>
#include "globaltime.hpp"

/**
 * Implementation of a packet communication mechanism using headers and a checksum.
 * 
 * getLastPacket() can be called from non-IRQ and IRQ context.
 * IMPORTANT: When receiving a packet, this class briefly disables interrupts (sei(); cli()).
 **/
class Communication {
public:
    typedef struct __attribute__((__packed__)) {
        uint8_t flags;
        uint8_t pwmLeft;
        uint8_t pwmRight;
        uint8_t batteryVoltage;
        uint8_t directionToNearestWall;
        uint8_t distanceToNearestWall;
    } packet_status_t;

    typedef struct __attribute__((__packed__)) {
        uint8_t flags;
        uint8_t joystickForward;
        uint8_t joystickRight;
    } packet_control_t;

    typedef struct __attribute__((__packed__)) {
        uint8_t errorcode;
    } packet_error_t;


    void init(uint32_t baudRate, uint8_t uartConfig, GlobalTime& time);
    void sendPacket(packet_control_t packet);
    void sendPacket(packet_status_t packet);
    void sendPacket(packet_error_t packet);
    void pollChannel();
    void getLastPacket(packet_control_t& packet, uint32_t& rxTimestamp);
    void getLastPacket(packet_status_t& packet, uint32_t& rxTimestamp);
    void getLastPacket(packet_error_t& packet, uint32_t& rxTimestamp);


private:
    static const uint8_t SYNC_NIBBLE = (0b1010 << 4);
    void sendDatagram(uint8_t packetTypeNibble, uint8_t* data, size_t bytes);

    // Packet types and their identifying nibbles (4-byte ID)
    enum PacketType {
        PACKET_STATUS = 0U,     // Status data. REG -> RC
        PACKET_CONTROL = 1U,    // Control data. RC -> REG
        PACKET_ERROR = 2U,      // ERROR code. REG -> RC
        PACKET_TYPE_SIZE
    };

    struct {
        struct {
            uint32_t rxTimestamp = 0;
            packet_control_t packet;
        } control;
        struct {
            uint32_t rxTimestamp = 0;
            packet_status_t packet;
        } status;
        struct {
            uint32_t rxTimestamp = 0;
            packet_error_t packet;
        } error;
    } lastPacket;

    GlobalTime* time = nullptr;
    bool receivingPacket = false;
    PacketType rxPacketType;
    uint8_t rxChecksum;

    // Packet sizes. Index must match value of enum entry.
    size_t PACKET_SIZE[PACKET_TYPE_SIZE] = {
        sizeof(packet_status_t),
        sizeof(packet_control_t),
        sizeof(packet_error_t)
    };
};

#endif