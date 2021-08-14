#if defined(ARDUINO) && ARDUINO >= 100 // Arduino IDE Version
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include "SR518.h"

int SR518::read_error()
{
  Time_Counter = 0;
  while ((serialPort->available() < 5) & (Time_Counter < TIME_OUT))
  { // Wait for Data
    Time_Counter++;
    delayMicroseconds(1000);
  }

  while (serialPort->available() > 0)
  {
    if ((serialPort->read() == START_FLAG) & (serialPort->peek() == START_FLAG))
    {                                  //Checks for begining of Status Packet 0xFF 0xFF
      serialPort->read();              // START_FLAG
      serialPort->read();              // ID
      serialPort->read();              // LENGTH
      Error_Byte = serialPort->read(); // ERROR
      Serial.print("Error: ");         //
      Serial.println(Error_Byte);      //
      return (Error_Byte);
    }
  }
  return (-1); // No Response
}

void SR518::setSerial(HardwareSerial *sPort)
{
  serialPort = sPort;
}

void SR518::begin(long baud, unsigned char directionPin)
{
  Direction_Pin = directionPin;
  pinMode(Direction_Pin, OUTPUT);
  serialPort->begin(baud);
}

int SR518::move(byte id, double position_angle)
{
  int position = position_angle * POSITION_RESOLUTION_H;
  char pos_h = position >> 8;
  char pos_l = position % 256;
  byte checksum = ~lowByte(id + POSITION_LENGTH + WRITE + GOAL_POSITION_L + pos_l + pos_h);

  digitalWrite(Direction_Pin, TX_MODE);
  serialPort->write(START_FLAG);
  serialPort->write(START_FLAG);
  serialPort->write(id);
  serialPort->write(POSITION_LENGTH); //Length
  serialPort->write(WRITE); //Instruction
  serialPort->write(GOAL_POSITION_L); //First Address of data write
  serialPort->write(pos_l); //First data write
  serialPort->write(pos_h); //Second data write
  serialPort->write(checksum);
  serialPort->flush();
  digitalWrite(Direction_Pin, RX_MODE);
  return (read_error());
}

