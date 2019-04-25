/*
 * rcProto
 * main.cpp
 *
 * The main file for an Arduino interface between
 * a Raspberry Pi Model 3 and a suite of sensors
 * and actuators
 *
 * Coastal Oceanography and Autonomous Systems Laboratory
 * University of California, Santa Barbara
 */

#include <Arduino.h>

#include "info.h"
#include "RPiComm.h"
#include "IMUComm.h"
#include "GPSComm.h"
#include "CarComm.h"

// I2C pins: IMU
#define SDA 20
#define SCL 21

// PWM pins: ESC, Steering
#define ESC 2
#define STR 3

// Devices
RPiComm* pRPi;
GPSComm* pGPS;
IMUComm* pIMU;
CarComm* pCar;

void setup() {
  // Logging to computer
  Serial.begin(115200);

  pRPi = new RPiComm(&Serial1, 115200);
  // TODO: implement "GPSComm(HardwareSerial, int)"
  pGPS = new GPSComm(&Serial2, 9600);
  // TODO: implement "IMUComm(int, int)"
  pIMU = new IMUComm(SDA, SCL);
  // TODO: implement "CarComm(int, int)"
  pCar = new CarComm(ESC, STR);

  delay(100);

  // Set up interrupts on Timer 0
  OCR0A = 0xAF;
  TIMSK0 |= _BV(OCR0A);
}

SIGNAL(TIMER0_COMPA_vect) {
  // Interrupt is called once a millisecond,
  // looks for new serial data, and stores it
  char c = pRPi->readChar();
  //char g = GPS.read();3
}

Position pos;
Momentum mom;
Goals goals;

void loop() {
  // TODO: test "Position GPSComm::update()"
  //
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  // TODO: !!! Speed and Heading are from GPS !!! Refactor accordingly
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  //format send to MOOS:
  //#N,T12345,LAT12.34567,LON12.34567,NAVE12.34,NAVN12.34,V1.23,H123.4,HDOP1.23*99
  pos = pGPS->update();
  // TODO: implement "Momentum IMUComm::update()"
  ine = pIMU->update();

  // TODO: implement "void RPiComm::postAll(Position, Momentum)"
  pRPi->postAll(pos, mom);

  if (pRPi->isNewMail()) {
    char *newMail = pRPi->newMail();
    parse(newMail, goals);
  }

  // TODO: implement "void CarComm::command(Goals)"
  Car.command(goals);
}
