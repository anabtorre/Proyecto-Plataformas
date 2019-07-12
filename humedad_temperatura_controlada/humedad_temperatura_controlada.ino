
#include "DHT.h"
//En funciones.h:////////////////////////////////////
#define DHTTYPE DHT21   // DHT 21 (AM2301)
#define DHTPIN 2
DHT dht(DHTPIN, DHTTYPE);    //Se inicia una variable que sera usada
float humLeida, tempLeida  ;

int tempMax= 26;
int tempMin=22;
int humMin= 80;
int humMax=90;

const int relayBombaHg = 6;                     //Pin en el que está conectado el relay de la Bomba que se activa o no segun medicion del Higrometro            
const int relayAbanico=5;                      //Pin en el que está conectado el relay del abanico que se enciende o no segun medicion de Temperatura
const int relayCalentador=7;
                                    
int ledAbanico=11;                   //LED que debe encenderse si abanico esta encendido
int ledBomba=12;                     //LED que debe encenderse si bomba de riego esta encendida
int ledCalentador= 13;  //*****************VERIFICAR PIN *********** //LED que debe encenderse si calentador esta encendido

//////////////////////////////////////////////////


void setup() {
 Serial.begin(9600);    //Se inicia la comunicacion serial
 pinMode (relayBombaHg,OUTPUT);               //Configurar relayBombaHg como salida
 pinMode (relayAbanico,OUTPUT);               //Configurar relayBombaHg como salida  
 pinMode(ledAbanico, OUTPUT);                 //Configuramos ledAbanico como salida
 pinMode(ledBomba, OUTPUT);                  //Configuramos ledBomba como salida
 pinMode(ledCalentador, OUTPUT);              //Configuramos ledCalentador como salida
 Serial.println("Prueba DHT");
 dht.begin();           //Se inicia el sensor
}
void loop() {
 delay(2000);    //Se establece un retraso porque el sensor solo realiza una lectura cada ?(cuantos segundos? 2000 si son 2 s)
 // Reading temperature or humidity takes about 250 milliseconds!
 // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
 
 humLeida = dht.readHumidity();       //Se lee la humedad.Se establece h de variable de humedad relativa.
 tempLeida = dht.readTemperature();    //Se lee la temperatura. Se establece t de variable de temperatura.
 // || es un "o"
//Con la funcion isnan controlamos que el valor recibido del sensor sea un número, sino dara error
// NaN (not a number) --> si t (valor medido de temperatura) o h (valor medido de humedad), no es un numero se imprime que hubo un fallo.
 if (isnan(tempLeida) || isnan(humLeida)) {
   Serial.println("Fallo al leer del sensor DHT");
   //return;
 } else {
  //Se imprimen las variables obtenidas

   Serial.print("Humedad: "); 
   Serial.print(humLeida);
   Serial.print(" %\t");
   Serial.print("Temperatura: "); 
   Serial.print(tempLeida);
   Serial.println(" *C");
   
 //OJO: los reles en LOW encienden, en HIGH apagan

      if (tempLeida>tempMax & humLeida>humMax){
        Serial.print("La temperatura y humedad esta por encima de los maximos permitidos");
        digitalWrite(relayAbanico,LOW); //Si la temperatura y humedad sobrepasan los maximos, se ENCIENDE el abanico
        digitalWrite(ledAbanico,HIGH); //Si temperatura es muy alta encienda LED, que indica que el abanico esta encendido
        digitalWrite(relayCalentador,HIGH); // Si estaba prendido el calentador, se apaga
        digitalWrite(ledCalentador,LOW); //Se apaga el LED que dice que el calentador esta encendido
    
      } else if (tempLeida>tempMax & humLeida<humMin ){
        Serial.print("La temperatura esta por encima de lo permitido, y la humedad por debajo del minimo");
        digitalWrite(relayAbanico,LOW); //Si la temperatura sobrepasa el maximo, se ENCIENDE el abanico
        digitalWrite(ledAbanico,HIGH); //Si temperatura es muy alta encienda LED, que indica que el abanico esta encendido
    
        digitalWrite(relayCalentador,HIGH); // Si estaba prendido el calentador, apaguelo
        digitalWrite(ledCalentador,LOW); //Apague el LED que dice que el calentador esta encendido
        Serial.print("ALARMA: necesita rociar un poco de agua para aumentar la humedad del ambiente");
   
      } else if (tempLeida<tempMin & humLeida>humMax){
        Serial.print("La temperatura esta por debajo del minimo y la humedad por encima del maximo");
        digitalWrite(relayCalentador,LOW); // Si temperatura baja del minimo, se ENCIENDE calentador
        digitalWrite(ledCalentador,HIGH); //Se enciende el LED que dice que el calentador esta encendido

        digitalWrite(relayAbanico,LOW); //Si la humedad sobrepasa el valor maximo, se ENCIENDE el abanico
        digitalWrite(ledAbanico,HIGH); //Se enciende el LED que indica que el abanico esta encendido
    
      } else if (tempLeida<tempMin & humLeida<humMin ){
        Serial.print("La humedad y temperatura estan por debajo de los minimos permitidos");
        digitalWrite(relayCalentador,LOW); // Si temperatura baja del minimo, se ENCIENDE calentador
        digitalWrite(ledCalentador,HIGH); //Se enciende el LED que dice que el calentador esta encendido

        digitalWrite(relayAbanico,HIGH); // Si estaba prendido el abanico, apaguelo
        digitalWrite(ledAbanico,LOW); //Apague el LED que dice que el abanic esta encendido

        Serial.print("ALARMA: necesita rociar un poco de agua para aumentar la humedad del ambiente");
    
      } else {
        //Se entra a este caso es porque la humedad esta en el rango ideal o la temperatura esta en el rango ideal, y el otro esta fuera del rango
        //Al siguiente caso entra si la temperatura esta en el rango ideal, y la humedad esta mal:
        
        if (humLeida>humMax || humLeida<humMin){
          Serial.print("La temperatura se encuentra en rangos ideales, su problema es con la humedad");
          if (humLeida>humMax){
            Serial.print("La humedad es MAYOR de lo que deberia.\nDebe encenderse el abanico.");
            digitalWrite(relayAbanico,LOW); //Si la humedad sobrepasa el valor maximo, se ENCIENDE el abanico
            digitalWrite(ledAbanico,HIGH); //Se enciende el LED que indica que el abanico esta encendido

            digitalWrite(relayCalentador,HIGH); // Si estaba prendido el calentador, apaguelo
            digitalWrite(ledCalentador,LOW); //Apague el LED que dice que el calentador esta encendido
         
          } else { // Este caso seria si la humedad esta por debajo de la minima
            Serial.print("La humedad es MENOR de lo que deberia.");
            Serial.print("ALARMA: necesita rociar un poco de agua para aumentar la humedad del ambiente");

            digitalWrite(relayCalentador,HIGH); // Si estaba prendido el calentador, apaguelo
            digitalWrite(ledCalentador,LOW); //Apague el LED que dice que el calentador esta encendido

            digitalWrite(relayAbanico,HIGH); // Si estaba prendido el abanico, apaguelo
            digitalWrite(ledAbanico,LOW); //Apague el LED que dice que el abanic esta encendido
            }
      
      
        } else if (tempLeida>tempMax || tempLeida<tempMin) {   //Se entra aqui si humedad es ideal y temperatura se sale de los rangos
              Serial.print("La humedad se encuentra en rangos ideales, su problema es con la temperatura");
              if (tempLeida>tempMax){
                Serial.print("La temperatura es MAYOR de lo que deberia.\nDebe encenderse el abanico");
                digitalWrite(relayAbanico,LOW); //Si la humedad sobrepasa el valor maximo, se ENCIENDE el abanico
                digitalWrite(ledAbanico,HIGH); //Se enciende el LED que indica que el abanico esta encendido

                digitalWrite(relayCalentador,HIGH); // Si estaba prendido el calentador, apaguelo
                digitalWrite(ledCalentador,LOW); //Apague el LED que dice que el calentador esta encendido
 
              }else {  // Este caso es si la humedad es ideal y la temp es minima 
                Serial.print("La temperatura es MENOR de lo que deberia.\nDebe encenderse el calentador");
                digitalWrite(relayCalentador,LOW); // Si temperatura baja del minimo, se ENCIENDE calentador
                digitalWrite(ledCalentador,HIGH); //Se enciende el LED que dice que el calentador esta encendido

                digitalWrite(relayAbanico,HIGH); // Si estaba prendido el abanico, apaguelo
                digitalWrite(ledAbanico,LOW); //Apague el LED que dice que el abanico esta encendido
              }
              
        }else {
              Serial.print(" Muy bien, tanto temperatura como humedad estan en rangos ideales!!!! ");
        }
          
        }
        
      }
        


} // del loop
