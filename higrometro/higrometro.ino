//*Sensor Higrometro: YL-69, modulo comparador: LM393
//YA TODO EN AVANCE2

const int relayBombaHg = 6; //Bomba que se activa cuando la humedad esta baja. En el pin 2 del relay
const int higrometro = A0;  // Higrometro conectado a pin A0 del arduino
//Variables 
int lecturaHigrom; 
int ledBomba=12;
void setup()
{
  Serial.begin(9600);
  pinMode(relayBombaHg,OUTPUT); 
  pinMode(ledBomba, OUTPUT);
  pinMode(higrometro, OUTPUT);
}

void loop()
{
  // Cuando el hongo tiene suficiente humedad en la tierra, el sensor va a leer entre 380-400
 // podria cambiarse el 400 a un valor mas bajo 
  
  lecturaHigrom = analogRead(higrometro);   //Lee entrada del higrometro
  //Los siguientes valores (400 y 1023 hay que establecer si son esos)
  lecturaHigrom = constrain(lecturaHigrom,400,1023);  //Constrain limita el rango del sensor (lecturaHigrom) entre 400 y 1023
  //Retorna lecturaHigrom si este esta entre 400 y 1023, retorna 400 si lecturaHigrom es menor que 400, retorna  1023 si lecturaHigrom es mayor que 1023.
  //O sea, si esta dentro del rango retorne lo que es, si esta para abajo del minimo retorne ese minimo, y si esta para abajo del maximo, retorne ese maximo
  lecturaHigrom = map(lecturaHigrom,400,1023,100,0);  //Mapeo. Ahora 400 va a ser 100 (minimo) 1023 va a ser 0 (maximo)

  Serial.print("Humedad:");
  Serial.print (lecturaHigrom);
  Serial.println("%");
  //Si la humedad baja del 20%, enciende la bomba, sino se mantiene apagada
  if (lecturaHigrom < 20){
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
