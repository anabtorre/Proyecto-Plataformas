//*Sensor Higrometro: YL-69, modulo comparador: LM393
//YA TODO EN AVANCE2
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <stdio.h>
#include <stdbool.h>
#include <Arduino.h>

# include "libreria_higrometro.h"

void setup()
{
  empezar(relayBombaHg,higrometro,ledBomba);
  
 
}

void loop()
{
  leerYtraducir(lecturaHigrom, higrometro);
  salida(relayBombaHg , lecturaHigrom );
}
