#include "bcm2835.h"
#include <stdint.h>
#include <stdio.h>

const uint8_t gpio_pin_cs	= 36;	// Define pins here as a const. TODO: variable pins based on cmdline arguments?
const uint8_t gpio_pin_clk	= 39;
const uint8_t gpio_pin_mosi	= 38;
const uint8_t gpio_pin_rst  = 42;

#define CLK_HIGH	bcm2835_gpio_set(gpio_pin_clk)
#define CLK_LOW		bcm2835_gpio_clr(gpio_pin_clk)

#define CS_HIGH		bcm2835_gpio_set(gpio_pin_cs)
#define CS_LOW		bcm2835_gpio_clr(gpio_pin_cs)

#define SDA_HIGH	bcm2835_gpio_set(gpio_pin_mosi)
#define SDA_LOW		bcm2835_gpio_clr(gpio_pin_mosi)

#define SDA_VALUE	bcm2835_gpio_lev(gpio_pin_mosi)

#define SDA_IN		bcm2835_gpio_fsel(gpio_pin_mosi, BCM2835_GPIO_FSEL_INPT)
#define SDA_OUT		bcm2835_gpio_fsel(gpio_pin_mosi, BCM2835_GPIO_FSEL_OUTP)

#define RST_HIGH	bcm2835_gpio_set(gpio_pin_rst)
#define RST_LOW		bcm2835_gpio_clr(gpio_pin_rst)


#define SDA_SET(v)	bcm2835_gpio_write(gpio_pin_mosi, v)

void Delay(int ms) {
	bcm2835_delay(ms);
}

// Initialise the GPIO for SPI
void SPI_Init(void) {
	bcm2835_gpio_fsel(gpio_pin_cs, BCM2835_GPIO_FSEL_OUTP);		
	bcm2835_gpio_set_pud(gpio_pin_cs, BCM2835_GPIO_PUD_UP);
	bcm2835_gpio_set(gpio_pin_cs);	// CS is active low, so set CS high to start
	
	bcm2835_gpio_fsel(gpio_pin_clk, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_set_pud(gpio_pin_clk, BCM2835_GPIO_PUD_UP);
	bcm2835_gpio_set(gpio_pin_clk);	// CLK should idle high according to ILI9481 datasheet						
	
	bcm2835_gpio_fsel(gpio_pin_mosi, BCM2835_GPIO_FSEL_OUTP);	
	bcm2835_gpio_set_pud(gpio_pin_mosi, BCM2835_GPIO_PUD_UP);
	bcm2835_gpio_clr(gpio_pin_mosi);

	bcm2835_gpio_fsel(gpio_pin_rst, BCM2835_GPIO_FSEL_OUTP);	
	bcm2835_gpio_set_pud(gpio_pin_rst, BCM2835_GPIO_PUD_UP);
	bcm2835_gpio_set(gpio_pin_rst);

	CLK_HIGH;
	CS_HIGH;
	SDA_HIGH;
	RST_HIGH;
}


// The rst pin set low will reset the device and must be applied to properly initialize the chip.
void LCD_Rst(void){			
	RST_LOW;
    bcm2835_delay(100);					   
	RST_HIGH;
    bcm2835_delay(100);	
}

void SPI_Delay()
{
	bcm2835_delayMicroseconds(1);
}

void LCD_WriteByteSPI(uint8_t value) {
	int i;
	for(i = 7; i >= 0; i--)
	{
		CLK_LOW;
		SDA_SET( (value >> i) & 0x01 );
		SPI_Delay();
		CLK_HIGH;
		SPI_Delay();
	}
}

void SPI_WriteComm(uint8_t CMD) {	
	SDA_OUT;
	// command
	
	SDA_LOW;
	CLK_LOW;
	SPI_Delay();
	CLK_HIGH;
	SPI_Delay();

	LCD_WriteByteSPI(CMD);
}

void SPI_WriteData(uint8_t DATA) {
	SDA_OUT;
	// data
	SDA_HIGH;
	CLK_LOW;
	SPI_Delay();
	CLK_HIGH;
	SPI_Delay();

	LCD_WriteByteSPI(DATA);
}


int main(void) 
{
    if (!bcm2835_init()) {
		return 1;
	}

    SPI_Init();

    LCD_Rst();


    return 0;
}

