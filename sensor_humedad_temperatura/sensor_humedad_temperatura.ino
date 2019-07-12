//Sensor de temperatura sin los actuadores, solo imprimiendo variables obtenidas



//El sketch para mostrar los datos de temperatura y humedad relativa en el display LCD es:
//#include <LiquidCrystal.h> 

#include "DHT.h"
#define DHTTYPE DHT21   // DHT 21 (AM2301)
#define DHTPIN 2
DHT dht(DHTPIN, DHTTYPE);    //Se inicia una variable que sera usada


void setup() {
 Serial.begin(9600);    //Se inicia la comunicacion serial
 Serial.println("Prueba DHT");
 dht.begin();           //Se inicia el sensor
}
void loop() {
 delay(2000);    //Se establece un retraso porque el sensor solo realiza una lectura cada ?(cuantos segundos? 2000 si son 2 s)
 // Reading temperature or humidity takes about 250 milliseconds!
 // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
 
 float h = dht.readHumidity();       //Se lee la humedad.Se establece h de variable de humedad relativa.
 float t = dht.readTemperature();    //Se lee la temperatura. Se establece t de variable de temperatura.
 
 // || es un "o"
//Con la funcion isnan controlamos que el valor recibido del sensor sea un número, sino dara error
// NaN (not a number) --> si t (valor medido de temperatura) o h (valor medido de humedad), no es un numero se imprime que hubo un fallo.
 if (isnan(t) || isnan(h)) {
   Serial.println("Fallo al leer del sensor DHT");
   //return;
 } else {

  //Se imprimen las variables obtenidas
  // Aqui ademas de imprimir variables debe poner los actuadores a funcionar
   Serial.print("Humedad: "); 
   Serial.print(h);
   Serial.print(" %\t");
   Serial.print("Temperatura: "); 
   Serial.print(t);
   Serial.println(" *C");
 }
}
