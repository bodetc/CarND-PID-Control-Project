//
// Created by Cédric Bodet on 21.07.17.
//

#include <iostream>
#include "TwiddleController.h"

void TwiddleController::update(double cte, double speed, double angle) {
  reset=false;
  iteration++;

  std::cout << "Iteration " << iteration << std::endl;

  pid.update(cte);

  switch (mode) {
    case starting:
      if(iteration>=N_start) {
        iteration=0;
        mode=measuring;
      }
    case measuring:
      if(iteration>=N_measure) {
        // TODO: Update PID with new values

        iteration=0;
        mode=starting;
        reset=true;
      }
      break;
  }
}
