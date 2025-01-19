#include <stdint.h>
#include "nrf_gpio.h"

static void sleep(unsigned long sleep_time)
{
    while (sleep_time--)
        __asm__("nop");
}

static void gpio_init(void)
{
    // Configure LED_PIN_1 as output
    NRF_P0->DIR |= (1 << 21);
    // Configure LED_PIN_2 as output
    NRF_P0->DIR |= (1 << 28);
}

int main(void)
{
    gpio_init();
    while (1) {
        NRF_P0->OUTSET = (1 << 21);
        NRF_P0->OUTCLR = (1 << 28);
        sleep(1000000);

        NRF_P0->OUTCLR = (1 << 21);
        NRF_P0->OUTSET = (1 << 28);
        sleep(1000000);
    }

    return 0;
}
