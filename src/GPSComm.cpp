#include "Arduino.h"
#include "GPSComm.h"
#include "Adafruit_GPS.h"

#define PMTK_SET_NAVSPEED_THRESHOLD_20CMS "$PMTK386,0.2*3F"
#define PMTK_SET_NAVSPEED_THRESHOLD_40CMS "$PMTK386,0.4*39"
#define PMTK_SET_NAV_ACK "$PMTK001,386,3*3D"
#define PMTK_Q_NAV_THRESHOLD "$PMTK447*35"

GPSComm::GPSComm(HardwareSerial* ser, int baud) {
  Serial.println("GPS: Initializing.");
  this->GPS = Adafruit_GPS(ser);
  this->GPS.begin(baud);
  setModes();
  Serial.println("GPS: Initialized.");
}

void GPSComm::setModes() {
  this->GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  this->GPS.sendCommand(PMTK_SET_NMEA_UPDATE_5HZ);
  Serial.println("GPS: Set echo rate.");

  this->GPS.sendCommand(PMTK_API_SET_FIX_CTL_1HZ);
  Serial.println("GPS: Set update rate");

  this->GPS.sendCommand(PMTK_SET_NAVSPEED_THRESHOLD_40CMS);
  if (this->GPS.waitForSentence(PMTK_SET_NAV_ACK))
    Serial.println("GPS: NAVSPEED set.");
  else
    Serial.println("GPS: NAVSPEED set FAILED.");

  this->GPS.sendCommand(PMTK_Q_NAV_THRESHOLD);
  if (this->GPS.waitForSentence("$PMTK527"))
    Serial.println(this->GPS.lastNMEA());

  this->GPS.sendCommand(PGCMD_NOANTENNA); // OFF
  //GPS.sendCommand(PGCMD_ANTENNA); // ON
}

struct Position GPSComm::update() {

  // TODO: Find out what this snippet does
  if (GPS.newNMEAreceived()) {
    GPS.parse(GPS.lastNMEA())
  }

  position.lat = GPS.latitudeDegrees;
  position.lon = GPS.longitudeDegrees;

  return position;
}
