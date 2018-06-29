#include "Arduino.h"
#include "GPSComm.h"

#define PMTK_SET_NAVSPEED_THRESHOLD_20CMS "$PMTK386,0.2*3F"
#define PMTK_SET_NAVSPEED_THRESHOLD_40CMS "$PMTK386,0.4*39"
#define PMTK_SET_NAV_ACK "$PMTK001,386,3*3D"
#define PMTK_Q_NAV_THRESHOLD "$PMTK447*35"

GPSComm::GPSComm(HardwareSerial* ser, int baud) {
  Serial.println("GPS: Initializing.");
  GPS = Adafruit_GPS(ser);
  setModes();
  GPS.begin(baud);
  Serial.println("GPS: Initialized.");
}

void GPSComm::setModes() {
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_5HZ);
  Serial.println("GPS: Set echo rate.");

  GPS.sendCommand(PMTK_API_SET_FIX_CTL_1HZ);
  Serial.println("GPS: Set update rate");

  GPS.sendCommand(PMTK_SET_NAVSPEED_THRESHOLD_40CMS);
  if (GPS.waitForSentence(PMTK_SET_NAV_ACK))
    Serial.println("GPS: NAVSPEED set.");
  else
    Serial.println("GPS: NAVSPEED set FAILED.");

  GPS.sendCommand(PMTK_Q_NAV_THRESHOLD);
  if (GPS.waitForSentence("$PMTK527"))
    Serial.println(GPS.lastNMEA());

  GPS.sendCommand(PGCMD_NOANTENNA); // OFF
  //GPS.sendCommand(PGCMD_ANTENNA); // ON
}

struct Position GPSComm::update() {
  
}
