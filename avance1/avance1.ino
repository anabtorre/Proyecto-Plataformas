/**
* Sensor de temperatura simple TMP36
*Sensor Higrometro: YL-69, modulo comparador: LM393
*Sensor temperatura y humedad: dth22 modelo am2301
*Salidas de Relays: Bomba (relayBombaHg, 2). Abanico (relayFanTemp,1).
*
*Ana b. Torre b36963
*Jose M. Hidalgo B63466
*/

const int sensorHg = A0;                              //Pin en el que está conectado el sensor Higrometro
const int sensorTemp=A1;                               //Pin en el que está conectado el sensor de SOLO Temperatura
const int resistenciaCalibracionHg = 1000;            //Resistencia de calibración Higrometro
const int relayBombaHg = 2;                     //Pin en el que está conectado el relay de la Bomba que se activa o no segun medicion del Higrometro            
const int relayFanTemp=1;                      //Pin en el que está conectado el relay del abanico que se enciende o no segun medicion de Temperatura
const int relayCalentador=3;
                                     //Tensión por parte de los sensores de temperatura y humedad
int ledSistema=13;                   //LED que debe encenderse si abanico o calentador estan encendidos
int ledOk=12;

int tensionHg;                  //Tension del Higrometro
int tensionTemp;
 
int contadorRiego = 0;             // contador para ver cuantas veces se ha regadp
long Rsensor;                       //valor de la resistencia del sensor de humedad piso en ohm
long Resk;                         // misma resistencia que Rsensor,pero en kohm

//variables del sistema de riego
unsigned long tiempoRiego = 0.1;                    //Tiempo de regado  en minutos //PROBAR cuanto tiempo se ocupa                          
unsigned long tiempoEspera = 10;                    //Tiempo espera en minutos                                       
const int resistenciaSuelo = 15;                    //Resistencia (en kohmios) a partir de la cual empieza a regar 

const int tempMaxima=24;                            //valor a CAMBIAR
const int tempMinima=22;                            //valor a CAMBIAR

void setup() {
  Serial.begin(9600);                          //inicia comunicación serial
  pinMode (relayBombaHg,OUTPUT);               //Configurar relayBombaHg como salida
  pinMode (relayFanTemp,OUTPUT);               //Configurar relayBombaHg como salida  
  pinMode(ledSistema, OUTPUT);                     //Configuramos el led como salida si abanicos o calentador estan trabajando
  pinMode(ledOk, OUTPUT);                      //Configuramos el led como salida en 
}

void loop() {

  //tensionHg =  analogRead(sensorHg);                                                  //leer sensor higrometro
 // Rsensor = 1024L * resistenciaCalibracionHg / tensionHg - resistenciaCalibracionHg;  //calcular resistencia del sensor (divisor tension)
 // Resk = Rsensor /1000;                                                                //pasar a kiloohmios

  //Serial.print(contadorRiego); Serial.println("  riegos.");                                   //contadorRiego para ver en serial cuantas veces se ha regado
  //Serial.print("Valor resistencia: "); Serial.print(Resk); Serial.println(" mil ohmios ");   //escribir en serial el valor de la resistencia
//  delay(1000);

 /**if (Resk>resistenciaSuelo){
  digitalWrite(relayBombaHg,HIGH);       //activar relayBombaHg
  //Serial.print("Valor resistencia: ")
  delay(tiempoRiego*60*1000);              // Espera Tiempo de regado con relayBombaHg activado
  digitalWrite(relayBombaHg,LOW);        //desactivar relayBombaHg
  delay(tiempoEspera*60*1000);         // Espera Tiempo de espera entre regados con relayBombaHg desactivado para que el agua se filtre a la tierra y llegue al sensor
  contadorRiego = contadorRiego + 1 ;   
  }
*/
     int lecturaTemp = analogRead(sensorTemp);  
     float vTemp = lecturaTemp * 5.0;
     vTemp /= 1024.0; 
     Serial.print(vTemp); Serial.println(" voltaje Temperatura");
     float temperaturaC = (vTemp - 0.5) * 100 ; 
     Serial.print(temperaturaC); Serial.println(" grados C");
     float temperaturaF = (temperaturaC * 9.0 / 5.0) + 32.0;
     Serial.print(temperaturaF); Serial.println(" grados F");
     delay(1000); 
     
     if (temperaturaC>tempMaxima){
     digitalWrite(relayFanTemp,HIGH);     //activar relay de Abanico
     digitalWrite(ledSistema, HIGH);
     digitalWrite(ledOk, LOW);
     } else {
     digitalWrite(relayFanTemp,LOW);       //apaga relay de Abanico
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
 
