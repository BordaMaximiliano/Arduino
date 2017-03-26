/*
  www.diymakers.es
  by A.García
  Mover motores paso a paso con Arduino
  Tutorial en: http://diymakers.es/mover-motores-paso-paso-con-arduino/
*/
 
#include <Stepper.h> //Importamos la librería para controlar motores paso a paso

 //a cuantos pasos va el motor, se setea por motor.
#define STEPS 48 //Ponemos el número de pasos que necesita para dar una vuelta. 48 en nuestro caso
 
// Ponemos nombre al motor, el número de pasos y los pins de control
Stepper stepper(STEPS, 8, 9, 10, 11); //Stepper nombre motor (número de pasos por vuelta, pins de control)
 
void setup()
{
  // Velocidad del motor en RPM 180 = 3 vueltas por segundo.
  stepper.setSpeed(180); 
}
 
void loop()
{

/*
  stepper.setSpeed(50);
  //Girar una vuelta entera en un sentido 48 = 1 giro o 360 grados.
  stepper.step(150);
  delay(1000); //Pequeña pausa
 
  //Girar una vuelta entera en sentido contrario
  //Si se seteo que el motor es de 48 pasos por vuelta en la funcion deberemos de definir cuantos pasos ordenaremos, en el caso 
  //de colocar 48 le estaremos diciendo que de una vuelta.
  stepper.step(-48);
  delay(1000); //Pequeña pausa

  stepper.setSpeed(180);
  stepper.step(150);
  delay(1000); //Pequeña pausa
  */
  stepper.step(1);
  delay(2000); //Pequeña pausa
  
}

