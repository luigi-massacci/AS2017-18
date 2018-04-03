#ifndef MOTORE_H
#define MOTORE_H


class Motori{
  private:
    int pin_dx1, pin_dx2, pin_sx1, pin_sx2;  //1 --> DAVANTI; 2 --> DIETRO
  public:
    Motori(int, int, int, int);
    void move(int, int);
    void aggira_ostacolo();
    void indietro();
    void avanti();
    void svolta(int);
};


#endif
