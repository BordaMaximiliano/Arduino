//Projeto Arduino+Bluetooth+Android - Evandro Sperandiu Gonçaves
//evandrosg@gmail.com

char buffer[67];

byte Pino02 = 2;
byte Pino03 = 3;
byte Pino04 = 4;
byte Pino05 = 5;
byte Pino06 = 6;
byte Pino07 = 7;
byte Pino08 = 8;
byte Pino09 = 9;
byte Pino10 = 10;
byte Pino11 = 11;
byte Pino12 = 12;
byte Pino13 = 13;
byte PinoA0 = A0;
byte PinoA1 = A1;
byte PinoA2 = A2;
byte PinoA3 = A3;
byte PinoA4 = A4;
byte PinoA5 = A5;

void setup(){
  Serial.begin(9600);
  Serial.flush();
  pinMode(Pino02, OUTPUT);
  pinMode(Pino03, OUTPUT);
  pinMode(Pino04, OUTPUT);
  pinMode(Pino05, OUTPUT);
  pinMode(Pino06, OUTPUT);
  pinMode(Pino07, OUTPUT);
  pinMode(Pino08, OUTPUT);
  pinMode(Pino09, OUTPUT);
  pinMode(Pino10, OUTPUT);
  pinMode(Pino11, OUTPUT);
  pinMode(Pino12, OUTPUT);
  pinMode(Pino13, OUTPUT);
  pinMode(PinoA0, OUTPUT);
  pinMode(PinoA1, OUTPUT);
  pinMode(PinoA2, OUTPUT);
  pinMode(PinoA3, OUTPUT);
  pinMode(PinoA4, OUTPUT);
  pinMode(PinoA5, OUTPUT);
}
void loop(){
  if (Serial.available()>0){
    int index=0;
    delay(100);//deixe o buffer encher
    int numChar = Serial.available();
    if(numChar>65){
      numChar=65;
    }
    while(numChar--){
      buffer[index++] = Serial.read();
    }
    splitString(buffer);
  }
}
void splitString(char* data){
  Serial.print("Dados inseridos: ");
  Serial.println(data);
  char* parameter;
  parameter= strtok (data, " ,");
  while(parameter != NULL){
    setLED(parameter);
    parameter = strtok (NULL, " ,");
  }
  //Limpa o texto e os buffers seriais
  for (int x=0; x<66; x++){
    buffer[x]='\0';
  }
  Serial.flush();
}
void setLED(char* data){
  Serial.print("Dados inseridos: ");
  Serial.println(data[10]);
  if ((data[10] =='a') || (data[10] == 'A')){
    int Ans = strtol(data+1, NULL, 10);
    Ans = constrain(Ans,0,1);
    Serial.print("valor: ");
    Serial.println(Ans);
    digitalWrite(Pino02, Ans);
    Serial.print("Pino02 esta em: ");
    Serial.println(Ans);
  }
  if ((data[11] =='b') || (data[11] == 'B')){
    int Ans = strtol(data+1, NULL, 10);
    Ans = constrain(Ans,0,255);
    analogWrite(Pino03, Ans);
    Serial.print("Pino03 esta em: ");
    Serial.println(Ans);
  }
  if ((data[11] =='c') || (data[11] == 'C')){
    int Ans = strtol(data+1, NULL, 10);
    Ans = constrain(Ans,0,1);
    digitalWrite(Pino04, Ans);
    Serial.print("Pino04 esta em: ");
    Serial.println(Ans);
  }
  if ((data[11] =='d') || (data[11] == 'D')){
    int Ans = strtol(data+1, NULL, 10);
    Ans = constrain(Ans,0,255);
    analogWrite(Pino05, Ans);
    Serial.print("Pino05 esta em: ");
    Serial.println(Ans);
  }
  if ((data[0] =='e') || (data[0] == 'E')){
    int Ans = strtol(data+1, NULL, 10);
    Ans = constrain(Ans,0,255);
    analogWrite(Pino06, Ans);
    Serial.print("Pino06 esta em: ");
    Serial.println(Ans);
  }
  if ((data[0] =='f') || (data[0] == 'F')){
    int Ans = strtol(data+1, NULL, 10);
    Ans = constrain(Ans,0,1);
    digitalWrite(Pino07, Ans);
    Serial.print("Pino07 esta em: ");
    Serial.println(Ans);
  }
  if ((data[0] =='g') || (data[0] == 'G')){
    int Ans = strtol(data+1, NULL, 10);
    Ans = constrain(Ans,0,1);
    digitalWrite(Pino08, Ans);
    Serial.print("Pino08 esta em: ");
    Serial.println(Ans);
  }
  if ((data[0] =='h') || (data[0] == 'H')){
    int Ans = strtol(data+1, NULL, 10);
    Ans = constrain(Ans,0,255);
    analogWrite(Pino09, Ans);
    Serial.print("Pino09 esta em: ");
    Serial.println(Ans);
  }
  if ((data[0] =='i') || (data[0] == 'I')){
    int Ans = strtol(data+1, NULL, 10);
    Ans = constrain(Ans,0,255);
    analogWrite(Pino10, Ans);
    Serial.print("Pino10 esta em: ");
    Serial.println(Ans);
  }
  if ((data[0] =='j') || (data[0] == 'J')){
    int Ans = strtol(data+1, NULL, 10);
    Ans = constrain(Ans,0,255);
    analogWrite(Pino11, Ans);
    Serial.print("Pino11 esta em: ");
    Serial.println(Ans);
  }
  if ((data[0] =='k') || (data[0] == 'K')){
    int Ans = strtol(data+1, NULL, 10);
    Ans = constrain(Ans,0,1);
    digitalWrite(Pino12, Ans);
    Serial.print("Pino12 esta em: ");
    Serial.println(Ans);
  }
  if ((data[0] =='l') || (data[0] == 'L')){
    int Ans = strtol(data+1, NULL, 10);
    Ans = constrain(Ans,0,1);
    digitalWrite(Pino13, Ans);
    Serial.print("Pino13 esta em: ");
    Serial.println(Ans);
  }
  if ((data[0] =='m') || (data[0] == 'M')){
    int Ans = strtol(data+1, NULL, 10);
    Ans = constrain(Ans,0,1);
    digitalWrite(PinoA0, Ans);
    Serial.print("PinoA0 esta em: ");
    Serial.println(Ans);
  }
  if ((data[0] =='n') || (data[0] == 'N')){
    int Ans = strtol(data+1, NULL, 10);
    Ans = constrain(Ans,0,1);
    digitalWrite(PinoA1, Ans);
    Serial.print("PinoA1 esta em: ");
    Serial.println(Ans);
  }
  if ((data[0] =='o') || (data[0] == 'O')){
    int Ans = strtol(data+1, NULL, 10);
    Ans = constrain(Ans,0,1);
    digitalWrite(PinoA2, Ans);
    Serial.print("PinoA2 esta em: ");
    Serial.println(Ans);
  }
  if ((data[0] =='p') || (data[0] == 'P')){
    int Ans = strtol(data+1, NULL, 10);
    Ans = constrain(Ans,0,1);
    digitalWrite(PinoA3, Ans);
    Serial.print("PinoA3 esta em: ");
    Serial.println(Ans);
  }
  if ((data[0] =='q') || (data[0] == 'Q')){
    int Ans = strtol(data+1, NULL, 10);
    Ans = constrain(Ans,0,1);
    digitalWrite(PinoA4, Ans);
    Serial.print("PinoA4 esta em: ");
    Serial.println(Ans);
  }
  if ((data[0] =='r') || (data[0] == 'R')){
    int Ans = strtol(data+1, NULL, 10);
    Ans = constrain(Ans,0,1);
    digitalWrite(PinoA5, Ans);
    Serial.print("PinoA5 esta em: ");
    Serial.println(Ans);
  } 
}
