#ifndef PID_H
#define PID_H

struct eccezione{
  bool a_retto_sx;
  bool a_retto_dx;
  bool linea;
};

class PID{
  private:
    double Kp, Ki, Kd;
    double P, I, D, E;
  public:
    PID();
    PID(double, double, double);
    int pid(int*);
    eccezione controllo(int*);
};

#endif
