/** @file STATION_pin_def.h
 * 
 * @brief Pinagem dos sensores da estção meteorologica
 *
 * 
 */ 

#ifndef STATION_PIN_DEF_H
#define STATION_PIN_DEF_H

#define DHTTYPE DHT22 
#define DHT_OUT GPIO_NUM_2

#define UV_OUT GPIO_NUM_37

#define RAIN_ANALOG_OUT GPIO_NUM_32

#define ANEMOMETER_OUT GPIO_NUM_35


#define BMP_SDA 21                                                                //Definição dos pinos I2C
#define BMP_SCL 22

#define wind_vane_north GPIO_NUM_12
#define wind_vane_south GPIO_NUM_13
#define wind_vane_west GPIO_NUM_17
#define wind_vane_east GPIO_NUM_23

#define RAIN_GAUGE_OUT GPIO_NUM_25

#endif /* STATION_PIN_DEF_H */

/*** end of file ***/