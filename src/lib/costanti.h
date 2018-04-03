#ifndef COSTANTI_H
#define COSTANTI_H

enum verde
{
   ENTRAMBI,
   DESTRA,
   SINISTRA
};



const int MAX_V = 255;
const int MIN_V = 210;                      //VELOCITÀ (PWM)
const int STD_V = 210;

const int BIANCO = 60;                      //COSTANTI LUCE
const int VERDE = 1000;

const int TEMPO_GIRO1 = 3500;
const int TEMPO_GIRO2 = 3000;
const int TEMPO_AGGIRAMENTO = 3000;         //OSTACOLO
const int SPAZIO_OSTACOLO = 100;
const int TEMPO_SUPERAMENTO = 5000;
const int DIREZIONE = 1;                   //indica se il robot deve girare a destra (1) o sinistra (-1)


#endif
