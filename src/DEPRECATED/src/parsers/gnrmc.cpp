// Copyright 2018 Gustavo Muñoz

#include "gnrmc.h"

int GNRMC::is_valid_string(const char *s) {
  if (s[0] == '$') {
    return 1;
  } else {
    return 0;
  }
}

void GNRMC::parse(const char *s) {
  split_string_by_comma(s, this->terms);
}

float GNRMC::getLatitude() {
  return formatCoordinate(this->terms[3], this->terms[4]);
}

float GNRMC::getLongitude() {
  return formatCoordinate(this->terms[5], this->terms[6]);
}

char *GNRMC::getTime() {
  return formatTime(this->terms[1]);
}

char *GNRMC::getDate() {
  return formatDate(this->terms[9]);
}

float GNRMC::getSpeed() {
  return formatSpeed(this->terms[7], 1);
}
