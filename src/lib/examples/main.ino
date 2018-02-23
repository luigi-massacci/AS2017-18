#include <Wire.h>
#include "motori.h"
int t;
Motori M(3, 6, 10, 11);
PID pidous(-10, -10, -10);


const int MAX_V = 255;
const int MIN_V = 100;
const int STD_V = 200;

int data[8];

void setup()
{
  Wire.begin();
  Serial.begin(9600);
  t = 0;
}

void loop()
{
  Wire.requestFrom(9, 16);
  while (Wire.available())
  {
    if(!(t%2))
      data[t/2] = Wire.read();
    if (t < 15)
      t++;
    else{
      t = 0;
      M.move(STD_V+pidous.pid(data), STD_V-pidous.pid(data));
    }
  }

  delay(500);
}
