#include <iostream>

#include "functions.h"

int main()
{
    // blink(20, 1);

    // read_sample_file("./src/data/samples.txt");
    
    int samples = 20000;
    
    std::cout << "Reading " <<  samples << " GPS samples." << std::endl;

    read_gps(samples);

    return EXIT_SUCCESS;
}
