#include <Wire.h>
#include "motori.h"
#include "PID.h"
#include "costanti.h"
#include "VL53L0X.h"
#include "Adafruit_TCS34725.h"
#include "verde.h"

int t;
Motori M(11, 3, 9, 5);
PID pidous(10, 20, 5); //30, 0, 0 --> 10, 10, 5 --> 10, 20, 5

VL53L0X Tof;
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

int data[8];

void setup()
{

  Wire.begin();           //initialize comm protocols
  Serial.begin(9600);
  
  pinMode(11, OUTPUT);     //set pins
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(12, OUTPUT);

    //initialize ToF
    Serial.println("A");

  digitalWrite(12, LOW);    
  //change ToF address
  delay(10);
  digitalWrite(12, HIGH);
  
  Tof.init(); 
  delay(100);

  Tof.setAddress((uint8_t) 0x31);

  Tof.setTimeout(500);
  Tof.startContinuous();


  tcs.begin();            //initialize color sensor
        Serial.println("A");
t = 0;

}


void loop()
{
  eccezione Casi;
  Serial.println("1");
  if (Tof.readRangeContinuousMillimeters() < SPAZIO_OSTACOLO)
    M.aggira_ostacolo();

  Wire.requestFrom(9, 16);

  while (Wire.available())
  {

    int h = Wire.read();
    if (!(t % 2))
      data[t / 2] = h;
    if (t < 15)
      t++;
    else {
      t = 0;

    for (int i = 0; i < 8; ++i)
      Serial.println(data[i]);
      
      Casi = pidous.controllo(data);

      

      if (Casi.a_retto_sx && Casi.a_retto_dx)
      {
        Serial.println("A");
        uint16_t clear, r, g, b;
        tcs.setInterrupt(false);      // turn on LED
        delay(60);  // takes 50ms to read
        tcs.getRawData(&r, &g, &b, &clear);
        tcs.setInterrupt(true);  // turn off LED

        bool dx = false;
        bool sx = false;

        for (int i = 1; i <= 2; i++) {
          M.move(0, 0);
          delay(10);

          M.move(STD_V, -STD_V);
          delay(OSCILLA);
          M.move(0, 0);
          delay(100);
          dx = isGreen(r, g, b);

          M.move(-STD_V, STD_V);
          delay(2 * OSCILLA);
          M.move(0, 0);
          delay(100);
          sx = isGreen(r, g, b);

          M.move(STD_V, -STD_V);
          delay(OSCILLA);
          M.move(0, 0);
          delay(100);

          if (dx && sx)
          {

            M.move(STD_V, -STD_V);
            delay(2 * MUOVI_2);
            break;
          }
          else if (dx)
          {
            M.move(STD_V, STD_V);
            delay(MUOVI_1);
            M.move(STD_V, -STD_V);
            delay(MUOVI_2);
            break;
          }
          else if (sx)
          {
            M.move(STD_V, STD_V);
            delay(MUOVI_1);
            M.move(-STD_V, STD_V);
            delay(MUOVI_2);
            break;
          }
          else if (i == 2)
          {
            M.move(MAX_V, MAX_V);
            delay(1000);
            break;
          }



        }
      }

        int pid_s = STD_V + pidous.pid_bool(data);
        int pid_d = STD_V - pidous.pid_bool(data);

        if (-MIN_V < pid_s && pid_s < MIN_V) {
          if (pid_s < 0)
            pid_s += (2 * MIN_V);
          else
            pid_s -= (2 * MIN_V);
        }

        if (-MIN_V < pid_d && pid_d < MIN_V) {
          if (pid_d < 0)
            pid_d += (2 * MIN_V);
          else
            pid_d -= (2 * MIN_V);
        }
        Serial.print(pid_s);
        Serial.print("   ");
        Serial.println(pid_d);

        M.move(pid_s, pid_d);
      }
    
    }

  }



