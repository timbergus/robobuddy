// gnrmc.h

#ifndef GNRMC_H
#define GNRMC_H

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

#include "utils.h"

class GNRMC
{
public:
  std::string id = "$GNRMC";

  GNRMC();
  GNRMC(std::string &);

  void parser(std::string &);
  void render();

private:
  std::string time;
  std::string date;
  double latitude;
  double longitude;
  std::string orientation;
  double speed;
};

GNRMC::GNRMC()
{
  time = "";
  date = "";
  latitude = 0.0;
  longitude = 0.0;
  orientation = "";
  speed = 0.0;
}

GNRMC::GNRMC(std::string &sample)
{
  parser(sample);
}

void GNRMC::parser(std::string &sample)
{
  std::vector<std::string> parts;

  split_string(sample, parts);

  if (parts.at(1).size() >= 6)
  {
    time = parts.at(1);
  }
  else
  {
    time = "000000";
  }

  if (parts.at(9).size() >= 6)
  {
    date = parts.at(9);
  }
  else
  {
    date = "000000";
  }

  if (!parts.at(3).empty())
  {
    latitude = std::stod(parts.at(3));
  }
  else
  {
    latitude = 0.0;
  }

  if (!parts.at(5).empty())
  {
    longitude = std::stod(parts.at(5));
  }
  else
  {
    longitude = 0.0;
  }

  orientation = parts.at(6);

  if (!parts.at(7).empty())
  {
    speed = std::stod(parts.at(7));
  }
  else
  {
    speed = 0.0;
  }
}

void GNRMC::render()
{
  std::cout << std::setw(10);
  std::string units = "MS";
  std::string label = units == "MS" ? "m/s" : "km/h";

  std::cout << format_date(date) << "(" << format_time(time) << ")";
  std::cout << "Lat: " << format_latitude(latitude);
  std::cout << "Lng: " << format_longitude(longitude, orientation);
  std::cout << "Speed: " << format_speed(speed, units) << label << std::endl;
}

#endif // GNRMC_H
