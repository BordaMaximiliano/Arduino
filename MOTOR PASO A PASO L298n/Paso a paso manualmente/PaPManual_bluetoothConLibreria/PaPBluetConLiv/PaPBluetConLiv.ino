/* Motor Paso a Paso ajustado a grados
 by: www.elprofegarcia.com
   
Gira los grados que se le indiquen por bluetooth

Conexion  entre el Arduino y Modulo Bluetooth HC-06
Arduino   Bluetooth
  5V          VCC
  GND         GND
  2           TX
  3           RX
  
Conexion  entre el Arduino y Modulo Bluetooth HC-06
Arduino    Driver ULN200
  8          IN1
  9          IN2
  10         IN3
  11         IN4

 Nota:  La conexion de alimentacion del Driver  ULN200 debe ser externa, no se conecte al Arduino
        La fuente debe ser de 5Vdc y se recomienda unificar tierras con el Arduino
  
Tienda en Linea: http://dinastiatecnologica.com/
*/
#include <SoftwareSerial.h>

SoftwareSerial Serial_2 (2, 3);   //  Crea nueva conexion para el Bluetooth
                                  //  Pin2(RX) a TX y Pin3(TX) a RX
int retardo=2;          // Tiempo de retardo en milisegundos (Velocidad del Motor)
int dato_rx;            // valor recibido en grados
int numero_pasos = 0;   // Valor en grados donde se encuentra el motor
String leeCadena;       // Almacena la cadena de datos recibida

void setup() {                
Serial.begin(9600);     // inicializamos el puerto serie a 9600 baudios
Serial_2.begin(9600);   // Iniciamos el puerto nuevo Serial_2 a 9600 Baudios
pinMode(11, OUTPUT);    // Pin 11 conectar a IN4
pinMode(10, OUTPUT);    // Pin 10 conectar a IN3
pinMode(9, OUTPUT);     // Pin 9 conectar a IN2
pinMode(8, OUTPUT);     // Pin 8 conectar a IN1
}

void loop() {
  while (Serial_2.available()) {    // Leer el valor enviado por el Puerto serial
    delay(2);
    char c  = Serial_2.read();     // Lee los caracteres
    leeCadena += c;              // Convierte Caracteres a cadena de caracteres
  }  
  if (leeCadena.length()>0){       
        dato_rx = leeCadena.toInt();        // Convierte Cadena de caracteres a un numero Entero
        Serial.println(dato_rx);            // Envia valor en Grados 
        dato_rx = (dato_rx * 1.4222222222); // Ajuste de 512 vueltas a los 360 grados
  }  

  if ((dato_rx <= 512) && (dato_rx >= -512)){    // Descarta datos incorrectos recibidos
  
      while (dato_rx>numero_pasos){   // Girohacia la izquierda en grados
       paso_izq();
       numero_pasos = numero_pasos + 1;
      }
      while (dato_rx<numero_pasos){   // Giro hacia la derecha en grados
        paso_der();
        numero_pasos = numero_pasos -1;
      }
}

  leeCadena = "";   // Inicializamos la cadena de caracteres recibidos 
  apagado();         // Apagado del Motor para que no se caliente
}  ///////////////////// Fin del Loop ///////////////////////////

/********************************************************************/

//Modo de paso (Paso doble)
void paso_der(){         // Pasos a la derecha
 digitalWrite(11, LOW); 
 digitalWrite(10, LOW);  
 digitalWrite(9, HIGH);  
 digitalWrite(8, HIGH);  
   delay(retardo); 
 digitalWrite(11, LOW); 
 digitalWrite(10, HIGH);  
 digitalWrite(9, HIGH);  
 digitalWrite(8, LOW);  
   delay(retardo); 
 digitalWrite(11, HIGH); 
 digitalWrite(10, HIGH);  
 digitalWrite(9, LOW);  
 digitalWrite(8, LOW);  
  delay(retardo); 
 digitalWrite(11, HIGH); 
 digitalWrite(10, LOW);  
 digitalWrite(9, LOW);  
 digitalWrite(8, HIGH);  
  delay(retardo);  
}


//Modo de paso (Medio paso)
void paso_der_Medio(){         // Pasos a la derecha
 digitalWrite(11, HIGH); 
 digitalWrite(10, LOW);  
 digitalWrite(9, LOW);  
 digitalWrite(8, LOW);  
   delay(retardo); 
 digitalWrite(11, HIGH); 
 digitalWrite(10, HIGH);  
 digitalWrite(9, LOW);  
 digitalWrite(8, LOW);  
   delay(retardo); 
 digitalWrite(11, LOW); 
 digitalWrite(10, HIGH);  
 digitalWrite(9, LOW);  
 digitalWrite(8, LOW);  
  delay(retardo); 
 digitalWrite(11, LOW); 
 digitalWrite(10, HIGH);  
 digitalWrite(9, HIGH);  
 digitalWrite(8, LOW);  
  delay(retardo);  

  digitalWrite(11, LOW); 
 digitalWrite(10, LOW);  
 digitalWrite(9, HIGH);  
 digitalWrite(8, LOW);  
   delay(retardo); 
 digitalWrite(11, LOW); 
 digitalWrite(10, LOW);  
 digitalWrite(9, HIGH);  
 digitalWrite(8, HIGH);  
   delay(retardo); 
 digitalWrite(11, LOW); 
 digitalWrite(10, LOW);  
 digitalWrite(9, LOW);  
 digitalWrite(8, HIGH);  
  delay(retardo); 
 digitalWrite(11, HIGH); 
 digitalWrite(10, LOW);  
 digitalWrite(9, LOW);  
 digitalWrite(8, HIGH);  
  delay(retardo);  
}

//Modo de paso (Paso Simple)
void paso_der_Simple(){         // Pasos a la derecha
 digitalWrite(11, HIGH); 
 digitalWrite(10, LOW);  
 digitalWrite(9, LOW);  
 digitalWrite(8, LOW);  
   delay(retardo); 
 digitalWrite(11, LOW); 
 digitalWrite(10, HIGH);  
 digitalWrite(9, LOW);  
 digitalWrite(8, LOW);  
   delay(retardo); 
 digitalWrite(11, LOW); 
 digitalWrite(10, LOW);  
 digitalWrite(9, HIGH);  
 digitalWrite(8, LOW);  
  delay(retardo); 
 digitalWrite(11, LOW); 
 digitalWrite(10, LOW);  
 digitalWrite(9, LOW);  
 digitalWrite(8, HIGH);  
  delay(retardo);  
}

/****************************************************************/

void paso_izq() {        // Pasos a la izquierda
 digitalWrite(11, HIGH); 
 digitalWrite(10, HIGH);  
 digitalWrite(9, LOW);  
 digitalWrite(8, LOW);  
  delay(retardo); 
 digitalWrite(11, LOW); 
 digitalWrite(10, HIGH);  
 digitalWrite(9, HIGH);  
 digitalWrite(8, LOW);  
  delay(retardo); 
 digitalWrite(11, LOW); 
 digitalWrite(10, LOW);  
 digitalWrite(9, HIGH);  
 digitalWrite(8, HIGH);  
  delay(retardo); 
 digitalWrite(11, HIGH); 
 digitalWrite(10, LOW);  
 digitalWrite(9, LOW);  
 digitalWrite(8, HIGH);  
  delay(retardo); 
}
        
void apagado() {         // Apagado del Motor
 digitalWrite(11, LOW); 
 digitalWrite(10, LOW);  
 digitalWrite(9, LOW);  
 digitalWrite(8, LOW);  
 }

