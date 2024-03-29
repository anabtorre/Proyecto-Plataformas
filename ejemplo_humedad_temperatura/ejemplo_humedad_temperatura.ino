//EJEMPLO sensor humedad y temperatura
// hay que incluir libreria?

#include "DHT.h"
#define DHTPIN 2    // modify to the pin we connected
// Uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11 
//#define DHTTYPE DHT22   // DHT 22  (AM2302)


// ESTE es el nuestro
#define DHTTYPE DHT21   // DHT 21 (AM2301)
// Connect pin 1 (on the left) of the sensor to +5V
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor
DHT dht(DHTPIN, DHTTYPE);

void setup() {
 Serial.begin(9600); 
 Serial.println("DHTxx test!");
 dht.begin();
}
void loop() {
 // Reading temperature or humidity takes about 250 milliseconds!
 // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
 float h = dht.readHumidity();               //se lee la humedad
 float t = dht.readTemperature();
 // check if returns are valid, if they are NaN (not a number) then something went wrong!
 
 // || es un "o"
 
 if (isnan(t) || isnan(h)) {
   Serial.println("Failed to read from DHT");
 } else {
   Serial.print("Humidity: "); 
   Serial.print(h);
   Serial.print(" %\t");
   Serial.print("Temperature: "); 
   Serial.print(t);
   Serial.println(" *C");
 }
}
