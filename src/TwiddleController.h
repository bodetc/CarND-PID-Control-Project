//
// Created by Cédric Bodet on 21.07.17.
//

#ifndef PID_TWIDDLECONTROLLER_H
#define PID_TWIDDLECONTROLLER_H


#include <cfloat>
#include "PID.h"
#include "Controller.h"

class TwiddleController : public Controller {
private:
  enum Mode {
    starting, measuring
  };

  const int N_start = 100;
  const int N_measure = 5000;

  // Simulation status
  bool reset = false; // Should the simulation be reset
  Mode mode = starting; // Current mode
  int iteration = 0;  // Number of iterations in the current mode
  int N_max = N_start;  // Number of iterations to reach in the current mode

  // The PID Controller itself
  PID *pid= nullptr;

  // Accumulated error
  double error = 0;

  // Twiddle parameters
  double p[3] = {0.3, 0., 6.};
  double dp[3] = {0.15, 0.0001, 3.};

  double best_error = DBL_MAX;

  bool firstTwiddleRun = false;

  int n_twiddle = 0;
  int twiddle_index = 2;

  const int N_twiddle = 10000;

  /**
   * Handles the transistions between the various states of the controller
   */
  void handleModeTransition();

  void twiddleUpdate();

  void printPValues();

  void createPID();
public:

  TwiddleController();

  virtual ~TwiddleController();

  virtual void update(double cte, double speed, double angle);

  inline double getControl() {
    return pid->getControlValue();
  }

  inline virtual bool isReset() {
    return reset;
  };
};


#endif //PID_TWIDDLECONTROLLER_H
