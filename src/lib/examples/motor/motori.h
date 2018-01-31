#ifndef MOTORE_H
#define MOTORE_H

const int MAX_V = 255;

const int MIN_V = 100;

class motori{
  private:
    int pin_dx1, pin_dx2, pin_sx1, pin_sx2;  //1 stays for "forward" and 2 stays "backward"
    void move(int, int);
  public:
    motori(int, int, int, int);
    void avanti(int);
    void curva(int, int);
    void gira_per(int);
}

#endif
