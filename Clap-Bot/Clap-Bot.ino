// LIBRERIAS
#include <Servo.h>

// DEFINICIONES
#include "Definiciones/def_clap_bot.h"
         
int lecturaMicrofono=0; // GUARDAR LECTURA DEL MICROFONO

int a=0;                //FLAG QUE CONTARA EL NUMERO DE APLAUSOS 
int b=0;                //FLAG PARA SALIR DE BUCLE (Comienza Apagado)

unsigned long tiempoAntes = millis();

Servo servo;

//Metodos Servomotor
void encenderLuz();
void apagarLuz();


void setup(){ 

    Serial.begin(9600);         // COMUNICACION SERIAL
    pinMode(Microfono, INPUT);  // MICROFONO - ENTRADA DE SEÑAL 
    servo.attach(servoPin);     // ESTABLEZCO PIN PARA MOVIMIENTO DEL SERVOMOTOR
    servo.write(pos_inicial);   // ESTABLEZCO LA POSICIÓN INICIAL DEL SERVOMOTOR
}


void loop(){
    unsigned long tiempoDespues = millis();   // TIEMPO DESPUES DE LA LECTURA

    lecturaMicrofono=digitalRead (Microfono); // LEER ESTADO DEL MICROFONO
    
    delay(10);
    if(lecturaMicrofono == 1){
        if(tiempoDespues - tiempoAntes >= intervalo){   // VALIDO QUE HAYA CIERTO TIEMPO ENTRE CADA APLAUSO
            a++;
            tiempoAntes = tiempoDespues;
        }
    }

    if(tiempoDespues - tiempoAntes >= 1000){  // SI PASO UN SEGUNDO, VALIDO SI HUBO APLAUSOS

        if (a==2 && b==1){       // 2 APALUSOS Y FOCO ENCENDIDO, ENTONCES APAGAMOS EL FOCO
            Serial.println ("APAGADO"); 
            apagarLuz();        // APAGAR FOCO
            b = 0;
        }
        else if(a==2 && b==0){   // 2 APLAUSOS Y FOCO APAGADO, ENTONCES ENCENDEMOS EL FOCO
            Serial.println("ENCENDIDO");
            encenderLuz();       // ENCENDER FOCO
            b=1;
        }

        a=0;
        tiempoAntes = tiempoDespues;
      }
    
}

// MOVIMIENTO DEL SERVOMOTOR PARA APAGAR
void apagarLuz(){
  int i;
  i = 0;

  Serial.println("Apagando Luz...");
  for(i = pos_inicial; i>pos_apagado; i--){
    servo.write(i);
    delay(20);
  }
  delay(200);

  servo.write(pos_inicial);             // VUELVO A POSICION INICIAL
  Serial.println("Luz Apagada...");
  
}

// MOVIMIENTO DEL SERVOMOTOR PARA ENCENDER
void encenderLuz(){
  int i;
  i = 0;

  Serial.println("Encendiendo Luz...");
  for(i = pos_inicial; i<pos_encendido; i++){
    servo.write(i);
    delay(20);
  }
  delay(200);

  servo.write(pos_inicial);             // VUELVO A POSICION INICIAL
  Serial.println("Luz Encendida...");

}
