#include "LiquidCrystal.h"
//***********//
//riego masetero: se comenzara el riego cuando el sensor de humedad este por debajo 
//                del parametro (valorHumedadRiego), 
//                y el sensor de luz indique que es de noche (valorLuzRiego)
//                o que se hayan superado los 5 dias sin riego (DiasEmergenciaRiego).
// 1 dia = 86400000 milisegundos
// 1 min  = 60 seg
// 1 dia = 86400 segundos.
//riego bonsai: 
//*******Manejo del LCD ***************//
// initialize the library by providing the nuber of pins to it
LiquidCrystal lcd(8,9,4,5,6,7);
int a=0; 
const int pantalla=53;
//*************************************//

//***** HUMEDAD ********//
const int pinHumedad = 2;
int valorSensorHumedad=0;
//***** FIN HUMEDAD ****//

//***** LUMINOSIDAD ****//
// Variable donde se almacena el valor del LDR = SENSOR DE LUMINOSIDAD.
int valoSensorLDR = 0; 
// Pin analogico de entrada para el LDR
int pinLDR = 0;
//***** FIN LUMINOSIDAD ****//

//***** RELE *******//
const int pinRelemasetero = 30;
const int pinRelebomsai = 31;
//***** FIN RELE *****//

//***** MANEJO RIEGO ******//
//Cada cuantos dias va a regar.
//ESTA REPRESENTADO EN SEGUNDOS. //1 dia = 86400 segundos.
const long DiasEmergenciaRiego = 4 * 86400L;
//const long DiasEmergenciaRiego = 25L;
//cuandto tiempo regara por emergencia.
//ESTA REPRESENTADO EN SEGUNDOS. //1 Minuto = 60 segundos. 
const long MaximoMinutosRegando = 3 * 60L;
//const long MaximoMinutosRegando = 1 * 60L;
//parametros de los sensores.
//const long valorHumedadRiego = 750;
const long valorHumedadRiego = 650;
const int valorLuzRiego = 800;

//tendra el tiempo transcurrido de riego por emergencia.
int MinutosRegandomasetero = 0;
long tiempominutosTranscurrido = 0L;
int estaRegandomasetero = 0;


//ESTA REPRESENTADO EN SEGUNDOS. //1 dia = 86400 segundos.
//const long DiasRiegoBonsai = 1 * 86400L;
//1 hora son 3600 segundos
const long DiasRiegoBonsai = 12 * 3600L;                                  //PARA PRUEBAS
//ESTA REPRESENTADO EN SEGUNDOS. //1 Minuto = 60 segundos. 
const long MaximoMinutosRegandoBonsai = 6 * 60L;

//const long DiasRiegoBonsai = 60L;                                   //PARA PRUEBAS
//const long MaximoMinutosRegandoBonsai = 1 * 10L;                   //PARA PRUEBAS

int estaRegandoBonsai = 0;

//es el total de minutos transcurridos para calcular diasRiegoBonsai.
long tiempominutosTranscurridoBonsai = 0L;
//long tiempominutosTranscurridoBonsai = 86390L;
int MinutosRegandoBonsai = 0;

int cantidadRiegosMasetero = 0;
int cantidadRiegoBonsai = 0;
int cantidadRiegosMaseteroEmerg = 0;
//***** FIN RIEGO ********//

//pin de pulsador
const int pulsador=52;
//pin para iluminar la pantalla
int estadopulsador=LOW;
long tiempoApagado=0L;
String incomingByte = "";

//****************************************************************************************//
void setup() {
  lcd.begin(16,2);
  //  Configurar el puerto serial
  Serial.begin(9600);

  
  pinMode(pulsador, INPUT);
  pinMode(pantalla, OUTPUT);
  //apago la pantalla
  digitalWrite(pantalla,LOW);
}

