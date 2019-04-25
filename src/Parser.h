#ifndef PARSER_H
#define PARSER_H

#include <stdint.h>

#include "info.h"

namespace MOOSMsg {
  Goals parse(char *msg);
  uint8_t parseHex(char c);
}

#endif
