
#include "motori.h"

void motori::motori(int pin1, int pin2, int pin3, int pin4){
  this.pin_dx1=pin1;
  this.pin_dx2=pin2;
  this.pin_sx1=pin3;
  this.pin_sx2=pin4;
}

void motori::avanti(){
  analogWrite ( this.pin_dx1, MAX_V );
  analogWrite ( this.pin_sx1, MAX_V);
  analogWrite ( this.pin_dx2, MAX_V);
  analogWrite ( this.pin_sx2, MAX_V);
}

void motori::curva(){

}
