#include <Wire.h>
#include "motori.h"
#include "PID.h"
#include "costanti.h"


int t;
Motori M(11, 3, 9, 5);
PID pidous(30, 0, 0);


int data[8];

void setup()
{
  Wire.begin();
  Serial.begin(9600);
  t = 0;

  pinMode(11, OUTPUT); //vanno rigorosamente qua e non nei costruttori
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(9, OUTPUT);
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

      int pid_s = STD_V+pidous.pid_bool(data); 
      int pid_d = STD_V-pidous.pid_bool(data);

     if(-MIN_V < pid_s && pid_s < MIN_V){
       if(pid_s < 0)
         pid_s+=(2*MIN_V);
       else
         pid_s-=(2*MIN_V);
     }

     if(-MIN_V < pid_d && pid_d < MIN_V){
       if(pid_d < 0)
         pid_d+=(2*MIN_V);
       else
         pid_d-=(2*MIN_V);
     }

      M.move(pid_s, pid_d); 
    }
  }

}