int SR518::moveAll(double coxa_pos_angle, double femur_pos_angle, double tibia_pos_angle) // Moving Two Servos 1, 2
{
  char servo_ID_1 = 1;
  char servo_ID_2 = 2;
  char servo_ID_3 = 3;
  char servo_ID_4 = 4;
  char servo_ID_5 = 5;
  char servo_ID_6 = 6;
  char servo_ID_7 = 7;
  char servo_ID_8 = 8;
  char servo_ID_9 = 9;
  char servo_ID_10 = 10;
  char servo_ID_11 = 11;
  char servo_ID_12 = 12;

  char speed_l = 80;
  char speed_h = 1;

  int coxa_position = coxa_pos_angle * POSITION_RESOLUTION_H;
  char coxa_pos_h = coxa_position >> 8;
  char coxa_pos_l = coxa_position % 256;

  int femur_position = femur_pos_angle * POSITION_RESOLUTION_H;
  char femur_pos_h = femur_position >> 8;
  char femur_pos_l = femur_position % 256;
  
  int tibia_position = tibia_pos_angle * POSITION_RESOLUTION_H;
  char tibia_pos_h = tibia_position >> 8;
  char tibia_pos_l = tibia_position % 256;


  byte Lenght = (READ_POS_LENGTH + 1) * 12 + 4;

  byte checksum = ~lowByte(BROADCAST_ID + Lenght + SYNC_WRITE + 0x1E + READ_POS_LENGTH + 
  servo_ID_1 + coxa_pos_l + coxa_pos_h + speed_l + speed_h +
  servo_ID_2 + coxa_pos_l + coxa_pos_h + speed_l + speed_h +
  servo_ID_3 + coxa_pos_l + coxa_pos_h + speed_l + speed_h +
  servo_ID_4 + coxa_pos_l + coxa_pos_h + speed_l + speed_h +
  servo_ID_5 + femur_pos_l + femur_pos_h + speed_l + speed_h +
  servo_ID_6 + femur_pos_l + femur_pos_h + speed_l + speed_h +
  servo_ID_7 + femur_pos_l + femur_pos_h + speed_l + speed_h +
  servo_ID_8 + femur_pos_l + femur_pos_h + speed_l + speed_h +
  servo_ID_9 + tibia_pos_l + tibia_pos_h + speed_l + speed_h +
  servo_ID_10 + tibia_pos_l + tibia_pos_h + speed_l + speed_h +
  servo_ID_11 + tibia_pos_l + tibia_pos_h + speed_l + speed_h +
  servo_ID_12 + tibia_pos_l + tibia_pos_h + speed_l + speed_h);

  digitalWrite(Direction_Pin, TX_MODE);
  serialPort->write(START_FLAG);
  serialPort->write(START_FLAG);
  serialPort->write(BROADCAST_ID); // 0xFE
  serialPort->write(Lenght); //(DataLength + 1) * NumberOfServos + 4
  serialPort->write(SYNC_WRITE); //Instruction 0x83
  serialPort->write(0x1E);
  serialPort->write(READ_POS_LENGTH);

  serialPort->write(servo_ID_1); //Length of data write
  serialPort->write(coxa_pos_l); //First Id
  serialPort->write(coxa_pos_h); //First data write
  serialPort->write(speed_l);
  serialPort->write(speed_h);

  serialPort->write(servo_ID_2); //Length of data write
  serialPort->write(coxa_pos_l); //First Id
  serialPort->write(coxa_pos_h); //First data write
  serialPort->write(speed_l);
  serialPort->write(speed_h);

  serialPort->write(servo_ID_3); //Length of data write
  serialPort->write(coxa_pos_l); //First Id
  serialPort->write(coxa_pos_h); //First data write
  serialPort->write(speed_l);
  serialPort->write(speed_h);

  serialPort->write(servo_ID_4); //Length of data write
  serialPort->write(coxa_pos_l); //First Id
  serialPort->write(coxa_pos_h); //First data write
  serialPort->write(speed_l);
  serialPort->write(speed_h);
  
  serialPort->write(servo_ID_5); //Length of data write
  serialPort->write(femur_pos_l); //First Id
  serialPort->write(femur_pos_h); //First data write
  serialPort->write(speed_l);
  serialPort->write(speed_h);

  serialPort->write(servo_ID_6); //Length of data write
  serialPort->write(femur_pos_l); //First Id
  serialPort->write(femur_pos_h); //First data write
  serialPort->write(speed_l);
  serialPort->write(speed_h);

  serialPort->write(servo_ID_7); //Length of data write
  serialPort->write(femur_pos_l); //First Id
  serialPort->write(femur_pos_h); //First data write
  serialPort->write(speed_l);
  serialPort->write(speed_h);

  serialPort->write(servo_ID_8); //Length of data write
  serialPort->write(femur_pos_l); //First Id
  serialPort->write(femur_pos_h); //First data write
  serialPort->write(speed_l);
  serialPort->write(speed_h);

  serialPort->write(servo_ID_9); //Length of data write
  serialPort->write(tibia_pos_l); //First Id
  serialPort->write(tibia_pos_h); //First data write
  serialPort->write(speed_l);
  serialPort->write(speed_h);

  serialPort->write(servo_ID_10); //Length of data write
  serialPort->write(tibia_pos_l); //First Id
  serialPort->write(tibia_pos_h); //First data write
  serialPort->write(speed_l);
  serialPort->write(speed_h);
  
  serialPort->write(servo_ID_11); //Length of data write
  serialPort->write(tibia_pos_l); //First Id
  serialPort->write(tibia_pos_h); //First data write
  serialPort->write(speed_l);
  serialPort->write(speed_h);

  serialPort->write(servo_ID_12); //Length of data write
  serialPort->write(tibia_pos_l); //First Id
  serialPort->write(tibia_pos_h); //First data write
  serialPort->write(speed_l);
  serialPort->write(speed_h);

  serialPort->write(checksum);

  serialPort->flush();
  digitalWrite(Direction_Pin, RX_MODE);
  return (read_error());
}

