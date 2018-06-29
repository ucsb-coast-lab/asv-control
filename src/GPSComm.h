#include "Arduino.h"
#include "SoftwareSerial.h"
#include "Adafruit_GPS.h"
#include "info.h"

class GPSComm {
public:
  // TODO: Test GPSComm(HardwareSerial*, int)
  // TODO: Refactor GPSComm(HardwareSerial*, int)
  GPSComm(HardwareSerial*, int);
  // TODO: implement update()
  Position update();

private:
  // TODO: Refactor setModes()
  void setModes();
  Adafruit_GPS GPS;
};
