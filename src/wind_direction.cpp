#include "wind_direction.hpp"

WindDirection::WindDirection(int pin_north, int pin_south, int pin_east, int pin_west)
{
    pinMode(pin_north, INPUT);
    pinMode(pin_south, INPUT);
    pinMode(pin_east, INPUT);
    pinMode(pin_west, INPUT);

    this->pin_north=pin_north;
    this->pin_east=pin_east;
    this->pin_west=pin_west;
    this->pin_south=pin_south;
}

WindDirection::~WindDirection()
{
}