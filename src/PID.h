#ifndef PID_H
#define PID_H

class PID {
public:

  /*
   * Coefficients
   */
  const double Kp;
  const double Ki;
  const double Kd;

  /*
   * Memory for Integral and Derivative
   */
  double previous_cte;
  double sum_cte;

  /*
  * Constructor
  */
  PID(double Kp_, double Ki_, double Kd_);

  /*
  * Destructor.
  */
  virtual ~PID() {};

  /*
   * Update the PID error variables given cross track error and returns the next control value
   */
  double UpdateErrorAndGetNewControl(double cte);
};

#endif /* PID_H */
