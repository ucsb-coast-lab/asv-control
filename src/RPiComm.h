#include "Arduino.h"
#include "info.h"

// TODO: Abstract this
class RPiComm {
public:
  RPiComm(HardwareSerial*, int);


  // TODO: Implement reading MOOS messages
  int getDesiredRudder();
  int getDesiredThrust();
  Goals updateGoals();

  void postAll(Position, Momentum);

  // TODO: Implement individual posts
  // void postNavLat(int);
  // void postNavLon(int);
  // void postNavX(int);
  // void postNavY(int);
  // void postNavSpeed(int);
  // void postNavHeading(int);

private:
  String appendChecksum(String msg);
  double toXCoord(double lon);
  double toYCoord(double lat)

  // TODO: Implement Parser class
  // TODO: Add Parser object
  HardwareSerial* ser;
  int desiredRudder;
  int desiredThrust;
};
