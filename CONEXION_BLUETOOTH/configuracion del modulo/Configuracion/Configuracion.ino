/*
Algunos comandos AT:
AT+RESET - Reinicia el módulo
AT+ORGL - Valores de fabrica
AT+NAMExxxxx - Cambiar nombre
AT+BAUDx - Cambiar velocidad
AT+PINxxxx - Cambiar PIN de conexion
*/
#define CARACTER_INICIO_CMD '*'
#define CARACTER_FINAL_CMD '#'
#define CARACTER_DIV_CMD '|'
#define ESCRITURA_DIGITAL_CMD 10
#define ESCRITURA_ANALOGA_CMD 11
#define TEXTO_CMD 12
#define LECTURA_ARDUDROID_CMD 13
#define MAX_COMMAND 20  
#define MIN_COMMAND 10 
#define LONGITUD_ENTRADA_STRING 40
#define ESCRITURA_ANALOGICA_MAX 255
#define PIN_ALTO 3
#define PIN_BAJO 2

const int LED = 13;
const int BTPWR = 53;

char nombreBT[20] = "pruebaBT";
char velocidad ='4'; //9600
char pin[5]= "1111";

void setup(){
  
    pinMode(LED, OUTPUT);
    pinMode(BTPWR, OUTPUT);
  
    digitalWrite(LED, LOW);
    digitalWrite(BTPWR, HIGH);
  
    Serial.begin(9600);
  
    Serial.print("AT");
    delay(1000);
  
    Serial.print("AT+NAME");
    Serial.print(nombreBT);
    delay(1000);
  
    Serial.print("AT+BAUD");
    Serial.print(velocidad);
    delay(1000);
  
    Serial.print("AT+PIN");
    Serial.print(pin);
    delay(1000);
  
    digitalWrite(LED, HIGH);
}

void loop(){
  
   
  
}

