#include "Arduino.h"
#include "info.h"
// TODO: Add include statements for all relevant Adafruit Devices

class IMUComm {
public:
  // TODO: Implement IMUComm(int, int)
  IMUComm(int, int);
  // TODO: Implement update();
  // TODO: Embed Madgwick Filter into update
  Momentum update();

private
  // TODO: Add all relevant Adafruit Devices (see GPSComm.h for example)
  // TODO: Implement a Madgwick Filter class
  // TODO: Add a Momemtum object for bookkeeping
};
