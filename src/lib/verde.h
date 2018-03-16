#ifndef VERDE_H
#define VERDE_H

bool isGreen(uint16_t R, uint16_t G, uint16_t B)
{
int tot = (int)R + (int)G + (int)B;
// double percentage = (double)G / tot *100;
//if(percentage > VERDE)
if(G > B + VERDE)
  return true;
else
  return false;
}

#endif