//****************************************************************************************//
void loop()
{

  if (Serial.available() > 0) {
      // read the incoming byte:
      //incomingByte = Serial.readBytes();
    
      // say what you got:
      Serial.print("I received: ");
      Serial.println(incomingByte);
  }
  
  // turn off automatic scrolling
  lcd.noAutoscroll();
  lcd.clear();
  //Ya que el delay de cada 1 segundo.
  //al sumar uno estoy sumando 1 segundo.
  tiempoApagado = tiempoApagado + 1;
  tiempominutosTranscurrido = tiempominutosTranscurrido +1;
  tiempominutosTranscurridoBonsai = tiempominutosTranscurridoBonsai +1;
  
  // Guardamos el valor leido del ADC en una variable
  // El valor leido por el ADC (voltaje) aumenta de manera directamente proporcional
  // con respecto a la luz percibida por el LDR
  valoSensorLDR= analogRead(pinLDR);
  valorSensorHumedad = analogRead(pinHumedad);
  
  //********Pulsador prender pantalla**********
  //leo el pulsador.
  estadopulsador= digitalRead(pulsador);
  if(estadopulsador==HIGH){
    digitalWrite(pantalla,HIGH);
    tiempoApagado=0;    
  }
  //es porque el tiempo es cada 5 segundos.
  if (tiempoApagado == 10 ){
    digitalWrite(pantalla,LOW);    
  }
  //*************FIN Pulsador************
   
  // Devolver el valor leido a nuestro monitor serial en el IDE de Arduino
  Serial.println(valoSensorLDR);
  Serial.println(valorSensorHumedad);
  
  
  a = 10;
  MostrarPantallaLuz(valoSensorLDR);
  MostrarPantallaHumedad(valorSensorHumedad) ;

  RegadorMasetero(valorSensorHumedad,valorHumedadRiego,tiempominutosTranscurrido);
  RegadorBonsai();
  
  //delay de 1 segundo.
  //Osea el loop se hara cada 1 segundo.
  //digitalWrite(46,HIGH);
  //lcd.clear();
  delay(1000);
  //digitalWrite(46,LOW);
  lcd.clear();

}
//***********************************************************************************//
//**MANEJO LCD**//
void MostrarPantallaLuz(int valor){
  String mensaje="LUZ:";
  mensaje.concat(valor);
  mensaje.concat(" CRB:");
  mensaje.concat(cantidadRiegoBonsai);
  
  MostrarMensaje(mensaje,0);
}
void MostrarPantallaHumedad(int valor){
  String mensaje="HUM:";
  mensaje.concat(valor);
  mensaje.concat(" CRM:");
  mensaje.concat(cantidadRiegosMasetero);
  
  MostrarMensaje(mensaje,1);
}
void MostrarMensaje(String mensaje, int linea){
  lcd.setCursor(0,linea);
  lcd.print(mensaje);
}
//**FIN MANEJO LCD**//

