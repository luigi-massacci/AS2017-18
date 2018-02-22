#include "motori.h"

Motori::motori( int pin1, int pin2, int pin3, int pin4 )
{
  pin_dx1 = pin1;
  pin_dx2 = pin2;
  pin_sx1 = pin3;
  pin_sx2 = pin4;
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
  Kp=10;     //i valori sono casuali, vanno sistemati
  Ki=10;
  Kd=10;
  I=0;
  E=0;
}

PID::PID(int p, int i, int d){
  Kp=p;
  Ki=i;
  Kd=d;
}

int PID::pid(int vet[]){        //il vettore in input è di lunghezza 8: adattiamo il programma di esempio per leggere solo i valori pari
  int M, S;
  for(int i=0; i<8; i++){
    M+=vet[i]*i;
    S+=vet[i];
  }
  double E_prec=E;
  E=M/S-3.5;        //da controllare (forse è 3.5-M/S)
  P=E*Kp;
  I+=E*Ki;
  D=D-E*Kd;
  return P+I+D;
}
