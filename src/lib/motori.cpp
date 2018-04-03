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
  move(STD_V*DIREZIONE, -STD_V*DIREZIONE);
  delay(TEMPO_GIRO1);

  move(STD_V, STD_V);
  delay(TEMPO_AGGIRAMENTO);

  move(-STD_V*DIREZIONE, STD_V*DIREZIONE);
  delay(TEMPO_GIRO2);

  move(STD_V, STD_V);
  delay(TEMPO_SUPERAMENTO);

  move(-STD_V*DIREZIONE, STD_V*DIREZIONE);
  delay(TEMPO_GIRO2-1000);

  move(STD_V, STD_V);
  delay(1500);

}

void Motori::indietro()
{
  move(0, 0);
  move(STD_V*dir, -STD_V*dir);
  delay(6000); //da aggiustare
  move(0, 0);
}

void Motori::svolta(int dir)
{
  move(0, 0);
  move(STD_V*dir, -STD_V*dir);
  delay(2000); //da aggiustare
  move(0, 0);
}


void Motori::avanti()
{
  move(0, 0);
  move(MAX_V, MAX_V);
  delay(1000);
  move(0, 0);
}