//**PROCESO RIEGO **//
//******************************************* MASETERO * ***********************************
void RegadorMasetero(int p_valorSensorHumedad,long p_constvalorHumedadRiego,  long p_tiempominutosTranscurrido )
{
  String mensajeerr="EMERGENCIA LL: ";
  mensajeerr.concat(p_valorSensorHumedad);
  String mensajeMostrar="";
  //1 dia = 86400 segundos.
  //Riego de emergencia.
  //entra si el tiempo transcurrido es mayor al riego de emergencia.
  //RIEGO DE EMERGENCIA.

  mensajeMostrar = "tiempo transcurridos: " ;  
  mensajeMostrar.concat(p_tiempominutosTranscurrido);
  Serial.println(mensajeMostrar);
  mensajeMostrar = "Dias de emergencia: " ;  
  mensajeMostrar.concat(DiasEmergenciaRiego);
  Serial.println(mensajeMostrar);

  mensajeMostrar = "Evaluara si entra en modo de emergencia " ;  
  Serial.println(mensajeMostrar);

  
  mensajeMostrar = "Cantidad Riegos de masetero = " ;  
  mensajeMostrar.concat(cantidadRiegosMasetero);
  Serial.println(mensajeMostrar);

  mensajeMostrar = "Cantidad Riegos de masetero Emergencia = " ;  
  mensajeMostrar.concat(cantidadRiegosMaseteroEmerg);
  Serial.println(mensajeMostrar);
  
  
  if(p_tiempominutosTranscurrido > DiasEmergenciaRiego ){

    MostrarMensaje(mensajeerr,1);

    mensajeMostrar = "ENTRO EN MODO DE EMERGENCIA" ;  
    Serial.println(mensajeMostrar);
    
    MinutosRegandomasetero = MinutosRegandomasetero +1;
    
    //Si la tierra esta seca realiza el riego. para no inundar la tierra.
    //if(p_valorSensorHumedad > p_constvalorHumedadRiego){
    
        //si pasaron los minutos de riego ahi si se reestablece tiempo transcurrido a cero.
        //si los minutos de riego transcurrido son menores a los seteados comienza el riego sino para.
        if(MinutosRegandomasetero < MaximoMinutosRegando ){ 
            //si no esta regando, comienza riego.
            if(estaRegandomasetero == 0){           
              ActivarRele(pinRelemasetero,HIGH);
              estaRegandomasetero = 1;
              mensajeMostrar = "se activa riego de emergencia" ;  
              cantidadRiegosMaseteroEmerg = cantidadRiegosMaseteroEmerg +1;
              Serial.println(mensajeMostrar);
            }      
            
        }else{ //se para el riego porque supero los minutos.
            ActivarRele(pinRelemasetero,LOW);
            estaRegandomasetero = 0;   
            MinutosRegandomasetero=0;   
            tiempominutosTranscurrido=0;
            mensajeMostrar = "***************se apaga el riego**************" ;  
            Serial.println(mensajeMostrar);
        }
    /*}else{
      //si tierra esta humeda porque llovio vuelve a comenzar el contador de dias.
      tiempominutosTranscurrido=0;      
    }*/
    
  }else{

    mensajeMostrar = "ENTRO EN MODO NORMAL" ;  
    Serial.println(mensajeMostrar);
    
    mensajeMostrar = "Evaluara sensores humedad: " ;  
    mensajeMostrar.concat(p_valorSensorHumedad);
    Serial.println(mensajeMostrar);

    mensajeMostrar = "Valor constante de humedad: " ;  
    mensajeMostrar.concat(p_constvalorHumedadRiego);
    Serial.println(mensajeMostrar);
  

    //RIEGO NORMAL POR SENSOR DE HUMEDAD.
    if(p_valorSensorHumedad <= p_constvalorHumedadRiego & valoSensorLDR < valorLuzRiego )
    {
        Serial.println("riego por sensor H");

        mensajeMostrar = "esta regando?: " ;  
        mensajeMostrar.concat(estaRegandomasetero);
        Serial.println(mensajeMostrar);
        
        if(estaRegandomasetero == 0){
          
          //habria que agregar un if para ver si supero el tiempo maximo de riego pare el mismo.
          //esto se coloca por si fallo el sensor de humedad o luz.
          ActivarRele(pinRelemasetero,HIGH);
          estaRegandomasetero = 1;
          tiempominutosTranscurrido=0;
          mensajeMostrar = "se activa riego NORMAL" ;  
          cantidadRiegosMasetero = cantidadRiegosMasetero +1;
          Serial.println(mensajeMostrar);
        }
        
    }else{
      
        ActivarRele(pinRelemasetero,LOW);
        estaRegandomasetero = 0;
        mensajeMostrar = "***************se apaga el riego Modo normal**************" ;  
        Serial.println(mensajeMostrar);
        
    }
    
  }
  
}
//******************************************** BONSAI ***************************************************************
void RegadorBonsai()
{
     String mensajeMostrar="";
    mensajeMostrar = "tiempo transcurridos: " ;  
    mensajeMostrar.concat(tiempominutosTranscurridoBonsai);
    Serial.println(mensajeMostrar);
    mensajeMostrar = "Dias de emergencia: " ;  
    mensajeMostrar.concat(DiasRiegoBonsai);
    Serial.println(mensajeMostrar);
  
    mensajeMostrar = "Evaluara si entra en modo de emergencia" ;  
    Serial.println(mensajeMostrar);

    mensajeMostrar = "Cantidad Riegos de Bonsai = " ;  
    mensajeMostrar.concat(cantidadRiegoBonsai);
    Serial.println(mensajeMostrar);
    
    mensajeMostrar = "Tiempo transcurrido bonsai " ;  
    mensajeMostrar.concat(tiempominutosTranscurridoBonsai);
    Serial.println(mensajeMostrar);

    mensajeMostrar = "Dias de riego " ;  
    mensajeMostrar.concat(DiasRiegoBonsai);
    Serial.println(mensajeMostrar);

    //si es momneto de regaar y es de noche entra 
    if(tiempominutosTranscurridoBonsai > DiasRiegoBonsai & valoSensorLDR < valorLuzRiego ){
  
      
  
      //mensajeMostrar = "REGANDO BONSAIS" ;  
      //Serial.println(mensajeMostrar);  
      
      
      
          //si pasaron los minutos de riego ahi si se reestablece tiempo transcurrido a cero.
          //si los minutos de riego transcurrido son menores a los seteados comienza el riego sino para.
          if(MinutosRegandoBonsai < MaximoMinutosRegandoBonsai ){ 

                MinutosRegandoBonsai = MinutosRegandoBonsai +1;
          
                //si no esta regando, comienza riego.
                if(estaRegandoBonsai == 0){           
                  ActivarRele(pinRelebomsai,HIGH);
                  estaRegandoBonsai = 1;
                  mensajeMostrar = "se activa riego de BONSAI";  
                  cantidadRiegoBonsai = cantidadRiegoBonsai +1;
                  Serial.println(mensajeMostrar);
                }      
                
            
          }else{ //se para el riego porque supero los minutos.
              ActivarRele(pinRelebomsai,LOW);
              estaRegandoBonsai = 0;                 
              MinutosRegandoBonsai=0;   
              tiempominutosTranscurridoBonsai=0;
              mensajeMostrar = "***************se apaga el riego**************" ;  
              Serial.println(mensajeMostrar);
          }   
      
    }
}

void ActivarRele(int pin, int estado)
{//estado = LOW o HIGH
  digitalWrite(pin,estado); 
}
//**FIN PROCESO RIEGO**//
