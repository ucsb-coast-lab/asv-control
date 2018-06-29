#include "Arduino.h"
#include "SoftwareSerial.h"
#include "Adafruit_GPS.h"
#include "info.h"

class GPSComm {
public:
  GPSComm(HardwareSerial*, int);
  Position update();

private:
  void setModes();
  Adafruit_GPS GPS;
};
