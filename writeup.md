# CarND-Controls-PID
Self-Driving Car Engineer Nanodegree Program

---

## Writeup

This is my implementation of the PID controller for the second term of the Self-Driving Car Engineer Nanodegree Program.

### Effects of the PID-parameters

By manually playing with the three parameters, I have found that they have the following effects on the behaviour of the car:
* P-parameter: The proportional term responds directly to the cross-track error. A high weight creates a stronger correction to any deviation from the center line. A too high value might create too strong oscillations that might be considered uncomfortable by an human occupant.
* D-parameter: The derivative term compensates for the oscillations created by the proportional term of the PID contoller. A strong weight will nearly fully suppress oscillations, but might lower the convergence speed towards the center line.
* I-parameter: The integral parameter is designed to compensate for any bias in the control (the steering not being perfectly tuned). However, it also helps to keep the car close to the center line in curves.

### Selection of the parameters

The parameters of the PID controller where selected manually by successively tuning one parameter after the other.
The following criteria were considered during tuning: no large deviation from the center line and no strong oscillations that might disturb human occupants.
The following parameters were finally selected:
* `K_p=0.3`
* `K_i=0.0002`
* `K_d=10.`

The twiddle algorithm was also considered, but due to its low convergence speed, the manual approach above was preferred.

### Fast mode

For the first part of the project, I have used a simple P-controller for the throttle, with a target speed of 25 mph. This speed allows to safely navigate the track, but might be considered slow on straight lines.

In other to improve the speed in those segment, a new throttle controller was implemented.
The controller is still a P-controller, but the target speed is not fixed anymore, but given by:

`target_speed=max_speed*(1. - fabs(angle/MAX_ANGLE))`

where `angle` and `MAX_ANGLE` are the current and maximum steering angle, respectively.

This improved throttle controller allows to safely navigate the track with an increased maximum speed of 55 mph.

The main disadvantage of this method is that the car brakes only once in the turn, which is generally considered unsafe.
Going around this limitation would required prediction of the path ahead, which is outside of the scope of this project, as it is the subject of the next one.

The fast mode can be started via: `./pid fast`