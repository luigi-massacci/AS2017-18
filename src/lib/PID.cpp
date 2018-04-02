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

int PID::pid(int* vet){
  double E_prec=E;
  E=0;
  int n=0;
  for(int i=0; i<8; i++)
    if(vet[i]<BIANCO)           //se il sensore individua la linea
      E+=(i-3.5), ++n;       //si aggiunge all'errore la posizione della linea all'interno del sistema di riferimento
  if(n==0) n=1;
  E/=n;
  if(E==0)
    E_prec=0, I=0;
  P=E*Kp;
  I+=E*Ki;
  D=(E-E_prec)*Kd;
  return P+I+D;
}

eccezione PID::controllo(int* vet){
  eccezione responso;
  responso.a_retto_sx=1;
  responso.a_retto_dx=1;
  responso.linea=0;
  for(int i=0; i<8; ++i){
    if(i<4)
      responso.a_retto_sx &= (vet[i]<BIANCO);
    else
      responso.a_retto_dx &= (vet[i]<BIANCO);
    responso.linea |= (vet[i]<BIANCO);
  }
  return responso;
}
