#include "RPiComm.h"

int RPiComm::getDesiredRudder();
int RPiComm::getDesiredThrust();

void RPiComm::postAll();
void RPiComm::postNavLat(int);
void RPiComm::postNavLon(int);
void RPiComm::postNavX(int);
void RPiComm::postNavY(int);
void RPiComm::postNavSpeed(int);
void RPiComm::postNavHeading(int);
