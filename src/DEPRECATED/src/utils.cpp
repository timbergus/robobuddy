// Copyright 2018 Gustavo Muñoz

#include "utils.h"

#define KNTOMS 0.514444444
#define KNTOKMH 1.85

void getType(const char *s, char *type) {
  int MAX_SIZE = 6;
  snprintf(type, MAX_SIZE, "%s", s + 1);
}

void split_string_by_comma(const char *s, char *terms[]) {
  const char *pch;
  int pos[15];
  pos[0] = 0;
  int count = 1;
  pch = strchr(s, ',');

  while (pch != NULL) {
    pos[count] = pch - s;
    pch = strchr(pch + 1 * sizeof(char), ',');
    count++;
  }

  char buffer[100];

  int con = 0;

  for (int i = 0; i < count; i++) {
    snprintf(buffer, pos[i + 1] - pos[i], "%s", s + pos[i] + 1);
    terms[con] = strdup(buffer);
    con++;
  }
}

float formatCoordinate(char *s, char *d) {
  float mul = 1.0;
  char degrees[10];
  float f_degrees = 0.0;
  char minutes[10];
  float f_minutes = 0.0;

  int dot = 0;
  const char *pch;

  pch = strchr(s, '.');
  dot = pch - s;

  strncpy(degrees, s, (dot - 2) * sizeof(char));
  degrees[dot - 2] = '\0';
  f_degrees = atof(degrees);

  strncpy(minutes, s + dot - 2, strlen(s) * sizeof(char));
  minutes[strlen(s)] = '\0';
  f_minutes = atof(minutes) / 60.0;

  if (strcmp(d, "S") == 0 || strcmp(d, "W") == 0) {
    mul = -1.0;
  }

  return mul * (f_degrees + f_minutes);
}

char *formatTime(const char *s) {
  char *time = (char *)malloc(9 * sizeof(char));
  char hours[] = "00";
  char minutes[] = "00";
  char seconds[] = "00";

  strncpy(hours, s, 2 * sizeof(char));
  strncpy(minutes, s + 2, 2 * sizeof(char));
  strncpy(seconds, s + 4, 2 * sizeof(char));

  snprintf(time, 9, "%s:%s:%s", hours, minutes, seconds);
  return time;
}

char *formatDate(const char *s) {
  char *date = reinterpret_cast<char *>(malloc(8 * sizeof(char)));
  char day[] = "00";
  char month[] = "00";
  char year[] = "00";

  strncpy(day, s, 2 * sizeof(char));
  strncpy(month, s + 2, 2 * sizeof(char));
  strncpy(year, s + 4, 2 * sizeof(char));

  snprintf(date, 9, "%s/%s/%s", day, month, year);
  return date;
}

float formatSpeed(char *speed, int units) {
  switch (units) {
  case 0:
    return KNTOMS * atof(speed);
  case 1:
    return KNTOKMH * atof(speed);
  default:
    return atof(speed);
  }
}
