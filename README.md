# DPI_LCD_RaspberryPi

如何使用树莓派的DPI接口来驱动LCD屏幕

## Hardware
### raspberry
* 树莓派CM3 + CMIO底板
### lcd module
* 3.5 YT35F120A0

## Software

### Initialization code
using c language with the bcm2835.h library.

GPIO configure

name|gpio|
---|---|
cs|36
clk|39
sda|38
rst|42

