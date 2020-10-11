#include "mbed.h"

int main()
{
    // Initialise the digital pin LED1 as an output
    DigitalOut led(LED1);

    while (true)
    {
        led = !led;
        wait_us(1000000/1);
    }
}