//
// Created by Cédric Bodet on 21.07.17.
//

#include "PIDController.h"

PIDController::PIDController(PIDController::Type type_, double Kp_, double Ki_, double Kd_,
                                   double targetValue_) :
    type(type_),
    targetValue(targetValue_),
    pid(PID(Kp_, Ki_, Kd_)) {}

inline double getValue(PIDController::Type type, double cte, double speed, double angle) {
  switch (type) {
    case PIDController::cte:
      return cte;
    case PIDController::speed:
      return speed;
    case PIDController::angle:
      return angle;
  }
}

void PIDController::update(double cte, double speed, double angle) {
  pid.update(getValue(type, cte, speed, angle)-targetValue);
}
