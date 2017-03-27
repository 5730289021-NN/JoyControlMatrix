#include <SPI.h>

//initialize x,y position
int x = 4;
int y = 4;

const int yPins[] = {2, 3, 4, 5, 6, 7, 8, 9}; //assign y pins to make it easier to maintain
const int xTrans[] = {1, 2, 4, 8, 16, 32, 64, 128}; //a table to convert x position to SPI transfer data

void setup() {
  //Serial.begin(9600);
  SPI.begin(); //Initialize SPI
  for(int i = 0;i < 8;i++)
  {
    pinMode(yPins[i], OUTPUT); //set all output pin
  }
}

void loop() {
  int inX = analogRead(A0); //X input from joystick
  int inY = analogRead(A1); //Y input from joystick
 

  int dx = 0;
  int dy = 0;

  //Let delta be the direction of x,y
  if(inX < 250) dx = 1; //Let delta x = 1 when X input < 250
  if(inX > 750) dx = -1; //Let delta x = -1 when X input < 250
  if(inY < 250) dy = -1; //Let delta y = -1 when X input < 250
  if(inY > 750) dy = 1; //Let delta y = 1 when X input < 250
  //X,Y will be the same position summing with the delta X,Y
  x = x + dx; 
  y = y + dy;

  //Set boundary condition because the red dot must not fall from matrix display
  if(x>7) x = 7;
  if(x<0) x = 0;
  if(y>7) y = 7;
  if(y<0) y = 0;

  //to send SPI value 'transfer data' must be 2^x 
  int a = xTrans[x]; 
  SPI.transfer(a);

  //for debugging purpose
  /*Serial.print(inX);
  Serial.print(' ');
  Serial.print(inY);
  Serial.print(' ');
  Serial.println(a);*/
  
  //let all cathode pin be high
  for(int i = 0;i < 8;i++)
  {
    digitalWrite(yPins[i], HIGH);
  }
  //let only one pin be low
  digitalWrite(yPins[y], LOW);

  //let it check the conditions every 200 ms
  delay(200);
}
