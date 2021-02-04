#include "myPid.h"

void myPid::computeStep(int secDelay)
{
	//compute current error
	double error{(*m_ref) - m_encoder.getSpeed(secDelay)};

	//compute proportional term
	double p_term{m_kp *error};

	//compute integrative term
	m_integrator_term += m_ki * 0.5 * secDelay * (error - m_prev_error);

	//anti-windup integrator
	double max_limit, min_limit;

	double max_speed{m_motor.getMaxSpeed()};

	//compute integrator limits
	if ( max_speed > p_term)
	{
		max_limit = m_motor_max_limit - p_term;
	}
	else
	{
		max_limit = 0.0;
	}

	if (-max_speed < p_term)
	{
		min_limit = m_motor_min_limit - p_term;
	}
	else
	{
		min_limit = 0.0;
	}

	//integrator term adjusting
	if (m_integrator_term > max_limit)
	{
		m_integrator_term = max_limit;
	}
	else if (m_integrator_term < min_limit)
	{
		m_integrator_term = min_limit;
	}

	//band limited derivative term - probably not used form motors


	//compute the output control action
	double out_control{p_term + m_integrator_term};

	//adjust output control depending on motor limits
	if (out_control > m_motor_max_limit)
	{
		out_control = m_motor_max_limit;
	}
	else if (out_control < m_motor_min_limit)
	{
		out_control = m_motor_min_limit;
	}

	//store prev values
	m_prev_error = error;

	//set PID output inside the motor
	m_motor.setSpeed(out_control);
}