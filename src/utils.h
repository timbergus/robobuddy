#ifndef _UTILS_H_
#define _UTILS_H_

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#define KNTOMS 0.514444444
#define KNTOKMH 1.85

void split_string(std::string &, std::vector<std::string> &);

std::string format_time(std::string);
std::string format_date(std::string);

double format_latitude(double);
double format_longitude(double, std::string);

double format_speed(double, std::string);

#endif // _UTILS_H_
