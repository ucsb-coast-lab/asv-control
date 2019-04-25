#include "Arduino.h"
#include "info.h"
// TODO: Add include statements for all relevant Adafruit Devices
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include <Adafruit_L3GD20_U.h>

class IMUComm {
public:
  // TODO: Implement IMUComm(int, int)
  IMUComm(int, int);
  // TODO: Implement update();
  // TODO: Embed Madgwick Filter into update
  Momentum update();

private:
  // TODO: Figure out what those magic numbers are
  Adafruit_LSM303_Accel_Unified  accel = Adafruit_LSM303_Accel_Unified(30301);
  Adafruit_LSM303_Mag_Unified    mag   = Adafruit_LSM303_Mag_Unified(30302);
  Adafruit_L3GD20_Unified        gyro  = Adafruit_L3GD20_Unified(20);
  // TODO: Implement a Madgwick Filter class
  // TODO: Add a Momemtum object for bookkeeping
};
