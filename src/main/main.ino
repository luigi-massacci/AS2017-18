#include <Wire.h>
#include "VL53L0X.h"
#include "Adafruit_TCS34725.h"

#include "motori.h"
#include "PID.h"
#include "costanti.h"
#include "verde.h"


//OGGETTI GLOBALI
Motori M(11, 3, 9, 5);
PID pidous(10, 20, 5); //30, 0, 0 --> 10, 10, 5 --> 10, 20, 5
VL53L0X Tof;
VL53L0X Tof1;
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
Adafruit_TCS34725 tcs1 = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);


//VARIABILI GLOBALI
int t;
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

  //INIZIALIZZAZIONE SENSORI
  digitalWrite(12, LOW);          //TOF 1
  delay(10);
  digitalWrite(12, HIGH);
  Tof.init();
  delay(100);
  Tof.setAddress((uint8_t) 0x31);
  Tof.setTimeout(500);
  Tof.startContinuous();
  digitalWrite(12, LOW);          //TOF 2
  delay(10);
  digitalWrite(12, HIGH);
  Tof1.init();
  delay(100);
  Tof1.setAddress((uint8_t) 0x31);
  Tof1.setTimeout(500);
  Tof1.startContinuous();

  tcs.begin();                  //S. VERDE 1
  tcs1.begin();                 //S. vERDE 2

}

void loop()
{
  eccezione e1;
  eccezione e2;

  if (Tof.readRangeContinuousMillimeters() < SPAZIO_OSTACOLO &&
      Tof1.readRangeContinuousMillimeters() < SPAZIO_OSTACOLO)
    M.aggira_ostacolo();

  Wire.requestFrom(9, 16);
  while (Wire.available())
  {
    int h = Wire.read();
    if (!(t % 2))
      data[t / 2] = h;
    if (t < 15)
      t++;
    else
      t = 0;
  }

  int verde = verde();


  if (verde == ENTRAMBI)
    M.indietro();
  else if (verde == DESTRA)
    M.svolta(1);
  else if (verde == SINISTRA)
    svolta(-1);
  else
  {
    e1 = pidous.controllo();
    M.avanti();
    e2 = pidous.controllo();

    if (e1.a_retto_sx && e1.a_retto_dx && !e2.a_retto_dx)
      ;//storto
    else if (e1.a_retto_dx && !e2.linea)
      svolta(1);
    else if (e1.a_retto_sx && !e2.linea)
      svolta(-1);
      
    }

  int pid_s = STD_V + pidous.pid(data);
  int pid_d = STD_V - pidous.pid(data);

  if (-MIN_V < pid_s && pid_s < MIN_V)
  {
    if (pid_s < 0)
      pid_s += (2 * MIN_V);
    else
      pid_s -= (2 * MIN_V);
  }
  if (-MIN_V < pid_d && pid_d < MIN_V)
  {
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
