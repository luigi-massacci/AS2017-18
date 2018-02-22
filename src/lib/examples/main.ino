#include <Wire.h>
#include "motori.h"
#define uchar unsigned char
uchar t;
Motori M;
PID pidous;


const int MAX_V = 255;

const int MIN_V = 100;

const int STD_V = 200;

//void send_data(short a1,short b1,short c1,short d1,short e1,short f1);
uchar data[8];
void setup()
{
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
  t = 0;
}
void loop()
{
  Wire.requestFrom(9, 16);    // request 16 bytes from slave device #9
  while (Wire.available())   // slave may send less than requested
  {
    if(!(t%2)) 
      data[t/2] = Wire.read(); // receive a byte as character
    if (t < 15)
      t++;
    else{
      t = 0;
      M.move(STD_V+pidous.pid(data), STD_V-pidous.pid(data));
    }
  }
  
  delay(500);
}