#include "PID.h"
#include <random>
#include <math.h>
#include <iostream>

using namespace std;

#define Twiddle 1

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

	total_error = 0;
	best_error = std::numeric_limits<double>::max();
	cur_par = 2;
	this->p[0] = Kp;
	this->p[1] = Kd;
	this->p[2] = Ki;

	iter = 0;

	eval1[0] = false;
	eval1[1] = false;
	eval1[2] = false;

	eval2[0] = false;
	eval2[1] = false;
	eval2[2] = false;

	// Initialize Twiddle dp values - normalized to be similar to coefficients	
	dp[0] = Kp * 0.1; //Kp
	dp[1] = Kd * 0.1; //Kd
	dp[2] = Ki * 0.1; //Ki

	boInit = false;

	n_settle_steps = 100;
	n_eval_steps = 1500;
}

void PID::UpdateError(double cte) {	

	if (!boInit)
	{
		d_error = 0;
		boInit = true;
	}		
	else
	{
		d_error = cte - p_error;
	}
		

	p_error = cte;
	i_error += cte;

#if(Twiddle == 1)
	iter++;
	
	// update total error only if we're past number of settle steps
	if ((iter % (n_settle_steps + n_eval_steps)) > n_settle_steps) {
		total_error += pow(cte, 2);

		if (!eval1[cur_par] & !eval2[cur_par])
		{
			p[cur_par] += dp[cur_par];
			eval1[cur_par] = true;
		}
	}		

	if (iter % (n_settle_steps + n_eval_steps) == 0)
	{
		if (eval1[cur_par] & !eval2[cur_par])
		{
			if ((total_error < best_error))
			{
				//cout << "improvement!" << endl;
				best_error = total_error;
				dp[cur_par] *= 1.1;
				eval2[cur_par] = true;
			}
			else
			{
				p[cur_par] -= 2 * dp[cur_par];
				eval1[cur_par] = false;
				eval2[cur_par] = true;
				//cout << "No improvement-Reduced!" << endl;
			}
		}
		else if (!eval1[cur_par] & eval2[cur_par])
		{
			if ((total_error < best_error))
			{
				//cout << "Improvement!" << endl;
				best_error = total_error;
				dp[cur_par] *= 1.1;
				eval1[cur_par] = true;
			}
			else
			{
				p[cur_par] += dp[cur_par];
				dp[cur_par] *= 0.9;
				eval1[cur_par] = true;
				//cout << "No improvement-Reduced!" << endl;
			}
		}	
		

		total_error = 0;

		if (eval1[cur_par] & eval2[cur_par])
		{
			eval1[cur_par] = false;
			eval2[cur_par] = false;
			cur_par = (cur_par + 1) % 3;
		}		

		//std::cout << "cur_par " << cur_par << std::endl;
		//std::cout << "Kp " << p[0] << " Kd " << p[1] << " Ki " << p[2] << std::endl;
	}

	std::cout << "iter " << iter << std::endl;
#endif
}

double PID::TotalError() {
	
#if(Twiddle == 1)
	Kp = p[0];
	Kd = p[1];
	Ki = p[2];
#endif

	return -(Kp * p_error) - (Kd * d_error) - (Ki * i_error);
}
