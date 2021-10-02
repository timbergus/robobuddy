#include <iostream>

#include "functions.h"

int main()
{
    // blink(20, 1);

    // read_sample_file("./src/data/samples.txt");
    
    std::cout << "Reading GPS." << std::endl;

    read_gps();

    return EXIT_SUCCESS;
}
