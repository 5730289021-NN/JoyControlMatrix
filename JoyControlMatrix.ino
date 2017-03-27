#include <SPI.h>
int x = 4;
int y = 4;
const int yPins[] = {2, 3, 4, 5, 6, 7, 8, 9};
const int xTrans[] = {1, 2, 4, 8, 16, 32, 64, 128}; 

void setup() {
  Serial.begin(9600);
  SPI.begin();
  for(int i = 0;i < 8;i++)
  {
    pinMode(yPins[i], OUTPUT);
  }
}

void loop() {
  int inX = analogRead(A0);
  int inY = analogRead(A1);
 

  int dx = 0;
  int dy = 0;
  if(inX<250) dx = 1;
  if(inX>750) dx = -1;
  if(inY<250) dy = -1;
  if(inY>750) dy = 1;

  x = x +dx;
  y = y +dy;
  if(x>7) x =7;
  if(x<0) x =0;
  if(y>7) y =7;
  if(y<0) y =0;

  int a = xTrans[x]; 
  SPI.transfer(a);
  
  /*Serial.print(inX);
  Serial.print(' ');
  Serial.print(inY);
  Serial.print(' ');
  Serial.println(a);*/
  

  for(int i = 0;i < 8;i++)
  {
    digitalWrite(yPins[i], HIGH);
  }
  digitalWrite(yPins[y], LOW);
  delay(200);
  // put your main code here, to run repeatedly:
}
