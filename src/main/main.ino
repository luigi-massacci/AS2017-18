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
Adafruit_TCS34725 sens = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
Adafruit_TCS34725 sens1 = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);


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
  
  pinMode(12, OUTPUT);
  pinMode(10, OUTPUT);

  //INIZIALIZZAZIONE SENSORI
  digitalWrite(12, LOW);          //TOF 1
  delay(10);
  digitalWrite(12, HIGH);
  Tof.init();
  delay(100);
  Tof.setAddress((uint8_t) 0x31);
  Tof.setTimeout(500);
  Tof.startContinuous();
  
  digitalWrite(10, LOW);          //TOF 2
  delay(10);
  digitalWrite(10, HIGH);
  Tof1.init();
  delay(100);
  Tof1.setAddress((uint8_t) 0x32);
  Tof1.setTimeout(500);
  Tof1.startContinuous();

  sens.begin();                  //S. VERDE SINISTRA
  sens1.begin();                 //S. vERDE DESTRA

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

  int V = verde();

  if (V == ENTRAMBI)
    M.indietro();
  else if (V == DESTRA)
    M.svolta(1);
  else if (V == SINISTRA)
    M.svolta(-1);
  else
  {
    e1 = pidous.controllo(data);
    M.avanti();
    e2 = pidous.controllo(data);

    if (e1.a_retto_sx && e1.a_retto_dx && !e2.linea)
      ;//storto
    else if (e1.a_retto_dx && !e2.linea)
      M.svolta(1);
    else if (e1.a_retto_sx && !e2.linea)
      M.svolta(-1);
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

  /*
    Serial.print(pid_s);
    Serial.print("   ");
    Serial.println(pid_d);
  */

  M.move(pid_s, pid_d);

}

int verde()
{

  uint16_t clear, red, green, blue;
  sens.setInterrupt(false);     
  delay(60);  
  sens.getRawData(&red, &green, &blue, &clear);
  sens.setInterrupt(true);  
  bool sx = isGreen(red, green, blue);

  sens1.setInterrupt(false);     
  delay(60);  
  sens1.getRawData(&red, &green, &blue, &clear);
  sens1.setInterrupt(true);  
  bool dx = isGreen(red, green, blue);

  if (dx && sx)
    return ENTRAMBI;
  else if (dx)
    return DESTRA;
  else if (sx)
    return SINISTRA;
  else
    return -1;  
}

