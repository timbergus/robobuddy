#include <iostream>

// #include "functions.h"
#include "gps.h"

int main()
{
  // Testing the board.
  
  /* blink(20, 1); */
  
  // Reading n samples from the GPS.

  /* int samples = 1000;

  std::cout << "Reading " << samples << " GPS samples." << std::endl;

  read_gps(samples); */
  
  // Reading back the samples stored.
  
  // read_sample_file("./src/data/samples.txt");
  
  GPS gps;

  gps.get_data_stream("./src/data/samples.txt", [&gps](std::string sample)
  {
    if (sample.substr(1, 5) == "GNRMC") {
      gps.parse_sample(sample);
    }
  });

  return EXIT_SUCCESS;
}
