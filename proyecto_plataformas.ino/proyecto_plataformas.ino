/**
* Sensor de temperatura simple TMP36
*Sensor Higrometro: YL-69, modulo comparador: LM393
*
*Sensor temperatura y humedad: DHT21 modelo AM2301
*Salidas de Relays: Bomba (relayBombaHg, 2). Abanico (relayFanTemp,1).
*
*Ana B. Torre B36963
*Jose M. Hidalgo B63466
*/

/* Variables propias del Sensor DTH21*/
#include "DHT.h"
#define DHTTYPE DHT21   // DHT 21 (AM2301)
#define DHTPIN 3
DHT dht(DHTPIN, DHTTYPE);    /*Se inicia una variable que sera usada*/

/*Parámetros del control sobre la temperatura y humedad*/
float humLeida, tempLeida  ;

int tempIdeal;
int humRIdeal;
int tempMax= 26;
int tempMin=22;
int humMin= 80;
int humMax=90;

/*Parámetros del control de humedad sobre el suelo y sustratos */

int lecturaHigrom;

int higrometro = A0;   /*ubicación en la placa de Arduino, entrada del Sensor Higrometro
 
/*Placa Arduino y sus pines de conexión*/

const int relayBombaHg = 6;                     /*Pin en el que está conectado el relay de la Bomba que se activa o no segun medicion del Higrometro  */          
const int relayAbanico=5;                      /*Pin en el que está conectado el relay del abanico que se enciende o no segun medicion de Temperatura*/
const int relayCalentador=7;

            /******************VERIFICAR PIN *********** //LED que debe encenderse si calentador esta encendido*/  
int ledAbanico=11;                   /*LED que debe encenderse si abanico esta encendido*/
int ledBomba=12;                     /*LED que debe encenderse si bomba de riego esta encendida*/
int ledCalentador= 13; 

/* Variables propias de la conexión Serial vía Bluetooth*/
#include <SoftwareSerial.h> 
char NOMBRE[10]  = "HC06";        /* Nombre asignado para nuestro módulo de Bluetooth: por defecto*/
char BPS         = '4';           /* 4=9600 Baudios*/
char PASS[10]    = "4321";        /*clave de acceso al dispositivo*/
SoftwareSerial BT1(0, 1); // RX | TX

void setup() {
  
 Serial.begin(9600); /*Indicamos que nuestra conexión será de 9600 baudios*/
 BT1.begin(9600);    /* Indicamos que nuestra conexión bluetooth será de 9600 baudios.*/
 pinMode (relayBombaHg,OUTPUT);               /*Configurar relayBombaHg como salida*/
 pinMode (relayAbanico,OUTPUT);               /*Configurar relayBombaHg como salida*/ 
 pinMode(ledAbanico, OUTPUT);                 /*Configuramos ledAbanico como salida*/
 pinMode(ledBomba, OUTPUT);                  /*Configuramos ledBomba como salida*/
 pinMode(ledCalentador, OUTPUT);             /*Configuramos ledCalentador como salida*/
 Serial.println("Prueba DHT");
 dht.begin();                                 /*Se inicia el sensor*/
  

 }
    
void loop() {    
  
    int opcionSeleccion=0; 
    int lecturaHigrom = analogRead(higrometro);
  
    int tempIdeal=0, humRIdeal=0, tempMax=0, tempMin=0, humMin=0, humMax=0;
    //controTempHum(tempIdeal, humRIdeal, tempMax, tempMin, humMin, humMax); 
    controlHumPiso(lecturaHigrom);   
   
    Serial.print("Universidad de Costa Rica");
    Serial.print("Inserte una opción:");
    Serial.print("1. Conexión via Bluetooth via comandos AT");
    Serial.print("2. Ver parametros sensor de Temperatura/Humedad Relativa");
    Serial.print("3. Ver Serial via Bluetooth (sensor de Temperatura/Humedad Relativa=");

    opcionSeleccion=Serial.read();
    switch(opcionSeleccion){
      case 1:
      conexionSerialBt();
      break;
      controlTempHum(tempIdeal, humRIdeal, tempMax, tempMin, humMin, humMax);
      case 2:
      break;
      case 3: 
      controlHumPiso(lecturaHigrom);
      break;
      case 4: 
      void serialBT();
      break;
      }
 }

    
///////////////////////////////////////////////////////////
////     F U N C I O N E S
////
//////////////////////////////////////////////////////////
    
void conexionSerialBt(){ 
  
    pinMode(13,OUTPUT);
    digitalWrite(13,HIGH);
    delay(10000);
    digitalWrite(13,LOW);
    
    Serial.print("AT"); 
    delay(1000);
 
    Serial.print("AT+NAME"); 
    Serial.print(NOMBRE);
    delay(1000);
 
    Serial.print("AT+BAUD"); 
    Serial.print(BPS); 
    delay(1000);
 
    Serial.print("AT+PIN");
    Serial.print(PASS); 
    delay(1000);    
}

void serialBT(){
 if (BT1.available())
  {
    Serial.write(BT1.read());
  }

  if (Serial.available())
  {
    BT1.write(Serial.read());
  }
  
}

