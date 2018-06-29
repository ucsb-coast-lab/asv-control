#include "Arduino.h"
#include "info.h"

class RPiComm {
public:
  RPiComm() {
    ser = 0;
    desiredRudder = 0;
    desiredThrust = 0;
  }

  void attach(HardwareSerial*, int);

  int getDesiredRudder();
  int getDesiredThrust();

  void postAll(struct Position, struct Inertia);
  void postNavLat(int);
  void postNavLon(int);
  void postNavX(int);
  void postNavY(int);
  void postNavSpeed(int);
  void postNavHeading(int);

private:
  HardwareSerial* ser;

  int desiredRudder;
  int desiredThrust;
};
