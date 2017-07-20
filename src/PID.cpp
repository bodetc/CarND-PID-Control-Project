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

/*
 * Update the PID error variables given cross track error and returns the next control value
 */
double PID::UpdateErrorAndGetNewControl(double cte) {
  const double p_error=-Kp*cte;
  const double i_error=-Ki*sum_cte;
  const double d_error=-Kd*(cte-previous_cte);

  previous_cte=cte;
  sum_cte+=cte;
  return p_error+i_error+d_error;
}

