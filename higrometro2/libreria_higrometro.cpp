#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <stdio.h>
#include <stdbool.h>
#include <Arduino.h>


# include "libreria_higrometro.h"


void empezar(const int relayBombaHg, const int higrometro,int ledBomba){
  Serial.begin(9600);
  pinMode(relayBombaHg,OUTPUT); 
  pinMode(ledBomba, OUTPUT);
  pinMode(higrometro, OUTPUT);

}
void leerYtraducir(int lecturaHigrom, const int higrometro){
  lecturaHigrom = analogRead(higrometro);  


//Lee entrada del higrometro
//Los siguientes valores (400 y 1023 hay que establecer si son esos)
  lecturaHigrom = constrain(lecturaHigrom,400,1023);  //Constrain limita el rango del sensor (lecturaHigrom) entre 400 y 1023
//Retorna lecturaHigrom si este esta entre 400 y 1023, retorna 400 si lecturaHigrom es menor que 400, retorna  1023 si lecturaHigrom es mayor que 1023.
//O sea, si esta dentro del rango retorne lo que es, si esta para abajo del minimo retorne ese minimo, y si esta para abajo del maximo, retorne ese maximo
  lecturaHigrom = map(lecturaHigrom,400,1023,100,0);  //Mapeo. Ahora 400 va a ser 100 (minimo) 1023 va a ser 0 (maximo)
}
void salida(const int relayBombaHg , int lecturaHigrom ){
  leerYtraducir(lecturaHigrom,higrometro);
 // Cuando el hongo tiene suficiente humedad en la tierra, el sensor va a leer entre 380-400
 // podria cambiarse el 400 a un valor mas bajo 
  
  Serial.print("Humedad:");
  Serial.print (lecturaHigrom);
  Serial.println("%");
  //Si la humedad baja del 80%, enciende la bomba, sino se mantiene apagada
  if (lecturaHigrom < 80){
    //aqui va a encender la bomba
    digitalWrite(relayBombaHg,LOW); //En LOW enciende
    digitalWrite(ledBomba,HIGH); 
  }
  else {
      digitalWrite(relayBombaHg,HIGH);
      digitalWrite(ledBomba,LOW); 
  }
  delay(1500); //un delay de 1,5 s (1500 ms)
}
