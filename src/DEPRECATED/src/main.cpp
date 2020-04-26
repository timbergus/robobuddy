// Copyright 2018 Gustavo Muñoz

#include <iostream>
#include "parsers/gnrmc.h"

int main()
{
  GNRMC gnrmc;

  FILE *file = fopen("./src/samples.txt", "r");

  if (file == NULL)
  {
    std::cout << "File not found." << std::endl;
    return 1;
  }

  char line[256];
  char type[] = "GNRMC";

  while (fgets(line, sizeof(line), file) != NULL)
  {
    getType(line, type);

    if (gnrmc.is_valid_string(line) && strcmp(type, "GNRMC") == 0)
    {
      gnrmc.parse(line);

      std::cout << "Lat: " << gnrmc.getLatitude() << "\t";
      std::cout << "Lng: " << gnrmc.getLongitude() << "\t";
      std::cout << "Time: " << gnrmc.getTime() << "\t";
      std::cout << "Date: " << gnrmc.getDate() << "\t";
      std::cout << "Speed: " << gnrmc.getSpeed() << "km/h" << std::endl;

      usleep(1000000);
    }
  }

  return 0;
}