int SR518::setPosLimitMin(byte id, double position_angle)
{
  int position = position_angle * POSITION_RESOLUTION_H;

  char pos_h = position >> 8;
  char pos_l = position % 256;
  byte checksum = ~lowByte(id + POSITION_LENGTH + WRITE + MIN_POSITION_L + pos_l + pos_h);

  digitalWrite(Direction_Pin, TX_MODE);
  serialPort->write(START_FLAG);
  serialPort->write(START_FLAG);
  serialPort->write(id);
  serialPort->write(POSITION_LENGTH);
  serialPort->write(WRITE);
  serialPort->write(MIN_POSITION_L);
  serialPort->write(pos_l);
  serialPort->write(pos_h);
  serialPort->write(checksum);
  serialPort->flush();
  digitalWrite(Direction_Pin, RX_MODE);
  return (read_error());
}

int SR518::setPosLimitMax(byte id, double position_angle)
{
  int position = position_angle * POSITION_RESOLUTION_H;
  char pos_h = position >> 8;
  char pos_l = position % 256;
  byte checksum = ~lowByte(id + POSITION_LENGTH + WRITE + MAX_POSITION_L + pos_l + pos_h);

  digitalWrite(Direction_Pin, TX_MODE);
  serialPort->write(START_FLAG);
  serialPort->write(START_FLAG);
  serialPort->write(id);
  serialPort->write(POSITION_LENGTH);
  serialPort->write(WRITE);
  serialPort->write(MAX_POSITION_L);
  serialPort->write(pos_l);
  serialPort->write(pos_h);
  serialPort->write(checksum);
  serialPort->flush();
  digitalWrite(Direction_Pin, RX_MODE);
  return (read_error());
}

int SR518::getTemperature(byte id)
{
  byte checksum = ~lowByte(id + TEMPERATURE_LENGTH + READ + PRESENT_TEMPERATURE + BYTE_READ);

  digitalWrite(Direction_Pin, TX_MODE);
  serialPort->write(START_FLAG);
  serialPort->write(START_FLAG);
  serialPort->write(id);
  serialPort->write(TEMPERATURE_LENGTH);
  serialPort->write(READ);
  serialPort->write(PRESENT_TEMPERATURE);
  serialPort->write(BYTE_READ);
  serialPort->write(checksum);
  serialPort->flush();
  digitalWrite(Direction_Pin, RX_MODE);

  Temperature_Byte = -1;
  Time_Counter = 0;
  while ((serialPort->available() < 6) & (Time_Counter < TIME_OUT))
  {
    Time_Counter++;
    delayMicroseconds(1000);
  }

  while (serialPort->available() > 0)
  {
    if ((serialPort->read() == START_FLAG) & (serialPort->peek() == START_FLAG))
    {
      serialPort->read();                         // Start Bytes
      serialPort->read();                         // Ax-12 ID
      serialPort->read();                         // Length
      if ((Error_Byte = serialPort->read()) != 0) // Error
        return (Error_Byte * (-1));
      Temperature_Byte = serialPort->read(); // Temperature
    }
  }
  return (Temperature_Byte); // Returns the read temperature
}

double SR518::getVoltage(byte id)
{
  byte checksum = ~lowByte(id + VOLTAGE_LENGTH + READ + PRESENT_VOLTAGE + BYTE_READ);

  digitalWrite(Direction_Pin, TX_MODE);
  serialPort->write(START_FLAG);
  serialPort->write(START_FLAG);
  serialPort->write(id);
  serialPort->write(VOLTAGE_LENGTH);
  serialPort->write(READ);
  serialPort->write(PRESENT_VOLTAGE);
  serialPort->write(BYTE_READ);
  serialPort->write(checksum);
  serialPort->flush();
  digitalWrite(Direction_Pin, RX_MODE);

  Voltage_Byte = -1;
  Time_Counter = 0;
  while ((serialPort->available() < 6) & (Time_Counter < TIME_OUT))
  {
    Time_Counter++;
    delayMicroseconds(1000);
  }

  while (serialPort->available() > 0)
  {
    if ((serialPort->read() == START_FLAG) & (serialPort->peek() == START_FLAG))
    {
      serialPort->read();                         // Start Bytes
      serialPort->read();                         // Ax-12 ID
      serialPort->read();                         // Length
      if ((Error_Byte = serialPort->read()) != 0) // Error
        return (Error_Byte * (-1));
      Voltage_Byte = serialPort->read(); // Voltage
    }
  }
  return (double(Voltage_Byte) / 10); // Returns the read temperature
}

