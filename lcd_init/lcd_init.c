#include "bcm2835.h"
#include <stdint.h>
#include <stdio.h>

const uint8_t gpio_pin_cs	= 36;	// Define pins here as a const. TODO: variable pins based on cmdline arguments?
const uint8_t gpio_pin_clk	= 39;
const uint8_t gpio_pin_mosi	= 38;
const uint8_t gpio_pin_rst  = 42;

int main(void) 
{
    return 0;
}

