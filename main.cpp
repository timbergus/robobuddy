#include <iostream>
#include <robotcontrol.h>

#define BUS 2
#define BUS_SIZE 128
#define TIMEOUT_S 0.5
#define BAUDRATE 9600

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

int main()
{
    // blink(20, 1);

    int ret;

    uint8_t buf[BUS_SIZE];

    if (rc_uart_init(BUS, BAUDRATE, TIMEOUT_S, 0, 1, 0))
    {
        std::cout << "Failed to init UART" << BUS << std::endl;
        return -1;
    }

    rc_uart_flush(BUS);

    for (int i = 0; i < 100; i++)
    {
        ret = rc_uart_read_line(BUS, buf, sizeof(buf));

        if (ret < 0)
        {
            std::cout << "Error reading bus." << std::endl;
        }
        else if (ret == 0)
        {
            std::cout << "Timeout reached, " << ret << " bytes readed." << std::endl;
        }
        else
        {
            std::cout << buf << std::endl;
        }

        memset(buf, 0, sizeof(buf));
    }

    rc_uart_close(BUS);

    return 0;
}
