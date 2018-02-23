#ifndef MOTORE_H
#define MOTORE_H



class Motori{
  private:
    int pin_dx1, pin_dx2, pin_sx1, pin_sx2;  //1 stays for "forward" and 2 stays "backward"
  public:
    Motori(int, int, int, int);
    void move(int, int);
    void gira_di(int);
};

class PID{
  private:
    int Kp, Ki, Kd;
    double P, I, D, E;
  public:
    PID();
    PID(int ,int ,int);
    int pid(int*);
};

#endif