void controlTempHum(int tempIdeal, int  humRIdeal,  int tempMax, int tempMin, int humMin, int humMax){ 
  
  delay(2000);                        /*Se establece un retraso porque el sensor solo realiza una lectura cada ?(cuantos segundos? 2000 si son 2 s)*/
 humLeida = dht.readHumidity();       /*Se lee la humedad.Se establece h de variable de humedad relativa.*/
 tempLeida = dht.readTemperature();   /*Se lee la temperatura. Se establece t de variable de temperatura.*/
 
                                      /*|| es un "o"*/
/*Con la funcion isnan controlamos que el valor recibido del sensor sea un número, sino dara error*/
/* NaN (not a number) --> si t (valor medido de temperatura) o h (valor medido de humedad), no es un numero se imprime que hubo un fallo.*/

 if (isnan(tempLeida) || isnan(humLeida)) {
   Serial.println("Fallo al leer del sensor DHT");
 } else {
  /*Se imprimen las variables obtenidas*/

   Serial.print("Humedad: "); 
   Serial.print(humLeida);
   Serial.print(" %\t");
   Serial.print("Temperatura: "); 
   Serial.print(tempLeida);
   Serial.println(" *C");
   
 /*OJO: los reles en LOW encienden, en HIGH apagan*/

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
        /*Se entra a este caso es porque la humedad esta en el rango ideal o la temperatura esta en el rango ideal, y el otro esta fuera del rango
        /*Al siguiente caso entra si la temperatura esta en el rango ideal, y la humedad esta mal:*/
        
        if (humLeida>humMax || humLeida<humMin){
          Serial.print("La temperatura se encuentra en rangos ideales, su problema es con la humedad");
          if (humLeida>humMax){
            Serial.print("La humedad es MAYOR de lo que deberia.\nDebe encenderse el abanico.");
            digitalWrite(relayAbanico,LOW);         /*Si la humedad sobrepasa el valor maximo, se ENCIENDE el abanico*/
            digitalWrite(ledAbanico,HIGH);          /*Se enciende el LED que indica que el abanico esta encendido*/

            digitalWrite(relayCalentador,HIGH);       /* Si estaba prendido el calentador, apaguelo*/
            digitalWrite(ledCalentador,LOW);          /*Apague el LED que dice que el calentador esta encendido*/
         
          } else {                                    /* Este caso seria si la humedad esta por debajo de la minima*/
            Serial.print("La humedad es MENOR de lo que deberia.");
            Serial.print("ALARMA: necesita rociar un poco de agua para aumentar la humedad del ambiente");

            digitalWrite(relayCalentador,HIGH);         /* Si estaba prendido el calentador, apaguelo*/
            digitalWrite(ledCalentador,LOW);            /*Apague el LED que dice que el calentador esta encendido*/

            digitalWrite(relayAbanico,HIGH);            /* Si estaba prendido el abanico, apaguelo*/
            digitalWrite(ledAbanico,LOW);               /*Apague el LED que dice que el abanic esta encendido*/
            }
      
      
        } else if (tempLeida>tempMax || tempLeida<tempMin) {   /*Se entra aqui si humedad es ideal y temperatura se sale de los rangos*/
              Serial.print("La humedad se encuentra en rangos ideales, su problema es con la temperatura");
              if (tempLeida>tempMax){
                Serial.print("La temperatura es MAYOR de lo que deberia.\nDebe encenderse el abanico");
                digitalWrite(relayAbanico,LOW); /*Si la humedad sobrepasa el valor maximo, se ENCIENDE el abanico*/
                digitalWrite(ledAbanico,HIGH); /*Se enciende el LED que indica que el abanico esta encendido*/

                digitalWrite(relayCalentador,HIGH); /* Si estaba prendido el calentador, apaguelo*/
                digitalWrite(ledCalentador,LOW); /*Apague el LED que dice que el calentador esta encendido*/
 
              }else {  /* Este caso es si la humedad es ideal y la temp es minima */
                Serial.print("La temperatura es MENOR de lo que deberia.\nDebe encenderse el calentador");
                digitalWrite(relayCalentador,LOW); /* Si temperatura baja del minimo, se ENCIENDE calentador*/
                digitalWrite(ledCalentador,HIGH); /*Se enciende el LED que dice que el calentador esta encendido*/

                digitalWrite(relayAbanico,HIGH); /* Si estaba prendido el abanico, apaguelo*/
                digitalWrite(ledAbanico,LOW); /*Apague el LED que dice que el abanico esta encendido*/
              }
              
        }else {
              Serial.print(" Muy bien, tanto temperatura como humedad estan en rangos ideales!!!! ");
        }
          
        }
        
      }
  }
  

void controlHumPiso(int lecturaHigrom){
  
  /* Cuando el hongo tiene suficiente humedad en la tierra, el sensor va a leer entre 380-400*/
 /* podria cambiarse el 400 a un valor mas bajo*/
  
  lecturaHigrom = analogRead(higrometro);   //Lee entrada del higrometro
  /*Los siguientes valores (400 y 1023 hay que establecer si son esos)*/
  lecturaHigrom = constrain(lecturaHigrom,400,1023);  /*Constrain limita el rango del sensor (lecturaHigrom) entre 400 y 1023*/
  /*Retorna lecturaHigrom si este esta entre 400 y 1023, retorna 400 si lecturaHigrom es menor que 400, retorna  1023 si lecturaHigrom es mayor que 1023*/
  /*O sea, si esta dentro del rango retorne lo que es, si esta para abajo del minimo retorne ese minimo, y si esta para abajo del maximo, retorne ese maximo*/
  lecturaHigrom = map(lecturaHigrom,400,1023,100,0);  /*Mapeo. Ahora 400 va a ser 100 (minimo) 1023 va a ser 0 (maximo)*/
  
  Serial.print("Humedad: ");
  Serial.print(lecturaHigrom);
  Serial.println("%");
     /*Si la humedad baja del 20%, enciende la bomba, sino se mantiene apagada*/
  if (lecturaHigrom < 20){
    //aqui va a encender la bomba
    digitalWrite(relayBombaHg,LOW);
    digitalWrite(ledBomba,HIGH);
  }
  else {
      digitalWrite(relayBombaHg,HIGH);
      digitalWrite(ledBomba,LOW);
  }
  delay(1500);        /*un pequeno delay*/
}


  
  
  
  
