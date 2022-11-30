/** @file RAIN_SENSOR_H.h
 * 
 * @brief RAIN_SENSOR lib
 *
 * @par       
 * 
 */ 

#ifndef RAIN_SENSOR_H
#define RAIN_SENSOR_H

#include <Arduino.h>


class RainSensor {     // The class
  public:           // Access specifier
    RainSensor(int espPin) {     // Constructor
      this->pin = espPin;
    };
    void begin();
    String isRaining();
    private:
    int pin;
    const int sensorMin = 800;     // sensor minimum
    const int sensorMax = 4096;  // sensor maximum
};

#endif /* RAIN_SENSOR_H */

/*** end of file ***/