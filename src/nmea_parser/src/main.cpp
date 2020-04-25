// Copyright 2018 Gustavo Muñoz

#include "parsers/gnrmc.h"

int main() {
  GNRMC gnrmc;

  FILE *file =
    fopen("/var/lib/cloud9/projects/nmea-parser/src/samples.txt", "r");

  if (file == NULL) {
    return 1;
  }

  char line[256];
  char type[] = "GNRMC";

  while (fgets(line, sizeof(line), file) != NULL) {
    getType(line, type);
    if (gnrmc.is_valid_string(line) && strcmp(type, "GNRMC") == 0) {
      gnrmc.parse(line);
      printf("Lat: %f\t", gnrmc.getLatitude());
      printf("Lng: %f\t", gnrmc.getLongitude());
      printf("Time: %s\t", gnrmc.getTime());
      printf("Date: %s\t", gnrmc.getDate());
      printf("Speed: %f km/h\n", gnrmc.getSpeed());
      
      usleep(1000000);
    }
  }

  return 0;
}
