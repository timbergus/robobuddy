// functions.h

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <fstream>
#include <chrono>
#include <thread>
#include <string>
#include <fstream>
#include <ctime>

#include <robotcontrol.h>

#include "gnrmc.h"
#include "board.h"

#define BUS 2
#define BUS_SIZE 1024
#define TIMEOUT_S 0.5
#define BAUDRATE 9600

void blink_led(rc_led_t, int);
void blink(int, int);
void read_sample_file(std::string);
// void read_gps();
void read_gps_message(int port);

// GPS Functions

void read_gps(int);

void blink_led(rc_led_t LED, int duration)
{
  rc_led_set(LED, 1);
  rc_usleep(duration * 100000);
  rc_led_set(LED, 0);
}

void blink(int times, int duration)
{
  for (int i = 0; i < times; i++)
  {
    blink_led(RC_LED_GREEN, duration);
    blink_led(RC_LED_RED, duration);
  }
}

void read_sample_file(std::string path)
{
  std::string line;
  std::ifstream file(path);
  GNRMC coords;

  if (!file)
  {
    std::cout << "File not found." << std::endl;
  }

  while (std::getline(file, line))
  {
    coords.parser(line);
    coords.render();
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }

  file.close();
}

// https://www.pluralsight.com/blog/software-development/how-to-measure-execution-time-intervals-in-c--

void read_gps(int samples)
{
  auto start = std::chrono::high_resolution_clock::now();

  time_t now = time(0);

  Board::options_t options;

  options.gps_port = 2;
  options.gps_baudrate = 9600;

  Board board(options);

  std::string file_name("./src/data/" + std::to_string(now) + ".txt");

  std::ofstream file(file_name);

  board.gps_init();

  for (int i = 0; i < samples; i++)
  {
    file << board.gps_read();
  }

  board.gps_close();
  file.close();

  auto finish = std::chrono::high_resolution_clock::now();

  std::chrono::duration<double> elapsed = finish - start;

  std::cout << "Elapsed time: " << elapsed.count() << " s\n";
}

#endif // FUNCTIONS_H
