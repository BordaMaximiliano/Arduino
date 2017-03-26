// https://www.youtube.com/watch?v=gzNP6-GI7Cc&t=4s
// Gm25 Electrônica y Mas !!
// le presentamos un programa basico para el uso del dirver A4988
// dale me gusta a nuestros video nos ayudara de mucho, y suscribete 
//para mas tutuoriales !!



const int steppin = 7;  // declaramos el pin 10 del arduino como step
const int dirpin = 4;  // declaramos el pin 12 del arduino con dir
int tiempo = 10;       // declaramos la variable tiempo  como (5 milisegundos) cuanto menos va mas rapido.
int pasos = 12;       //propiedad del motor, en 48 pasos del motor da un giro completo.
int reset = 10;

int pasosTotal = 0;
int GiroDerecha = 1;

void setup() {
  
  pinMode(steppin,OUTPUT); // declaramos como salidas
  pinMode(dirpin,OUTPUT);  // declaramos como salida
}

void loop() {
  
  GiroDerecha = 1;
  //digitalWrite(dirpin,GiroDerecha);  //  ponemos en alto o 1 logico a pin dir para que gire hacia un sentido
  Girar(pasos,GiroDerecha);
  delay(1000);                    // cuando  termine el lazo for , descanzara 1 segundo o 1000 milisegundos  

  GiroDerecha = 0;
  
  //digitalWrite(dirpin,GiroDerecha);     //   pones en bajo , o en 0 logico para que gire el el sentido opuesto
  Girar(pasos*2,GiroDerecha);  
  delay(5000);  

 

}



void Girar(int pasosAdar, int GiroDerecha )
{
    digitalWrite(dirpin,GiroDerecha);
    for(int x = 0; x < pasosAdar; x++){  // creamos un lazo for , en nuetro caso el  motor es de 200 paso, para dar  una vuelta !
      digitalWrite(steppin,HIGH);  // las intrucciones que se encuntran dentro  del lazo
      delay(tiempo);               // son las que aran que nuestro motor se mueva ,es la parte donde van los pulsos
      digitalWrite(steppin,LOW);   // necesarios para que el motor se mueva 
      delay(tiempo);
      pasosTotal++;
    }  
}

