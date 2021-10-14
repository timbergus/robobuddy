// board.h

#ifndef BOARD_H
#define BOARD_H

#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <map>

#include <robotcontrol.h>

// https://blog.mbedded.ninja/programming/operating-systems/linux/linux-serial-ports-using-c-cpp

namespace brd
{
  struct board_options
  {
    int gps_port;
    int gps_baudrate;
  };
}

class Board
{
private:
  int port;
  struct termios tty;
  brd::board_options options;
  std::map<int, speed_t> baudrates = {
      {9600, B9600},
      {19200, B19200},
      {38400, B38400},
      {57600, B57600},
      {115200, B115200},
  };

public:
  Board(brd::board_options);
  ~Board();

  void gps_init();
  std::string gps_read();
  void gps_close();
};

Board::Board(brd::board_options options)
{
  this->options = options;
  char port_name[50];
  sprintf(port_name, "/dev/ttyO%d", options.gps_port);
  port = open(port_name, O_RDWR);
}

Board::~Board()
{
}

void Board::gps_init()
{
  if (tcgetattr(port, &tty) != 0)
  {
    printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
  }

  cfsetispeed(&tty, baudrates[options.gps_baudrate]);
  cfsetospeed(&tty, baudrates[options.gps_baudrate]);

  if (tcsetattr(port, TCSANOW, &tty) != 0)
  {
    printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
  }
}

std::string Board::gps_read()
{
  std::string message;

  char c = '\0';

  read(port, &c, 1);

  message += c;

  while (c != '\n')
  {
    read(port, &c, 1);
    message += c;
  }

  return message;
}

void Board::gps_close()
{
  close(port);
}

#endif // BOARD_H
