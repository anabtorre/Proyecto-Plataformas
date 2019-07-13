
//Sensor Higrometro: YL-69, modulo comparador: LM393
//YA TODO EN AVANCE2

#include "libreria_higrometro.h"
void setup()
{
  Serial.begin(9600);
  pinMode(relayBombaHg,OUTPUT); 
  pinMode(ledBomba, OUTPUT);
  pinMode(higrometro, OUTPUT);
}
void lectura(){
  int lecturaHigrom = analogRead(higrometro);   //Lee entrada del higrometro
  //Los siguientes valores (400 y 1023 hay que establecer si son esos)
  lecturaHigrom = constrain(lecturaHigrom,400,1023);  //Constrain limita el rango del sensor (lecturaHigrom) entre 400 y 1023
  //Retorna lecturaHigrom si este esta entre 400 y 1023, retorna 400 si lecturaHigrom es menor que 400, retorna  1023 si lecturaHigrom es mayor que 1023.
  //O sea, si esta dentro del rango retorne lo que es, si esta para abajo del minimo retorne ese minimo, y si esta para abajo del maximo, retorne ese maximo
  lecturaHigrom = map(lecturaHigrom,400,1023,100,0);  //Mapeo. Ahora 400 va a ser 100 (minimo) 1023 va a ser 0 (maximo)

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

void loop()
{
  lectura();
}
