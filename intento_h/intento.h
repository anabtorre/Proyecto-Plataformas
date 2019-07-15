
#include "DHT.h"
//Para conexion Bluetooth:
#include <SoftwareSerial.h> 

#define DHTTYPE DHT21   // DHT 21 (AM2301)
#define DHTPIN 3
DHT dht(DHTPIN, DHTTYPE);    /*Se inicia una variable que sera usada*/

/*Parámetros del control sobre la temperatura y humedad*/
float humLeida, tempLeida  ;

//int tempIdeal;
//int humRIdeal;
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

char NOMBRE[10]  = "HC06";        /* Nombre asignado para nuestro módulo de Bluetooth: por defecto*/
char BPS         = '4';           /* 4=9600 Baudios*/
char PASS[10]    = "0000";        /*clave de acceso al dispositivo*/
SoftwareSerial BT1(0, 1); // RX | TX


////////////FUNCIONES//////////

void conexionSerialBt();
void serialBT();
void controlTempHum(int tempMax,int tempMin,int humMin,int humMax);
void controlHumPiso(int lecturaHigrom);
