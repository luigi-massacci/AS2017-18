#include "motori.h"
#include <Arduino.h>

Motori::Motori( int pin1, int pin2, int pin3, int pin4 )
{
  pin_dx1 = pin1;
  pin_dx2 = pin2;
  pin_sx1 = pin3;
  pin_sx2 = pin4;

  pinMode(pin_dx1, OUTPUT);
  pinMode(pin_dx2, OUTPUT);
  pinMode(pin_sx1, OUTPUT);
  pinMode(pin_sx2, OUTPUT);
}

// void motori::gira_di( int a )
// {
//   while ( angle() <=  a )
//   {
//     if(a<0){
//       move(MIN_V, -MIN_V)                     // angle() restituisce l'angolo misurato dall'imu
//     }
//     else{
//       move(-MIN_V, MIN_V);
//     }
//     delay(1);    //mettere un delay
//   }
// }

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

PID::PID(){
  Kp=-10;     //i valori sono casuali, vanno sistemati
  Ki=-10;
  Kd=-10;
  I=0;
  E=0;
}

PID::PID(int p, int i, int d){
  Kp=p;
  Ki=i;
  Kd=d;
}

int PID::pid(int vet[]){        //il vettore in input � di lunghezza 8: adattiamo il programma di esempio per leggere solo i valori pari
  int M, S;
  for(int i=0; i<8; i++){
    M+=vet[i]*i;
    S+=vet[i];
  }
  bool segno = (E > 0) ;   //segno=1 se l'errore � verso destra, segno=0 se verso sinistra
  E=M/S-3.5;        //da controllare (forse � 3.5-M/S)
  if(segno != (E>0))
    I=0;
  P=E*Kp;
  I+=E*Ki;
  D=E*Kd-D;
  return P+I+D;
}

void PID::controllo(int vet[]){
  bool linea=0, a_retto_sx=1, a_retto_dx=1;
  for(int i=0; i<8; i++){
    if( i<4 && vet[i]>BIANCO )
        a_retto_sx=0;
    if( i>=4 && vet[i]>BIANCO )
        a_retto_dx=0;
    if( vet[i]<BIANCO )
        linea=1;
  }
  if(a_retto_sx)
    incrocio();    //incrocio() è la funzione che gestisce gli incroci, da implementare
  if(a_retto_dx)
    incrocio();
  if(!linea)
    if( contatore<MAX_CONT )
      contatore++;
    else
      backTrack();   //backTrack() spinge il robot a rifare il percorso al contrario fino a quando
                     // non ritrova la linea e a quel punto modifica artificialmente il
                     // valore di PID per evitare lo stallo
}