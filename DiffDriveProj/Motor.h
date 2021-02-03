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

	bool m_isMoving{false};

public:
	Motor(std::uint8_t PWM_pin, std::uint8_t forward_pin, std::uint8_t backward_pin): 
		m_PWM_pin{PWM_pin},
		m_forward_pin{forward_pin},
		m_backward_pin{backward_pin} 
	{
		pinMode(m_PWM_pin, PWM_OUTPUT);
		pinMode(m_forward_pin, OUTPUT);
		pinMode(m_backward_pin, OUTPUT);
	}

	~Motor()
	{
		this->setPWM(0);
	}

/*	std::uint8_t getForwardPin(){return m_forward_pin;}

	std::uint8_t getBackwardPin(){return m_backward_pin;}

	std::uint8_t getPWMPin(){return m_PWM_pin;}*/

	bool isMoving(){return m_isMoving;}

	void setForwardDirection();

	void setBackwardDirection();

	void setPWM(int PWM_percentage);

};

#endif