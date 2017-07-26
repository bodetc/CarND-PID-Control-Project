//
// Created by Cédric Bodet on 26.07.17.
//

#include <cmath>
#include <iostream>
#include "ThrottleController.h"

#define MAX_ANGLE 25.

ThrottleController::ThrottleController(double Kp_, double maxSpeed_) :
    maxSpeed(maxSpeed_),
    pid(PID(Kp_, 0., 0.)) {}

void ThrottleController::update(double cte, double speed, double angle) {
  const double targetSpeed = fmax(maxSpeed * (1. - fabs(angle/MAX_ANGLE)), 0.);

  std::cout << "Angle: " << angle << ", Target speed: " << targetSpeed << std::endl;

  pid.update(speed - targetSpeed);
}
