/**
* Sensor de temperatura simple TMP36
*Sensor Higrometro: YL-69, modulo comparador: LM393
*Sensor temperatura y humedad: DHT21 modelo AM2301
*Salidas de Relays: Bomba (relayBombaHg, 2). Abanico (relayFanTemp,1).
*
*Ana B. Torre B36963
*Jose M. Hidalgo B63466
*/

//Cosas para sensor de humedad y temperatura:   /////////////////

//El sketch para mostrar los datos de temperatura y humedad relativa en el display LCD es:
//#include <LiquidCrystal.h> 

#include "DHT.h"
#define DHTTYPE DHT21   // DHT 21 (AM2301)
#define DHTPIN 2
DHT dht(DHTPIN, DHTTYPE);    //Se inicia una variable que sera usada
/////////////////////////////////////////////////////////

const int higrometro = A0;                              //Pin en el que está conectado el sensor Higrometro
const int sensorTemp=A1;                               //Pin en el que está conectado el sensor de SOLO Temperatura // En lugar de ese hay que poner el de HUMEDAD Y TEMPERATURA
const int resistenciaCalibracionHg = 1000;            //Resistencia de calibración Higrometro
const int relayBombaHg = 2;                     //Pin en el que está conectado el relay de la Bomba que se activa o no segun medicion del Higrometro            
const int relayAbanico=1;                      //Pin en el que está conectado el relay del abanico que se enciende o no segun medicion de Temperatura
const int relayCalentador=3;
                                    
int ledAbanico=13;                   //LED que debe encenderse si abanico esta encendido
int ledBomba=12;                     //LED que debe encenderse si bomba de riego esta encendida
int ledCalentador= 11;  //*****************VERIFICAR PIN *********** //LED que debe encenderse si calentador esta encendido

int lecturaHigrom;

 
int contadorRiego = 0;             // contador para ver cuantas veces se ha regadp
long Rsensor;                       //valor de la resistencia del sensor de humedad piso en ohm
long Resk;                         // misma resistencia que Rsensor,pero en kohm

//variables del sistema de riego
unsigned float tiempoRiego = 0.1;                    //Tiempo de regado  en minutos //PROBAR cuanto tiempo se ocupa                          
unsigned int tiempoEspera = 10;                    //Tiempo espera en minutos                                       
const int resistenciaSuelo = 15;                    //Resistencia (en kohmios) a partir de la cual empieza a regar 

const int tempMaxima=24;                            //valor a CAMBIAR
const int tempMinima=22;                            //valor a CAMBIAR

void setup() {
  Serial.begin(9600);                          //inicia comunicación serial
  pinMode (relayBombaHg,OUTPUT);               //Configurar relayBombaHg como salida
  pinMode (relayAbanico,OUTPUT);               //Configurar relayBombaHg como salida  
  pinMode(ledAbanico, OUTPUT);                 //Configuramos ledAbanico como salida
  pinMode(ledBomba, OUTPUT);                  //Configuramos ledBomba como salida
  pinMode(ledCalentador, OUTPUT);              //Configuramos ledCalentador como salida
  Serial.println("Prueba DHT");
  dht.begin();                               //Se inicia el sensor de humedad y temperatura DHT
}
}

void loop() {

//***********PROFE:en el loop solo debe llamarse a la funcion de los if de mas adelante. funcion (puntero)    *****************************

/////// ****** H I G R O M E T R O ************  ////////////////////////////////////////////////////

    // Cuando el hongo tiene suficiente humedad en la tierra, el sensor va a leer entre 380-400
    // podria cambiarse el 400 a un valor mas bajo 
    lecturaHigrom = analogRead(higrometro);   //Lee entrada del higrometro
    //Los siguientes valores (400 y 1023 hay que establecer si son esos)
    lecturaHigrom = constrain(lecturaHigrom,400,1023);  //Constrain limita el rango del sensor (lecturaHigrom) entre 400 y 1023
    //Retorna lecturaHigrom si este esta entre 400 y 1023, retorna 400 si lecturaHigrom es menor que 400, retorna  1023 si lecturaHigrom es mayor que 1023.
    //O sea, si esta dentro del rango retorne lo que es, si esta para abajo del minimo retorne ese minimo, y si esta para abajo del maximo, retorne ese maximo
    lecturaHigrom = map(lecturaHigrom,400,1023,100,0);  //Mapeo. Ahora 400 va a ser 100 (minimo) 1023 va a ser 0 (maximo)
  
    //Si la humedad baja del 20%, enciende la bomba, sino se mantiene apagada
    if (lecturaHigrom < 20){
    //aqui va a encender la bomba
      digitalWrite(relayBombaHg,HIGH);
      digitalWrite(ledActuadores, HIGH);
    }
    else {
      digitalWrite(relayBombaHg,LOW);
      digitalWrite(ledActuadores, LOW);
    }
    
    delay(150); //un pequeno delay
  
////// ******* T E M P E R A T U R A   Y   H U M E D A D ***************   //////////////////////////////////
   
    delay(2000);    //Se establece un retraso porque el sensor solo realiza una lectura cada ?(cuantos segundos? 2000 ms (2 s)
    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
 
    float h = dht.readHumidity();       //Se lee la humedad.Se establece h de variable de humedad relativa.
    float t = dht.readTemperature();    //Se lee la temperatura. Se establece t de variable de temperatura.
 
    //Con la funcion isnan controlamos que el valor recibido del sensor sea un número, sino dara error
    // NaN (not a number) --> si t (valor medido de temperatura) o (||) h (valor medido de humedad), no es un numero se imprime que hubo un fallo.
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

    /// PARA PONER ACTUADORES: y usar LCD
    //Al final, en comentarios medio viene
    
   //    https://cetroniconline.blogspot.com/2014/06/tutorial-arduino-iii-sensores-dht-y.html

    ///////////////////////////////////////// DEL DE SOLO TEMPERATURA:  /////////////
     
     int lecturaTemp = analogRead(sensorTemp);  
     float vTemp = lecturaTemp * 5.0;
     vTemp /= 1024.0; 
     Serial.print(vTemp); Serial.println(" voltaje Temperatura");
     float temperaturaC = (vTemp - 0.5) * 100 ; 
     Serial.print(temperaturaC); Serial.println(" grados C");
     float temperaturaF = (temperaturaC * 9.0 / 5.0) + 32.0;
     Serial.print(temperaturaF); Serial.println(" grados F");
     delay(1000); 

//**************** PROFE : los if deben ir en una funcion ******************************************************
     
     if (temperaturaC>tempMaxima){
     digitalWrite(relayAbanico,HIGH);     //activar relay de Abanico
     digitalWrite(ledActuadores, HIGH);
     digitalWrite(ledOk, LOW);
     } else {
     digitalWrite(relayAbanico,LOW);       //apaga relay de Abanico
     digitalWrite(ledSistema, LOW);
     digitalWrite(ledOk, HIGH);
     }
      if (temperaturaC<tempMinima){
     digitalWrite(relayCalentador,HIGH);       //activar relay del calentador
     digitalWrite(ledSistema, HIGH);
     digitalWrite(ledOk, LOW);
     } else {
     digitalWrite(relayCalentador,LOW);       //apaga relay del calentador
     digitalWrite(ledSistema, LOW);
     digitalWrite(ledOk, HIGH);
     }
}
 
