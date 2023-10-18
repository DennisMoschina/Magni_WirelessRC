#include "communication.h"
#include "Arduino.h"

void Communication::init(uint32_t baudRate, uint8_t uartConfig, GlobalTime& time)
{
    this->time = &time;
    Serial.begin(baudRate, uartConfig);
}

void Communication::sendPacket(packet_control_t packet)
{
    uint8_t buffer[PACKET_SIZE[PACKET_CONTROL]] = {
        packet.flags,
        packet.joystickForward,
        packet.joystickRight
    };
    sendDatagram(PACKET_CONTROL, buffer, PACKET_SIZE[PACKET_CONTROL]);
}

void Communication::sendPacket(packet_status_t packet)
{
    uint8_t buffer[PACKET_SIZE[PACKET_STATUS]] = {
        packet.flags,
        packet.pwmLeft,
        packet.pwmRight,
        packet.batteryVoltage,
        packet.directionToNearestWall,
        packet.distanceToNearestWall
    };
    sendDatagram(PACKET_STATUS, buffer, PACKET_SIZE[PACKET_STATUS]);
}

void Communication::sendPacket(packet_error_t packet)
{
    uint8_t buffer[PACKET_SIZE[PACKET_ERROR]] = {
        packet.errorcode
    };
    sendDatagram(PACKET_ERROR, buffer, PACKET_SIZE[PACKET_ERROR]);
}

void Communication::pollChannel()
{
    while(Serial.available())
    {
        if(!receivingPacket) {
            // consume packets and check for headers
            int data = Serial.read();
            if((data & 0xf0) != SYNC_NIBBLE)
                continue; // not a header, load next
            
            switch(data & 0x0f) {
                case PACKET_CONTROL:
                    // known packet. Continue
                    receivingPacket = true;
                    rxPacketType = PACKET_CONTROL;
                    rxChecksum = data & 0xff;
                    break;
                case PACKET_STATUS:
                    // known packet. Continue
                    receivingPacket = true;
                    rxPacketType = PACKET_STATUS;
                    rxChecksum = data & 0xff;
                    break;
                case PACKET_ERROR:
                    // known packet. Continue
                    receivingPacket = true;
                    rxPacketType = PACKET_ERROR;
                    rxChecksum = data & 0xff;
                    break;
                default:
                    continue; // unknown packet type, load next
            }
        }
        
        // When receiving a packet, wait until it is completely in the Serial buffer, including
        // checksum but excluding header, since the header has already been processed.
        size_t rxPacketSize = PACKET_SIZE[rxPacketType];
        if(Serial.available() < static_cast<int>(rxPacketSize + 1)) {
            // packet not fully in buffer yet
            return;
        }

        uint8_t buffer[rxPacketSize];
        Serial.readBytes(buffer, rxPacketSize);

        for(size_t i=0; i<rxPacketSize; i++) {
            rxChecksum += buffer[i];
        }

        // Obtain checksum and compare to calculated checksum.
        uint8_t checksum = Serial.read() & 0xff;
        if(rxChecksum != checksum) {
            // Checksum check failed, abort.
            receivingPacket = false;
            continue;
        }

        // Store packet (to avoid race conditions between IRQs and this section, interrupts are disabled)
        switch(rxPacketType) {
            case PACKET_CONTROL:
                cli();
                lastPacket.control.packet.flags                 = buffer[0];
                lastPacket.control.packet.joystickForward   = buffer[1];
                lastPacket.control.packet.joystickRight     = buffer[2];
                lastPacket.control.rxTimestamp = (time != nullptr) ? time->getTimeMS() : 0;
                sei();
                break;
            case PACKET_STATUS:
                cli();
                lastPacket.status.packet.flags                  = buffer[0];
                lastPacket.status.packet.pwmLeft                = buffer[1];
                lastPacket.status.packet.pwmRight               = buffer[2];
                lastPacket.status.packet.batteryVoltage         = buffer[3];
                lastPacket.status.packet.directionToNearestWall = buffer[4];
                lastPacket.status.packet.distanceToNearestWall  = buffer[5];
                lastPacket.status.rxTimestamp = (time != nullptr) ? time->getTimeMS() : 0;
                sei();
                break;
            case PACKET_ERROR:
                cli();
                lastPacket.error.packet.errorcode = buffer[0];
                lastPacket.error.rxTimestamp = (time != nullptr) ? time->getTimeMS() : 0;
                sei();
                break;
            default:
                // should not be reached
                break;
        }
            
        // Wait for next packet
        receivingPacket = false;
    }
}

void Communication::getLastPacket(packet_control_t& packet, uint32_t& rxTimestamp)
{
    packet = lastPacket.control.packet;
    rxTimestamp = lastPacket.control.rxTimestamp;
}

void Communication::getLastPacket(packet_status_t& packet, uint32_t& rxTimestamp)
{
    packet = lastPacket.status.packet;
    rxTimestamp = lastPacket.status.rxTimestamp;
}

void Communication::getLastPacket(packet_error_t& packet, uint32_t& rxTimestamp)
{
    packet = lastPacket.error.packet;
    rxTimestamp = lastPacket.error.rxTimestamp;
}

/**
 * Sends a datagram consisting of:
 *  - header byte (SYNC nibble, packet type nibble)
 *  - data
 *  - checksum byte (uint8 sum of header and all data bytes)
 **/
void Communication::sendDatagram(uint8_t packetTypeNibble, uint8_t* data, size_t bytes)
{
    uint8_t checksum = 0;
    
    uint8_t header = SYNC_NIBBLE | (packetTypeNibble & 0x0f);
    Serial.write(header);
    checksum += header;

    for (size_t i=0; i<bytes; i++)
    {
        Serial.write(data[i]);
        checksum += data[i];
    }

    Serial.write(checksum);
}
