#include <Wire.h>
#include "motori.h"
int t;
Motori M(9, 5, 3, 11);
PID pidous(-10, -10, -10);


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
    int h=Wire.read();
    if(!(t%2))
      data[t/2] = h;
    if (t < 15)
      t++;
    else{
      t = 0;
      M.move(STD_V+pidous.pid(data), STD_V-pidous.pid(data));
    }
  }

  delay(500);
}
