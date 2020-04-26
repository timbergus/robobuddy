#include "gnrmc.h"
#include "utils.h"

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

    time = parts.at(1);
    date = parts.at(9);
    latitude = std::stod(parts.at(3));
    longitude = std::stod(parts.at(5));
    orientation = parts.at(6);
    speed = std::stod(parts.at(7));
}

void GNRMC::render()
{
    std::cout << format_time(time) << "\t";
    std::cout << format_date(date) << "\t";
    std::cout << format_latitude(latitude) << "\t\t";
    std::cout << format_longitude(longitude, orientation) << "\t";
    std::cout << format_speed(speed, "MS") << std::endl;
}
