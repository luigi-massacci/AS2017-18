
#include "motori.h"

motori::motori( int pin1, int pin2, int pin3, int pin4 ){
  pin_dx1 = pin1;
  pin_dx2 = pin2;
  pin_sx1 = pin3;
  pin_sx2 = pin4;
}

void motori::avanti( int speed){
  move ( pin_dx1, speed );
  move ( pin_sx1, speed );
  move ( pin_dx2, speed );
  move ( pin_sx2, speed );
}

void motori::curva( int sx_v, int dx_v ){
  move ( pin_dx1, dx_v );
  move ( pin_dx2, dx_v );
  move ( pin_sx1, sx_v );
  move ( pin_sx2, sx_v );
}

void motori::gira_per( int a )
{
  while ( angle() <=  a )
  {                       // angle() restituisce l'angolo misurato dall'imu
    move ( pin_dx1, -a/abs(a)*MIN_V );
    move ( pin_dx2, -a/abs(a)*MIN_V );
    move ( pin_sx1, a/abs(a)*MIN_V );
    move ( pin_sx2, a/abs(a)*MIN_V );
  }
}