double SR518::getPosition(byte id)
{
  byte checksum = ~lowByte(id + READ_POS_LENGTH + READ + PRESENT_POSITION_L + BYTE_READ_POS);

  digitalWrite(Direction_Pin, TX_MODE);
  serialPort->write(START_FLAG);
  serialPort->write(START_FLAG);
  serialPort->write(id);
  serialPort->write(READ_POS_LENGTH);
  serialPort->write(READ);
  serialPort->write(PRESENT_POSITION_L);
  serialPort->write(BYTE_READ_POS);
  serialPort->write(checksum);
  serialPort->flush();
  digitalWrite(Direction_Pin, RX_MODE);

  Position_Long_Byte = -1;
  Time_Counter = 0;
  while ((serialPort->available() < 6) & (Time_Counter < TIME_OUT))
  {
    Time_Counter++;
    delayMicroseconds(1000);
  }

  while (serialPort->available() > 0)
  {
    if ((serialPort->read() == START_FLAG) & (serialPort->peek() == START_FLAG))
    {
      serialPort->read();
      serialPort->read();
      serialPort->read();
      if ((Error_Byte = serialPort->read()) != 0)
        return (Error_Byte * (-1));

      Position_Low_Byte = serialPort->read();
      Position_High_Byte = serialPort->read();
      Position_Long_Byte = Position_High_Byte << 8;
      Position_Long_Byte = Position_Long_Byte + Position_Low_Byte;
    }
  }
  return (double(Position_Long_Byte * POSITION_RESOLUTION_L));
}

double SR518::getCurrentPosition(byte id, double last_position)
{
  byte checksum = ~lowByte(id + READ_POS_LENGTH + READ + PRESENT_POSITION_L + BYTE_READ_POS);

  digitalWrite(Direction_Pin, TX_MODE);
  serialPort->write(START_FLAG);
  serialPort->write(START_FLAG);
  serialPort->write(id);
  serialPort->write(READ_POS_LENGTH);
  serialPort->write(READ);
  serialPort->write(PRESENT_POSITION_L);
  serialPort->write(BYTE_READ_POS);
  serialPort->write(checksum);
  serialPort->flush();
  digitalWrite(Direction_Pin, RX_MODE);

  Position_Long_Byte = -1;
  Time_Counter = 0;
  while ((serialPort->available() < 6) & (Time_Counter < TIME_OUT))
  {
    Time_Counter++;
    delayMicroseconds(1000);
  }

  while (serialPort->available() > 0)
  {
    if ((serialPort->read() == START_FLAG) & (serialPort->peek() == START_FLAG))
    {
      serialPort->read();
      serialPort->read();
      serialPort->read();
      if ((Error_Byte = serialPort->read()) != 0)
        return (Error_Byte * (-1));

      Position_Low_Byte = serialPort->read();
      Position_High_Byte = serialPort->read();
      Position_Long_Byte = Position_High_Byte << 8;
      Position_Long_Byte = Position_Long_Byte + Position_Low_Byte;
    }
  }

  return double(Position_Long_Byte * POSITION_RESOLUTION_L);

  // if ((return_position/last_position) < POSITION_ACCURACY || (last_position/return_position) < POSITION_ACCURACY)
  // {
  //   return (last_position);
  // }
  // else
  // {
  //   return (return_position);
  // }
}

SR518 Hub;
