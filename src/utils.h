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

double format_latitude(std::string);
double format_longitude(std::string, std::string);

double format_speed(std::string, std::string);

void show_results(std::vector<std::string> &, std::string);

#endif // _UTILS_H_
