#include "RPiComm.h"

RPiComm::RPiComm(HardwareSerial* s, int baud):
  ser(s)
{
  this->ser->begin(baud);
}

char RPiComm::readChar()
{
  char c = 0;
  if (ser->available()) {
    c = ser->read();
    if (c = '\n') {
      currMessage[idx] = 0;
      if (currMessage == buffA) {
        currMessage = buffB;
        lastMessage = buffA;
      } else {
        currMessage = buffA;
        lastMessage = buffB;
      }
      idx = 0;
      newMail = true;
    }
    currMessage[idx++] = c;
    if (idx >= buflen)
      idx = buflen - 1;
  }
  return c;
}

bool RPiComm::isNewMail()
{
  return newMail;
}

char* RPiComm::newMail()
{
  newMail = false;
  return lastMessage;
}

int RPiComm::getDesiredRudder() {
  return desiredRudder;
}

int RPiComm::getDesiredThrust() {
  return desiredThrust;
}

void RPiComm::postAll(Position pos, Momentum mom) {
  String msg = "#N,T" + String(millis()) + \
    ",LAT" + String(pos.lat, 5) + \
    ",LON" + String(pos.lon, 5) + \
    ",NAE" + String(toXCoord(pos.x), 1) + \
    ",NAN" + String(toYCoord(pos.y), 1) + \
    ",VEL" + String(mom.speed) + \
    ",HDG" + String(mom.direction, 1);

  msg = appendChecksum(msg);
  Serial.print(msg);
  ser->print(msg);
}

String RPiComm::appendChecksum(String msg){
  uint16_t sum = 0;
  for (uint8_t i = 1; i < (msg.length()); i++) {
    sum ^= msg[i];
  }
  return msg + "*" + String(sum, HEX) + "\n";
}


// void RPiComm::postNavLat(int);
// void RPiComm::postNavLon(int);
// void RPiComm::postNavX(int);
// void RPiComm::postNavY(int);
// void RPiComm::postNavSpeed(int);
// void RPiComm::postNavHeading(int);
