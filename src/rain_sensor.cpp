#include "rain_sensor.hpp"


void RainSensor::begin(){
   
}

String RainSensor::isRaining()
{
    String result;

    int sensorReading = analogRead(this->pin);
    Serial.print("#######");
    Serial.println(sensorReading);
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
