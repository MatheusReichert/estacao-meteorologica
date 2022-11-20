#include "rain_sensor.h"


String RainSensor::isRaining()
{
    String result;

    int sensorReading = analogRead(pin);

    int range = map(sensorReading, sensorMin, sensorMax, 0, 3);

    switch (range)
    {
    case 0:
        result = "Flood";
        break;
    case 1:
        result = "Rain Warning";

        break;
    case 2:
        result = "Not Raining";
        break;
    }
    return result;
}
