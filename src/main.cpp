#include <fstream>
#include <chrono>
#include <thread>
#include <robotcontrol.h>

#include "gnrmc.h"

#define BUS 2
#define BUS_SIZE 128
#define TIMEOUT_S 0.5
#define BAUDRATE 9600

/* void blink_led(rc_led_t LED, int duration)
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
} */

/* void readSampleFile(std::string path)
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
} */

void readGPS()
{
    int ret;
    GNRMC coords;

    uint8_t buf[BUS_SIZE];

    if (rc_uart_init(BUS, BAUDRATE, TIMEOUT_S, 0, 1, 0))
    {
        std::cout << "Failed to init UART" << BUS << std::endl;
    }

    while (true)
    {
        ret = rc_uart_read_line(BUS, buf, sizeof(buf));

        if (ret >= 0)
        {
            std::string line = (char *)buf;

            if (line.substr(0, 6) == coords.id)
            {
                coords.parser(line);
                coords.render();
            }
        }
    }

    rc_uart_close(BUS);
}

int main()
{
    // blink(20, 1);

    // readSampleFile("./src/samples.txt");

    readGPS();

    return 0;
}
