#ifndef PID_H
#define PID_H

class PID {
private:

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

  double control_value;

public:

  /*
  * Constructor
  */
  PID(double Kp_, double Ki_, double Kd_);

  /*
  * Destructor.
  */
  virtual ~PID() {};

  /**
   * Update the PID error variables given cross track error
   */
  void update(double value);

  /**
   * returns the next control value
   */
  inline double getControlValue() const {
    return control_value;
  };
};

#endif /* PID_H */
