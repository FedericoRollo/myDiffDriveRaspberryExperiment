#include "Motor.h"
#include <cassert>
#include <wiringPi.h>
#include <iostream>

void Motor::setForwardDirection()
	{
		digitalWrite(m_forward_pin, HIGH);
		digitalWrite(m_backward_pin, LOW);
	}

void Motor::setBackwardDirection()
{
		digitalWrite(m_forward_pin, LOW);
		digitalWrite(m_backward_pin, HIGH);
}

void Motor::setPWM(int PWM_percentage)
{
	assert(PWM_percentage>=0 && PWM_percentage<=100);

	constexpr int max_PWM_value{1023};

	int PWM_value{(PWM_percentage/100.0)*max_PWM_value};

	pwmWrite(m_PWM_pin, PWM_value);

	if (PWM_value>0)
	{
		m_isMoving=true;
		//std::cout << "Motor is moving\n";
	}
	else //if (PWM_value==0)
	{
		m_isMoving=false;
		//std::cout << "Motor stopped\n";
	}
}