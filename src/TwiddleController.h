//
// Created by Cédric Bodet on 21.07.17.
//

#ifndef PID_TWIDDLECONTROLLER_H
#define PID_TWIDDLECONTROLLER_H


#include "PID.h"
#include "Controller.h"

class TwiddleController : public Controller {
private:
  enum Mode { starting, measuring };

  const int N_start = 100;
  const int N_measure = 500;

  Mode mode=starting;
  PID pid=PID(0.3, 0.0001, 6.0);

  bool reset = false;
  int iteration = 0;
  int N_max=N_start;

  // Accumulated error
  double error = 0;

  /**
   * Handles the transistions between the various states of the controller
   */
  void handleModeTransition();

public:

  virtual void update(double cte, double speed, double angle);

  inline double getControl() {
    return pid.getControlValue();
  }

  inline virtual bool isReset() {
    return reset;
  };
};


#endif //PID_TWIDDLECONTROLLER_H
