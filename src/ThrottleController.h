//
// Created by Cédric Bodet on 26.07.17.
//

#ifndef PID_THROTTLECONTROLLER_H
#define PID_THROTTLECONTROLLER_H


#include "Controller.h"
#include "PID.h"

class ThrottleController : public Controller {
private:
  const double maxSpeed;

  PID pid;

public:
  ThrottleController(double Kp_, double maxSpeed_);

  virtual void update(double cte, double speed, double angle);

  inline double getControl() {
    return pid.getControlValue();
  }

  inline virtual bool isReset() {
    return false;
  };
};


#endif //PID_THROTTLECONTROLLER_H
