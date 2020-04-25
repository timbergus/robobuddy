// Copyright 2018 Gustavo Muñoz

#ifndef _USERS_GUSTAVO_DROPBOX_PROJECTS_C_NMEA_PARSER_SRC_UTILS_H_
#define _USERS_GUSTAVO_DROPBOX_PROJECTS_C_NMEA_PARSER_SRC_UTILS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void getType(const char *s, char *type);
void split_string_by_comma(const char *s, char *terms[]);
float formatCoordinate(char *s, char *d);
char *formatTime(const char *s);
char *formatDate(const char *s);
float formatSpeed(char *speed, int units);

#endif  // _USERS_GUSTAVO_DROPBOX_PROJECTS_C_NMEA_PARSER_SRC_UTILS_H_
