#ifndef MOTOR_H
#define MOTOR_H

#include <wiringPi.h>
#include <cstdint>

class Motor
{
private:
	std::uint8_t m_PWM_pin;
	std::uint8_t m_forward_pin;
	std::uint8_t m_backward_pin;

	double m_max_speed{};

	bool m_isMoving{false};

public:
	Motor(std::uint8_t PWM_pin, std::uint8_t forward_pin, std::uint8_t backward_pin, double max_speed=70): 
		m_PWM_pin{PWM_pin},
		m_forward_pin{forward_pin},
		m_backward_pin{backward_pin},
		m_max_speed{max_speed}
	{
		pinMode(m_PWM_pin, PWM_OUTPUT);
		pinMode(m_forward_pin, OUTPUT);
		pinMode(m_backward_pin, OUTPUT);
	}

	~Motor()
	{
		this->setPWM(0);
	}

	bool isMoving(){return m_isMoving;}

	double getMaxSpeed(){return m_max_speed;}

	void setForwardDirection();

	void setBackwardDirection();

	void setPWM(int PWM_percentage);
	void setPWM(double PWM_percentage);

	bool setSpeed(double motorSpeed); //cm/s

};

#endif
