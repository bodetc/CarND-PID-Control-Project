//
// Created by Cédric Bodet on 21.07.17.
//

#include <iostream>
#include "TwiddleController.h"

void TwiddleController::update(double cte, double speed, double angle) {
  reset = false;
  iteration++;

  std::cout << "Iteration " << iteration << std::endl;

  pid.update(cte);
  error+=pid.getControlValue();

  if (iteration >= N_max) {
    handleModeTransition();
  }
}

void TwiddleController::handleModeTransition() {
  switch (mode) {
    case starting:
      mode = measuring;
      N_max = N_measure;
      reset = false;
      break;
    case measuring:
      // TODO: Update PID with new values
      mode = starting;
      N_max = N_start;
      reset = true;
      break;
  }
  iteration = 0;
  error = 0.;
}
