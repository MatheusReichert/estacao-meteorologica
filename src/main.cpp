#include <Arduino.h>
#include "estacao_pin_def.h"
#include <esp32DHT.h>      // https://github.com/bertmelis/esp32DHT
#include "EspMQTTClient.h" // https://github.com/plapointe6/EspMQTTClient
#include <Wire.h>
#include <SPI.h>            
#include <ML8511.h>         // https://github.com/RobTillaart/ML8511
#include <Adafruit_BMP085.h>  // https://github.com/adafruit/Adafruit-BMP085-Library
#include "rain_sensor.hpp"


#include "heltec.h"

// Topico para onde sera enviada a mensagem com os dados dos sensores
#define topico "dasfkljasdiovfgjoadbg0oadbhgjoasdgoasdhno"

// Inicializacao de variaveis
float humidade = 0.0f;
float temperatura = 0.0f;
float uvLevel = 0.0f;
float altitude = 0.0f;

int state_anemometer = 0;

int state_rain_gauge = 0;

int state_wind_vane_north = 0;
int state_wind_vane_south = 0;
int state_wind_vane_west = 0;
int state_wind_vane_east = 0;

String rainStatus = "";

//Inicializacao dos objetos das bibliotecas
ML8511 uv_sensor(UV_OUT);

DHT22 dht22;

Adafruit_BMP085 bmp;

RainSensor rainSensor(RAIN_ANALOG_OUT);

EspMQTTClient client(
    "Hackerman",
    "c12h22o11",
    "54.87.92.106",
    "estacao-meteorologica");

void onConnectionEstablished()
{
  client.publish(topico, "Connected");
}

void setup()
{
  // Parametros iniciais e definicao de pinos
  Heltec.begin(false, false, true, false);
  Serial.begin(112500);
  
  pinMode(wind_vane_east, INPUT);
  pinMode(wind_vane_north, INPUT);
  pinMode(wind_vane_south, INPUT);
  pinMode(wind_vane_west, INPUT);

  pinMode(RAIN_GAUGE_OUT, INPUT);

  pinMode(ANEMOMETER_OUT, INPUT);

  uv_sensor.setVoltsPerStep(3.3, 4095);

  rainSensor.begin();

  dht22.setup(DHT_OUT);

  dht22.onData([](float humid, float temp)
               { Serial.printf("Temp: %.1f°C\nHumid: %.1f%%\n", temp, humid);
               humidade = humid ;
               temperatura = temp; });

  dht22.onError([](uint8_t error)
                { Serial.printf("DHT Error: %d-%s\n", error, dht22.getError()); });

  Wire.begin(21, 22);
  if (!bmp.begin())
  {
    Serial.println("Could not find a valid BMP085 sensor, check wiring!");
    while (1)
    {
    }
  }
}

void loop()
{
  // Coleta os valores dos sensores 
  dht22.read();
  uvLevel = uv_sensor.getUV();
  rainStatus = rainSensor.isRaining();
  altitude = bmp.readAltitude();

  state_anemometer = digitalRead(ANEMOMETER_OUT);

  state_rain_gauge = digitalRead(RAIN_GAUGE_OUT);

  state_wind_vane_north = digitalRead(wind_vane_north);
  state_wind_vane_south = digitalRead(wind_vane_south);
  state_wind_vane_west = digitalRead(wind_vane_west);
  state_wind_vane_east = digitalRead(wind_vane_east);

  // Transforma os valores coletados em uma mensagem
  char *template_msg = "{\r\n\"temperature\":\"%f\",\r\n\"humidity\":\"%f\",\r\n\"pressure\":\"%f\",\r\n\"uv\":\"%f\",\r\n\"rain\":\"%s\",\r\n\"anemometer_state\":\"%i\",\r\n\"rain_gauge_state\":\"%i\",\r\n\"wind_vane_north_state\":\"%i\",\r\n\"wind_vane_south\":\"%i\",\r\n\"wind_vane_west\":\"%i\",\r\n\"wind_vane_east\":\"%i\"\r\n}";
  char buffer[500];

  snprintf(buffer, 500, template_msg, temperatura, humidade, altitude, uvLevel, rainStatus, state_anemometer, state_rain_gauge, state_wind_vane_north, state_wind_vane_south, state_wind_vane_west, state_wind_vane_east);

  // Envia a mesagem para o serviço de mqtt
  client.publish(topico, buffer);
  client.loop();
  // Delay de 500 ms
  vTaskDelay(pdMS_TO_TICKS(1000));
}
