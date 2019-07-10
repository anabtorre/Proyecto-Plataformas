
const int sensor = A0;          //Pin en el que está conectado el sensor
const int Rc = 1000;            //Resistencia de calibración
const int relay = 2;            //Pin en en que está conectado el Relay            
int V;
int contador = 0;
long Rsensor;
long Resk;
unsigned float tr = 1;            //Tiempo de regado  en minutos                                   //AJUSTAR
unsigned float tespera = 10;      //Tiempo espera en minutos                                       //AJUSTAR
const int rr = 15;               //Resistencia (en kohmios) a partir de la cual empieza a regar   //AJUSTAR

void setup() {
  Serial.begin(9600);             //inicia comunicación serial
  pinMode (relay,OUTPUT);         //Configurar relay como salida
}
//INFO SOBRE SERIAL:
//   https://playground.arduino.cc/ArduinoNotebookTraduccion/Serial/
//Serial.begin:
//Establece la velocidad de datos en bits por segundo (baudios) para la transmisión de datos en serie. 
//Para comunicarse con el equipo, utilice uno de estos tipos: 300, 600, 1200, 2400, 4800, 9600, 14400, 19200, 28800, 38400, 57600 o 115200.

void loop() {
  V =  analogRead(sensor);        //leer sensor
  Rsensor = 1024L * Rc / V - Rc;  //calcular resistencia del sensor - la L lo hace un long
  //Si se hace operaciones matemáticas con enteros, al menos uno de los números debe estar seguido de una L, forzando a este número a ser un long
  Resk = Rsensor /1000;           //pasar a kiloohmios

  Serial.print(contador); Serial.println("  riegos.");  //contador para ver en serial cuantas veces se ha regado
Serial.print("Valor resistencia: "); Serial.print(Resk); Serial.println(" mil ohmios ");   //escribir en serial el valor de la resistencia
  delay(1000);

 if (Resk>rr){
  digitalWrite(relay,HIGH);       //activar relay
  delay(tr*60*1000);              // Espera Tiempo de regado con relay activado
  digitalWrite(relay,LOW);        //desactivar relay
  // Delay es una función que hace que el procesador espere
  delay(tespera*60*1000);         // Espera Tiempo de espera entre regados con relay desactivado para que el agua se filtre a la tierra y llegue al sensor
  contador = contador + 1 ;   
  }}
