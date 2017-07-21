#include "PID.h"

/*
 * Constructor
 */
PID::PID(double Kp_, double Ki_, double Kd_) :
    Kp(Kp_),
    Ki(Ki_),
    Kd(Kd_),
    previous_cte(0.),
    sum_cte(0.) {}

/**
 * Update the PID error variables given cross track error
 */
void PID::update(double value) {
  const double p_error=-Kp*value;
  const double i_error=-Ki*sum_cte;
  const double d_error=-Kd*(value-previous_cte);

  previous_cte=value;
  sum_cte+=value;

  control_value=p_error+i_error+d_error;
}

