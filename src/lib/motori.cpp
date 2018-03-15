#include "motori.h"
#include "costanti.h"
#include <Arduino.h>

Motori::Motori( int pin1, int pin2, int pin3, int pin4 )
{
  pin_dx1 = pin1;
  pin_dx2 = pin2;
  pin_sx1 = pin3;
  pin_sx2 = pin4;
}


void Motori::move( int SX, int DX) //lato=0 sinistra,   lato=1 destra
{
  if (SX > 0)
  {
    analogWrite(pin_sx1, SX);
    analogWrite(pin_sx2, 0);
  }
  else
  {
    analogWrite(pin_sx1, 0);
    analogWrite(pin_sx2,-SX);
  }

  if (DX > 0)
  {
    analogWrite(pin_dx1, DX);
    analogWrite(pin_dx2, 0);
  }
  else
  {
    analogWrite(pin_dx1, 0);
    analogWrite(pin_dx2,-DX);
  }
}

void Motori::aggira_ostacolo(){
  move(0, 0);
  move(segno*STD_V, segno*(-STD_V));
  delay(TEMPO_ROTAZIONE);

  move(STD_V, STD_V);
  delay(TEMPO_AGGIRAMENTO);

  move(segno*(-STD_V), segno*STD_V);
  delay(TEMPO_ROTAZIONE);

  move(STD_V, STD_V);
  delay(TEMPO_SUPERAMENTO);

  move(segno*(-STD_V), segno*STD_V);
  delay(TEMPO_ROTAZIONE-1500);

  move(STD_V, STD_V);
  delay(2500);  

}
