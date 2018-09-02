# PID Controller Project
Udacity CarND Term 2, Project 4 - PID Controller Project

## Project Basics
The main goal of the project is to apply PID controller in C++ to maneuver the vehicle around the track!

## Project Introduction
The purpose of this project is to "build a PID controller and tune the PID hyperparameters by applying the general processing flow as described in the lessons," and to "test your solution on the simulator!" The simulator will provide you the cross track error (CTE) and the velocity (mph) in order to compute the appropriate steering angle. The PID (proportional/integral/differential) controller must respond with steering and throttle commands to drive the car reliably around the simulator track.

## Reflection
### Describe the effect each of the P, I, D components had in your implementation.
The P, or "proportional" component has the most directly observable effect on the car's behavior. It causes the car to steer proportional (and opposite) to the car's distance from the lane center (which is the CTE) - if the car is far to the right it steers hard to the left, if it's slightly to the left it steers slightly to the right.
So the P controller controls the speed smoothly, allowing it to slow down as it approaches it's target, to shrink the overshoot. That's why it is called a proportional controller – the output speed is proportional to the value remaining to be changed, which we call an error.

* * *
The D, or "derivative", jobs is to predict the future value for the error, and then make the speed act accordingly. For example, if it thinks it will overshoot, it will slow it down. A properly tuned D parameter will cause the car to approach the center line smoothly without ringing.

* * *
The I, or "Integral", helps in elmiminating the bias in the CTE which doesn't let it reach to the centre of the lane. I componenet provides necessary action to eliminate the steady state error or bias.  It integrates the error over a period of time until error value reaches to zero. It holds the value to final control device at which error becomes zero.

### Describe how the final hyperparameters were chosen.
Firstly, I started with tuning the hyperparameters manually. This was required because otherwise car would always leave the track as there was little margin of error. Once I was able to get the car move around the track without going off the road, I used Twiddle algorithm to further tune the hyperparameters. I used atleast 1500 steps (which was roughly around 1 lap or round) for the values to be evaluated  and 100 steps for them to settle before changing them. After, running the car with Twiddle for 100 laps the hyperparameters stopped changing further and those were my final hyperparameters. 

I also tried to implement PID controller for the throttle but was not successfull as the car will always go off the track. My several attempts went down trying to implement it.

In PID.cpp file the Twiddle can be turned on and off. 
```
#define Twiddle 0 -> Off
#define Twiddle 0 ->> On
```
_ _ _

**Final Values (P: 0.2378, I: 0.00484, D: 3.134)**

[PID Controller Final](https://www.youtube.com/watch?v=1gVhF3JGWzk&t=11s)



