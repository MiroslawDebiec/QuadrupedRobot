#pragma once

#ifndef SR518_h
#define SR518_h

//Instructions
#define READ 2
#define WRITE 3
#define SYNC_WRITE 131

//Data Lenghts
#define POSITION_LENGTH 5
#define TEMPERATURE_LENGTH 4
#define VOLTAGE_LENGTH 4
#define SPEED_LENGTH 5
#define READ_POS_LENGTH 4

//Addresses
#define MIN_POSITION_L 6
#define MAX_POSITION_L 8
#define GOAL_POSITION_L 30
#define PRESENT_TEMPERATURE 43
#define PRESENT_VOLTAGE 42
#define PRESENT_SPEED_L 38
#define PRESENT_POSITION_L 36

//Variables
#define START_FLAG 255
#define TX_MODE 1
#define RX_MODE 0
#define TIME_OUT 10
#define BYTE_READ 1
#define BYTE_READ_POS 2
#define BROADCAST_ID 254

//#define POSITION_ACCURACY 1
#define POSITION_RESOLUTION_L 0.29
#define POSITION_RESOLUTION_H 3.45

#include "Arduino.h"
#include <string>

class SR518
{
public:
    // Serial
    void setSerial(HardwareSerial *sPort);
    void begin(long baud, unsigned char directionPin);

    // Movement
    int move(byte id, double position);
    int moveAll(double coxa_pos_angle, double femur_pos_angle, double tibia_pos_angle);

    // Config
    int setPosLimitMin(byte id, double pos);
    int setPosLimitMax(byte id, double pos);

    // Readings
    int getTemperature(byte id);
    double getVoltage(byte id);
    double getPosition(byte id);
    double getCurrentPosition(byte id, double last_position); 
    int getSpeed(byte id);
    int getLoad(byte id);

private:
    HardwareSerial *serialPort;
    unsigned char Checksum;
    unsigned char Direction_Pin;
    unsigned char Time_Counter;
    unsigned char Incoming_Byte;
    unsigned char Position_High_Byte;
    unsigned char Position_Low_Byte;

    int Temperature_Byte;
    int Voltage_Byte;
    int Position_Long_Byte;
    int Error_Byte;

    int read_error(void);
};

extern SR518 Hub;

#endif
