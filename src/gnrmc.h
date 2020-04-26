#ifndef _GNRMC_H_
#define _GNRMC_H_

#include <iostream>
#include <string>
#include <vector>

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

#endif // _GNRMC_H_
