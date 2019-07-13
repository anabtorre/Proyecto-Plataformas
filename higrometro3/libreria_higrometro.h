
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <stdio.h>
#include <stdbool.h>
#include <Arduino.h>


const int relayBombaHg = 6; //Bomba que se activa cuando la humedad esta baja. En el pin 2 del relay
const int higrometro = A0;  // Higrometro conectado a pin A0 del arduino
//Variables 
//int lecturaHigrom; 
int ledBomba=12;
void lectura();
