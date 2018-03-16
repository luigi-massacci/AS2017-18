#include <Wire.h>
#include "motori.h"
#include "PID.h"
#include "costanti.h"
#include "VL53L0X.h"


int t;
Motori M(11, 3, 9, 5);
PID pidous(10, 20, 5); //30, 0, 0 --> 10, 10, 5 --> 10, 20, 5

VL53L0X Tof;

int data[8];

void setup()
{
  Wire.begin();
  Serial.begin(9600);
  Tof.init(0x31);
  Tof.setTimeout(500);
  Tof.startContinuous();
  t = 0;

  pinMode(11, OUTPUT); //vanno rigorosamente qua e non nei costruttori
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(9, OUTPUT);
}

void loop()
{
  eccezione Casi;
  if(Tof.readRangeContinuousMillimeters() < SPAZIO_OSTACOLO)
    M.aggira_ostacolo();
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

      Casi = pidous.controllo(data);
      

      if(Casi.a_retto_sx && Casi.a_retto_dx)
      {
        
        Serial.println("aaaaa");
        M.move(0, 0);
        delay(1000);

        //if verde
        
        //else
        M.move(MAX_V, MAX_V);
        delay(1000);
        M.move(0, 0);

      }
        
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
     Serial.print(pid_s);
     Serial.print("   ");
     Serial.println(pid_d);

     M.move(pid_s, pid_d);
    }
  }

}
