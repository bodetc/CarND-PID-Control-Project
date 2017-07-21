//
// Created by Cédric Bodet on 21.07.17.
//

#include "SimpleController.h"

SimpleController::SimpleController(SimpleController::Type type_, double Kp_, double Ki_, double Kd_,
                                   double targetValue_) :
    type(type_),
    targetValue(targetValue_),
    pid(PID(Kp_, Ki_, Kd_)) {}

inline double getValue(SimpleController::Type type, double cte, double speed, double angle) {
  switch (type) {
    case SimpleController::cte:
      return cte;
    case SimpleController::speed:
      return speed;
    case SimpleController::angle:
      return angle;
  }
}

void SimpleController::update(double cte, double speed, double angle) {
  pid.update(getValue(type, cte, speed, angle)-targetValue);
}
