//
// Created by Cédric Bodet on 20.07.17.
//

#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H


class Controller {
public:
  virtual ~Controller() {}

  virtual void update(double cte, double speed, double angle) = 0;

  virtual bool isReset() = 0;

  virtual double getControl() = 0;
};


#endif //PID_CONTROLLER_H
