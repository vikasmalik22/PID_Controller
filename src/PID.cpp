#include "PID.h"
#include <random>
#include <math.h>
#include <iostream>

using namespace std;

#define num 10

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
	this->Kp = Kp;
	this->Ki = Ki;
	this->Kd = Kd;
	
	p_error = 0;
	i_error = 0;
	d_error = 0;

	v_ierror.assign(num, 0.0);
}

void PID::UpdateError(double cte) {	
	d_error = cte - p_error;
	p_error = cte;
	//i_error += cte;

	//Add the new cte to vector
	v_ierror.push_back(cte);

	//remove the oldest value of cte
	v_ierror.erase(v_ierror.begin());

	std::cout << "d_error: " << d_error << " p_error: " << p_error << " i_error: " << i_error << std::endl;
	std::cout << " " << std::endl;
}

double PID::TotalError() {
	
	for (int j = 0; j < v_ierror.size(); j++)
		i_error += v_ierror[j];

	return (Kp * p_error) + (Kd * d_error) + (Ki * i_error);
}
