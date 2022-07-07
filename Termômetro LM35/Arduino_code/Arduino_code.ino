#include <TimerOne.h>

char count1 = 0;
char count2 = 0;
int displayActive = 10;

byte seven_seg_digits[16][7] = { { 1,1,1,1,1,1,0 },  // = Digito 0
                                 { 0,1,1,0,0,0,0 },  // = Digito 1
                                 { 1,1,0,1,1,0,1 },  // = Digito 2
                                 { 1,1,1,1,0,0,1 },  // = Digito 3
                                 { 0,1,1,0,0,1,1 },  // = Digito 4
                                 { 1,0,1,1,0,1,1 },  // = Digito 5
                                 { 1,0,1,1,1,1,1 },  // = Digito 6
                                 { 1,1,1,0,0,0,0 },  // = Digito 7
                                 { 1,1,1,1,1,1,1 },  // = Digito 8
                                 { 1,1,1,0,0,1,1 },  // = Digito 9
                                 };
void setup() 
{  
  pinMode(2, OUTPUT); //Pino 2 do Arduino ligado ao segmento A  
  pinMode(3, OUTPUT); //Pino 3 do Arduino ligado ao segmento B
  pinMode(4, OUTPUT); //Pino 4 do Arduino ligado ao segmento C
  pinMode(5, OUTPUT); //Pino 5 do Arduino ligado ao segmento D
  pinMode(6, OUTPUT); //Pino 6 do Arduino ligado ao segmento E
  pinMode(7, OUTPUT); //Pino 7 do Arduino ligado ao segmento F
  pinMode(8, OUTPUT); //Pino 8 do Arduino ligado ao segmento G
  pinMode(9, OUTPUT); //Pino Multiplexação dezena
  pinMode(10, OUTPUT); //Pino Multiplexação unidade
  pinMode(11, OUTPUT); //Saída Buzzer

  Timer1.initialize(10000); // Em us
  Timer1.attachInterrupt(Display);
  
  Serial.begin(9600);
}


void Display(){
  if(displayActive == 9){
    displayActive = 10;
    digitalWrite(10, LOW);
    sevenSegWrite(count2);
    digitalWrite(9, HIGH);
  } else {
    displayActive = 9;
     digitalWrite(9, LOW);
     sevenSegWrite(count1);
     digitalWrite(10, HIGH);
  }
}

void sevenSegWrite(byte digit){
  byte pin = 2;
  for (byte segCount = 0; segCount < 7; ++segCount)  { 
    digitalWrite(pin, seven_seg_digits[digit][segCount]);
    ++pin;
  }
}
void loop() {
  unsigned long sensorValue = 0;
//  for (byte count = 0; count < 99; count++){
//    noInterrupts();
//    count1 = count/10;
//    count2 = count%10;
//    interrupts();
//    delay(200);
//  }
  while(1){
    //noInterrupts();
    sensorValue = analogRead(A0);
    Serial.println(sensorValue);
    sensorValue *= 100;
    sensorValue /= 1024;
    if(sensorValue >= 36){
      digitalWrite(11, HIGH);
      delay(200);
      digitalWrite(11, LOW);
    }
    Serial.println(sensorValue);
    
    count1 = sensorValue/10;
    count2 = sensorValue%10;
    //interrupts();
    delay(200);
  }
}
