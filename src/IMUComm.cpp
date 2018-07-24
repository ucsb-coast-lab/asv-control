#include "IMUComm.h"

IMUComm::IMUComm(int dataPin, int clockPin) {
  Serial.println("IMU: Initializing");

  bool success = true;

  if(!accel.begin()) {
    Serial.println("IMU: No accelerometer");
    success = false;
  }

  if(!mag.begin()) {
    Serial.println("IMU: No magnetometer");
    success = false;
  }

  if(!gyro.begin()) {
    Serial.println("IMU: No gyroscope");
    success = false;
  }

  if(success) {
    Serial.println("IMU: Fully initialized.");
  } else {
    Serial.println("IMU: Not fully initialized");
  }
}

Momentum IMUComm::update() {

  sensors_event_t evt;

  accel.getEvent(&evt);
  A[0][bufInd] = (double)map(imu.acceleration.x * 100, AXM, AXP, -981, 981) / 100;
  A[1][bufInd] = (double)map(imu.acceleration.y * 100, AYM, AYP, -981, 981) / 100;
  A[2][bufInd] = (double)map(imu.acceleration.z * 100, AZM, AZP, -981, 981) / 100;

  mag.getEvent(&imu);
  // Handle bad mag readings
  if (imu.magnetic.x == 0) {
    int lastGood = bufInd - 1;
    M[0][bufInd] = M[0][lastGood];
    M[1][bufInd] = M[1][lastGood];
    M[2][bufInd] = M[2][lastGood];
  } else {
    M[0][bufInd] = MXS * (imu.magnetic.x - MXB);
    M[1][bufInd] = MYS * (imu.magnetic.y - MYB);
    M[2][bufInd] = MZS * (imu.magnetic.z - MZB);
  }

  gyro.getEvent(&imu);
  G[0][bufInd] = imu.gyro.x;
  G[1][bufInd] = imu.gyro.y;
  G[2][bufInd] = imu.gyro.z;

  bufInd++;
  if (bufInd == win)
    bufInd = 0;

  // Zero sum counter
  for (int i = 0; i < 3; i++) {
    Abar[i] = 0;
    Mbar[i] = 0;
    Gbar[i] = 0;
  }

  // Add fractional readings to form an average
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < win; j++) {
      Abar[i] += A[i][j] / win;
      Mbar[i] += M[i][j] / win;
      Gbar[i] += G[i][j] / win;
    }
  }
}
