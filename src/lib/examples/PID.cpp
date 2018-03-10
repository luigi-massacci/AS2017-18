#include "PID.h"
#include "costanti.h"
#include <Arduino.h>

PID::PID(){
  Kp=10;
  Ki=10;
  Kd=10;
  E=0;
  I=0;
}

PID::PID(double p, double i, double d){
  Kp=p;
  Ki=i;
  Kd=d;
  E=0;
  I=0;
}

int PID::pid_int(int* vet){
  double M=0, S=0;
  for(int i=0; i<8; i++)
    M+=vet[i]*(i+1), S+=vet[i];
  double E_prec=E;
  E=4.5-M/S;
  if(-0.1<E && E<0.1)
    E_prec=0, I=0;
  P=E*Kp;
  I+=E*Ki;
  D=(E-E_prec)*Kd;
  return P+I+D;
}

int PID::pid_bool(int* vet){
  double E_prec=E;
  E=0;
  for(int i=0; i<8; i++)
    if(vet[i]<BIANCO)           //se il sensore individua la linea
      E+=(i-3.5);       //si aggiunge all'errore la posizione della linea all'interno del sistema di riferimento
  if(-0.1<E && E<0.1)
    E_prec=0, I=0;
  P=E*Kp;
  I+=E*Ki;
  D=(E-E_prec)*Kd;
  return P+I+D;
}