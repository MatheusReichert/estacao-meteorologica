#pragma once
#include "wind_direction.hpp"

#include "Arduino.h"
#include "freertos/FreeRTOS.h"
class WindDirection
{
private:
    int pin_north, pin_south, pin_east, pin_west;
public:
    void begin(char *position);
    WindDirection(int pin_north, int pin_south, int pin_east, int pin_west);
    ~WindDirection();
};


