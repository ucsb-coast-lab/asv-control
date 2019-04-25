#include "Parser.h"

#include <stdlib.h>
#include <string.h>

bool MOOSMsg::parse(char *msg, Goals& goals)
{
  if (msg[strlen(msg) - 4] == '*') {
    uint16_t sum = parseHex(msg[strlen(msg) - 3]) * 16;
    sum += parseHex(msg[strlen(msg) - 2]);
    for (uint8_t i = 1; i < (strlen(msg)- 4); i++) {
      sum ^= msg[i];
    }
    if (sum != 0) {
      return false;
    }
  }
  if (strstr(msg, "#C,Rudder")) {
    char *p = msg;
    p = strchr(p, ',') + 1; // skips "#C,"
    p = strchr(p, ',') + 1; // skips "Rudder,"
    goals.rudder = atoi(p); // takes value before ",*chksum\n"
    p = strchr(p, ',') + 1; // skips thrustvalue,
    p = strchr(p, ',') + 1; // skips "Thrust,"
    goals.thrust = atoi(p);
    return true;
  }
  return false;
}

uint8_t MOOSMsg::parseHex(char c)
{
  uint8_t val;
  if (c <= '9') {
    val = c - '0';
  } else if (c <= 'F') {
    val = (c - 'A') + 10;
  } else {
    val = 0;
  }
  return val;
}
