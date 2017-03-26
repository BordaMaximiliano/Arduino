int Segundos = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(50, OUTPUT); // Led pin 13 
}

void loop() {
  // put your main code here, to run repeatedly:

 Regador();

}

void Regador()
{
   /*
  1min     60seg
  60min    3600seg = 1 hora.
  */
  Segundos ++;
  Serial.print("segundos");
  Serial.print(Segundos);
  if (Segundos % 10 == 0)
  {
    digitalWrite(50, HIGH);
  }else{
    digitalWrite(50, LOW);
  }
  

  delay(1000); //DELAY DE UN SEGUNDO.
}
