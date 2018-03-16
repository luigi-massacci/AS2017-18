#include <Wire.h>
#include "motori.h"
#include "costanti.h"
#include "verde.h"
#include "Adafruit_TCS34725.h"
#include "VL53L0X.h"


//INITIALIZE OBJECTS
Motori M(11, 3, 9, 5);
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
VL53L0X Tof;


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




}
char comando;

void loop()
{
  if (Serial.available())
    comando = Serial.read();
  Serial.println(comando);
  switch (comando)
  {
    case '1':
      test_vet();
      break;
    case '2':
      test_motori();
      break;
    case '3':
      test_verde();
      break;
    case '4':
      test_tof();
      break;
    case '5':
    //  test_servo();
    default:
      break;
  }

  delay(500);
}




void test_vet() {
  int t = 0;
  Wire.requestFrom(9, 16);
  while (Wire.available())
  {
    int h = Wire.read();
    if (!(t % 2))
    {
      data[t / 2] = h;
      Serial.print(data[t / 2]);
      Serial.print("\t");
    }
    if (t < 15)
      t++;
    else
      t = 0;
  }
  Serial.println();

  for (int i = 0; i < 8; ++i)
  {
    if (data[i] > BIANCO)
      Serial.print("BIANCO  ");
    else
      Serial.print("NERO    ");

  }

  Serial.println();
  Serial.println();

}

void test_tof()
{
  if (Tof.readRangeContinuousMillimeters() < SPAZIO_OSTACOLO)
    Serial.println("VISTO");

}



void test_motori()
{
  M.move(STD_V, STD_V);
  delay(1000);
  M.move(0, 0);
  delay(1000);
  M.move(STD_V, -STD_V);
  delay(1000);
  M.move(0, 0);
  delay(1000);
  M.move(-STD_V, STD_V);
  delay(1000);
  M.move(0, 0);
  delay(1000);
  M.move(-STD_V, -STD_V);
  delay(1000);
  M.move(0, 0);
  delay(2000);
}



void test_verde()
{
  uint16_t clear, r, g, b;
  tcs.setInterrupt(false);      // turn on LED
  delay(60);  // takes 50ms to read
  tcs.getRawData(&r, &g, &b, &clear);
  tcs.setInterrupt(true);  // turn off LED
  Serial.print(r);
  Serial.print(" ");

  Serial.print(g);
  Serial.print(" ");
  Serial.println(b);

  bool test = isGreen(r, g, b);

  if (test)
    Serial.println("VERDE");




}


