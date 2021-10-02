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

std::string format_date(std::string date)
{
    std::string day = date.substr(0, 2);
    std::string month = date.substr(2, 2);
    std::string year = date.substr(4, 2);

    return day + "/" + month + "/" + year;
}

double format_latitude(double latitude)
{
    return latitude / 100.0;
}

double format_longitude(double longitude, std::string orientation)
{
    int sign = orientation == "W" ? -1 : 1;
    return sign * longitude / 100.0;
}

double format_speed(double knots, std::string units)
{
    double speed = knots;

    if (units == "MS")
    {
        speed = knots * KNTOMS;
    }
    else if (units == "KMH")
    {
        speed = knots * KNTOKMH;
    }

    return speed;
}
