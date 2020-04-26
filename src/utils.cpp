#include "utils.h"

void split_string(std::string &line, std::vector<std::string> &parts)
{
    std::stringstream s_stream(line);

    while (s_stream.good())
    {
        std::string substr;
        getline(s_stream, substr, ',');
        parts.push_back(substr);
    }
}

std::string format_time(std::string time)
{
    std::string hours = time.substr(0, 2);
    std::string minutes = time.substr(2, 2);
    std::string seconds = time.substr(4, 2);

    return hours + ":" + minutes + ":" + seconds;
}

std::string format_date(std::string time)
{
    std::string day = time.substr(0, 2);
    std::string month = time.substr(2, 2);
    std::string year = std::to_string(2000 + std::stoi(time.substr(4, 2)));

    return day + "/" + month + "/" + year;
}

double format_latitude(std::string latitude)
{
    double lat = std::stod(latitude);
    return lat / 100.0;
}

double format_longitude(std::string longitude, std::string orientation)
{
    int sign = orientation == "W" ? -1 : 1;
    double lng = std::stod(longitude);
    return sign * lng / 100.0;
}

double format_speed(std::string speed, std::string units)
{
    double knots = std::stod(speed);
    double sp = knots;

    if (units == "MS")
    {
        sp = knots * KNTOMS;
    }
    else if (units == "KMH")
    {
        sp = knots * KNTOKMH;
    }

    return sp;
}

void show_results(std::vector<std::string> &parts, std::string type)
{
    if (parts.at(0) == type)
    {
        std::cout << format_time(parts.at(1)) << "\t";
        std::cout << format_date(parts.at(9)) << "\t";
        std::cout << format_latitude(parts.at(3)) << "\t\t";
        std::cout << format_longitude(parts.at(5), parts.at(6)) << "\t";
        std::cout << format_speed(parts.at(7), "MS") << std::endl;
    }
}
