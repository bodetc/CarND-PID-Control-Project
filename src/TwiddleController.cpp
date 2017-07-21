//
// Created by Cédric Bodet on 21.07.17.
//

#include <iostream>
#include "TwiddleController.h"

TwiddleController::TwiddleController() {
  createPID();
}

TwiddleController::~TwiddleController() {
  delete (pid);
}

void TwiddleController::update(double cte, double speed, double angle) {
  reset = false;
  iteration++;

  pid->update(cte);
  error += cte * cte;

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
      twiddleUpdate();
      mode = starting;
      N_max = N_start;
      reset = true;
      break;
  }
  iteration = 0;
  error = 0.;
}

void TwiddleController::printPValues() {
  std::cout << "p-values: [ ";
  for (int i = 0; i < 3; i++) {
    std::cout << p[i] << " ";
  }
  std::cout << "]" << std::endl;
}

void TwiddleController::twiddleUpdate() {
  std::cout << "Error: " << error << std::endl;

  if (firstTwiddleRun && error > best_error) {
    // Search in the opposite direction without changing index
    p[twiddle_index] -= 2. * dp[twiddle_index];
    firstTwiddleRun = false;
  } else {
    if (error < best_error) {
      best_error = error;
      // Increment current delta
      dp[twiddle_index] *= 1.1;

      std::cout << "Found best error: ";
      printPValues();
    } else {
      // Decrement current delta
      p[twiddle_index] += dp[twiddle_index];
      dp[twiddle_index] *= 0.9;
    }

    // Switch to nex index and update parameters
    twiddle_index = (twiddle_index + 1) % 3;
    p[twiddle_index] += dp[twiddle_index];
    firstTwiddleRun = true;
  }

  n_twiddle++;
  if (n_twiddle > N_twiddle) {
    exit(0);
  }

  createPID();
}

void TwiddleController::createPID() {
  if(pid!= nullptr) {
    delete (pid);
  }
  // Set PID to new values
  pid = new PID(p[0], p[1], p[2]);

  // Print values
  std::cout << "Twiddle iteration: " << n_twiddle << ", ";
  printPValues();
}
