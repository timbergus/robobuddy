// Copyright 2018 Gustavo Muñoz

#ifndef _USERS_GUSTAVO_DROPBOX_PROJECTS_C_NMEA_PARSER_SRC_PARSERS_GNRMC_H_
#define _USERS_GUSTAVO_DROPBOX_PROJECTS_C_NMEA_PARSER_SRC_PARSERS_GNRMC_H_

#include "../utils.h"

class GNRMC {
 public:
  char type[6];
  char *terms[20];
 public:
  int is_valid_string(const char *s);
  void parse(const char *s);
  float getLatitude();
  float getLongitude();
  char *getTime();
  char *getDate();
  float getSpeed();
};

#endif  // _USERS_GUSTAVO_DROPBOX_PROJECTS_C_NMEA_PARSER_SRC_PARSERS_GNRMC_H_
