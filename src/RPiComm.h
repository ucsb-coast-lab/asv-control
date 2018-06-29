#include "Arduino.h"
#include "info.h"

class RPiComm {
public:
  RPiComm(HardwareSerial*, int);


  // TODO: Implement reading MOOS messages
  int getDesiredRudder();
  int getDesiredThrust();

  void postAll(Position, Momentum);

  // TODO: Implement individual posts
  // void postNavLat(int);
  // void postNavLon(int);
  // void postNavX(int);
  // void postNavY(int);
  // void postNavSpeed(int);
  // void postNavHeading(int);

private:
  String RPiComm::appendChecksum(String msg);

  HardwareSerial* ser;
  int desiredRudder;
  int desiredThrust;
};
