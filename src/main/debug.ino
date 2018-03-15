/*#include <Wire.h>
#include "motori.h"
#include "costanti.h"

Motori M(11, 3, 9, 5);

int data[8];

void setup()
{
  Wire.begin();
  Serial.begin(9600);

  pinMode(11, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(9, OUTPUT);
  
}
char comando;

void loop()
{
  if(Serial.available())
    comando = Serial.read();
  Serial.println(comando);
  switch(comando){
   case '1': 
     test_vet();
   break; 
   case '2':
     test_motori();
   break;
   case '3':
   // test_tof();
   break;
   case '4':
     //test_pid();
   break;
   case '5':
   //  test_servo();
   default:
   break;
  }

  delay(500);
}




void test_vet(){
  int t=0;
  Wire.requestFrom(9, 16);
  while (Wire.available())
  {
    int h=Wire.read();
    if(!(t%2))
    {
      data[t/2] = h;
      Serial.print(data[t/2]); 
      Serial.print("\t");
    }
    if (t < 15)
      t++;
    else
      t=0;
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

void test_motori()
{
  M.move(STD_V, STD_V);
  delay(1000);
  M.move(0, 0);
  delay(1000);
  Serial.println("aaaa");
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
}*/
