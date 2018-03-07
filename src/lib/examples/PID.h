#ifndef PID_H
#define PID_H

class PID{
  private:
    int Kp, Ki, Kd;
    double P, I, D, E;

  public:
    PID();
    PID(int, int, int);
    int pid_int(int*);
    int pid_bool(int*);
};

#endif
