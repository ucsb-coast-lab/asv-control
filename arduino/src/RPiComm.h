#include "Arduino.h"
#include "info.h"

class RPiComm {
public:
  RPiComm(HardwareSerial*, int);

  int getDesiredRudder();
  int getDesiredThrust();
  Goals currentGoals();

  char readChar();
  bool isNewMail();
  char* newMail();

  void postAll(Position, Momentum);

private:
  String appendChecksum(String msg);
  double toXCoord(double lon);
  double toYCoord(double lat);

  static const int buflen = 120;

  HardwareSerial* ser;
  int idx = 0;
  char buffA[buflen] = {};
  char buffB[buflen] = {};
  char *lastMessage = buffA;
  char *currMessage = buffB;
  bool newMail = false;

  int desiredRudder;
  int desiredThrust;
};
