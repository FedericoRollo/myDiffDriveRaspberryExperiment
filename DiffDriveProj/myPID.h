#ifndef MYPID_H
#define MYPID_H

#include "Motor.h"
#include "Encoder.h"

class myPID
{
private:
	double m_kp{0}, m_ki{0}, m_kd{0};

	double *m_ref{0}; //cm/s

	double m_prev_err{0}; // error at the previous step

	double m_integrator_term{0};
	double m_derivative_term{0};

	const Motor m_motor;

	const Encoder m_encoder;

public:
	myPID(double kp, double ki, double kd, double *ref, Motor &motor, Encoder &encoder):
		m_kp{kp},
		m_ki{ki},
		m_kd{kd},
		m_ref{ref},
		m_motor{motor},
		m_encoder{encoder}
		{
		}

	~myPID();

	void computeStep(int secDelay);
	
};



#endif MYPID_H