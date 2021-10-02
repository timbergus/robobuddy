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
int gps_init(const char *);
std::string gps_read(int);
void gps_close(int);

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

/* void read_gps()
{
    GNRMC coords;
    
    uint8_t buf[BUS_SIZE];
    
    time_t now = time(0);
    
    std::string file_name("./src/data/" + std::to_string(now) + ".txt");
    
    std::ofstream file(file_name);
    
    int samples{50};

    if (rc_uart_init(BUS, BAUDRATE, TIMEOUT_S, 0, 1, 0) < 0)
    {
        std::cout << "Failed to init UART" << BUS << std::endl;
    }

    while (samples > 0)
    {
        rc_uart_flush(BUS);
        
        if (rc_uart_read_line(BUS, buf, sizeof buf) > -1)
        {
            std::string line = (char *)buf;
            
            // std::cout << line << std::endl;
            // std::cout << "---------------------------------------" << std::endl;
            
            // std::cout << line.find("$") << "|" << line.find("*") << std::endl;

            if (line.find("$") == 0 && line.find("\n") > 0)
            {
                file << "--------- Positions: " << line.find("$") << "|" << line.find("*") << std::endl;
                file << buf << std::endl;
                file << "---------------------------------------" << std::endl;
                samples--;
            }
        }
    }
    
    file.close();

    rc_uart_close(BUS);
} */

#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

// https://blog.mbedded.ninja/programming/operating-systems/linux/linux-serial-ports-using-c-cpp

int gps_init(const char *port_name)
{
    int port = open(port_name, O_RDWR);
    
    struct termios tty;
    
    if(tcgetattr(port, &tty) != 0) {
        printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
    }
    
    cfsetispeed(&tty, B9600);
    cfsetospeed(&tty, B9600);
    
    if (tcsetattr(port, TCSANOW, &tty) != 0) {
        printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
    }
    
    return port;
}

std::string gps_read(int port)
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

void gps_close(int port)
{
    close(port);
}

// https://www.pluralsight.com/blog/software-development/how-to-measure-execution-time-intervals-in-c--

void read_gps(int samples)
{
    auto start = std::chrono::high_resolution_clock::now();
    
    time_t now = time(0);
    
    std::string file_name("./src/data/" + std::to_string(now) + ".txt");
    
    std::ofstream file(file_name);
    
    int serial_port = gps_init("/dev/ttyO2");
    
    for (int i = 0; i < samples; i++)
    {
      file << gps_read(serial_port);
    }
    
    gps_close(serial_port);
    file.close();
    
    auto finish = std::chrono::high_resolution_clock::now();
    
    std::chrono::duration<double> elapsed = finish - start;
    
    std::cout << "Elapsed time: " << elapsed.count() << " s\n";
}

#endif // FUNCTIONS_H
