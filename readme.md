# MaUWB_DW3000 with STM32 AT Command


```c++
/*
Version:		V1.0
Author:			Vincent
Create Date:	2023/10/14
Note:

*/
```
![](md_pic/main.jpg)


[toc]

# Makerfabs

[Makerfabs home page](https://www.makerfabs.com/)

[Makerfabs Wiki](https://wiki.makerfabs.com/)



# MaUWB_DW3000 with STM32 AT Command
## Intruduce

Product Link ：[MaUWB_DW3000 with STM32 AT Command](https://www.makerfabs.com/mauwb-dw3000-with-stm32-at-command.html) 

Wiki Link : []()

The latest UWB module that solves multiple anchors& tags mutual conflicts, support max 8 Anchors + 32 tags in application, to create a multi-anchor multi-tag positioning system.


## Feature

- DW3000 with PA, max range 500M
- Precision 0.5M(in range 100m)
- Support 8 anchors+ 32 Tags application

# Code

## Compiler Options

- Use type-c use cable connect USB-TTL to PC.
- Select "ESP32 DEV Module"

Libraries:
- Use 2.0.0   Wire
- Use 1.11.7   Adafruit_GFX_Library
- Use 1.14.4   Adafruit_BusIO
- Use 2.0.0   SPI
- Use 2.5.7   Adafruit_SSD1306


## Example

### esp32_at_t0

Factory firmware, reset the UWB AT module and set it to Tag 0.

### esp32_at_t0

Reset the UWB AT module and set it to Anchor 0.

### serial_test

Serial port test

### Indoor positioning

Simple indoor positioning example, using json to pass data.