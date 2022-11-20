#include <Arduino.h>
#include "estacao_pin_def.h"
#include <esp32DHT.h>      // https://github.com/bertmelis/esp32DHT
#include "EspMQTTClient.h" // https://github.com/plapointe6/EspMQTTClient
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>
#include <ML8511.h>
#include "rain_sensor.h"

#define SEALEVELPRESSURE_HPA (1013.25)

#define topico "dasfkljasdiovfgjoadbg0oadbhgjoasdgoasdhno"

ML8511 uv_sensor(uv);

DHT22 dht22;

RainSensor rainSensor(rain_a0);

Adafruit_BMP280 bmp;

EspMQTTClient client(
    "Hackerman",
    "c12h22o11",
    "54.87.92.106",
    "estacao-meteorologica");

void onConnectionEstablished()
{
  client.publish(topico, "Estacao meteorologica conectada");
}

void setup()
{
  Serial.begin(112500);

  // uv_sensor.enable(); conectado na 3.3 sempra vai estar enable, independente irmão

  dht22.setup(dht22_out);
  dht22.onData([](float humid, float temp)
               { Serial.printf("Temp: %.1f°C\nHumid: %.1f%%\n", temp, humid); });

  dht22.onError([](uint8_t error)
                { Serial.printf("Error: %d-%s\n", error, dht22.getError()); });

  // Sessão erros BMP280
  unsigned status;

  // default settings
  status = bmp.begin();
  
  
  if (!status)
  {
    Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
    Serial.print("SensorID was: 0x");
    Serial.println(bmp.sensorID(), 16);
    Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
    Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
    Serial.print("        ID of 0x60 represents a BME 280.\n");
    Serial.print("        ID of 0x61 represents a BME 680.\n");
    while (1)
      delay(10);
  }

  Serial.println("-- Default Test --");
  // fim sessao erros bmp280
}

void loop()
{
  //dht22.read(); //dispara o callback;
  //      bmpPrintValues(); 
  //      uv_sensor.getUV();
  rainSensor.isRaining();

  client.loop();
}

void bmpPrintValues()
{
  Serial.print("Temperature = ");
  Serial.print(bmp.readTemperature());
  Serial.println(" °C");

  Serial.print("Pressure = ");

  Serial.print(bmp.readPressure() / 100.0F);
  Serial.println(" hPa");

  Serial.print("Approx. Altitude = ");
  Serial.print(bmp.readAltitude(SEALEVELPRESSURE_HPA));
  Serial.println(" m");

  Serial.println();
}