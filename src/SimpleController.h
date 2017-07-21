//
// Created by Cédric Bodet on 21.07.17.
//

#ifndef PID_SIMPLECONTROLLER_H
#define PID_SIMPLECONTROLLER_H


#include "Controller.h"
#include "PID.h"

class SimpleController : public Controller {
public:
  enum Type { cte, speed, angle };

private:
  const Type type;
  const double targetValue;

  PID pid;

public:

  SimpleController(Type type_, double Kp_, double Ki_, double Kd_, double targetValue_);

  SimpleController(Type type_, double Kp_, double Ki_, double Kd_) : SimpleController(type_, Kp_, Ki_, Kd_, 0.) {}

  virtual void update(double cte, double speed, double angle);

  inline double getControl() {
    return pid.getControlValue();
  }

  inline virtual bool isReset() {
    return false;
  };
};


#endif //PID_SIMPLECONTROLLER_H
