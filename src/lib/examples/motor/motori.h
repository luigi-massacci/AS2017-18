#ifndef MOTORE_H
#define MOTORE_H

const int MAX_V = 255;

class motori{
  int pin_dx1, pin_dx2, pin_sx1, pin_sx2;  //1 stays for "forward" and 2 stays "backward"
  public:
    void motori(int, int, int, int);
    void avanti(int);
    void curva(int, int);
    void gira_per(int);
}

#endif
