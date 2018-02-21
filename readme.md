##rescuea
#Rescue Line Galilei 2017
This is the repository where we are developing the _code_ that will guide our robot at the 2017 edition of the Robocup JR in the Rescue Line competition.

![Alt text](https://upload.wikimedia.org/wikipedia/commons/f/fa/Martian_rover_Curiosity_using_ChemCam_Msl20111115_PIA14760_MSL_PIcture-3-br2.jpg "Our robot")

##Commits
###Prefixes:
 Since mostof you are lazy and use GitKraken, there's no point in telling you what prefix to use.
###Content:
  Keep it short and simple. But not stupid. Please.


##Code standards
 if in doubt, follow the Python Zen (import this).
###Indentation
 Indentations are made by a tab.

###Comments
Comments should respect these parameters:

+ the language used is English
+ the infinitive is preferred in order to keep things as simple as possible

The structure used to describe a function is as follows:

	/*******************************************
	* function name (possible parameters)
	* the aim of the function
	* possible values returned
	*******************************************/

* * *

##Contributors

+ Luigi
+ Nicola
+ Pietro
+ Martino
+ Rolleri
+ God

;)

#include "motori.h"

motori::motori( int pin1, int pin2, int pin3, int pin4 )
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

void motori::move( int SX, int DX) //lato=0 sinistra,   lato=1 destra
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


7777777777777777777777


#ifndef MOTORE_H
#define MOTORE_H

const int MAX_V = 255;

const int MIN_V = 100;

class motori{
  private:
    int pin_dx1, pin_dx2, pin_sx1, pin_sx2;  //1 stays for "forward" and 2 stays "backward"
  public:
    motori(int, int, int, int);
    void move(int, int);
    void gira_di(int);
}

class PID{
  private:
    int Kp, Ki, Kd;
    double P, I, E, D;
  public:
    PID(){
      Kp=10;     //i valori sono casuali, vanno sistemati
      Ki=10;
      Kd=10;
      I=0;
      E=3.5;
    }
    PID(int p, int i, int d){
      Kp=p;
      Ki=i;
      Kd=d;
    }
    int pid(int vet[]){        //il vettore in input è di lunghezza 8: adattiamo il programma di esempio per leggere solo i valori pari
      int M, S;
      for(int i=0; i<8; i++){
        M+=vet[i]*i;
        S+=vet[i];
      }
      double E_prec=E;
      E=M/S-3.5;        //da controllare (forse è 3.5-M/S)
      P=E*Kp;
      I+=E*Ki;
      D=(E-E_prec)*Kd;
      return P+I+D;
    }
}

#endif
