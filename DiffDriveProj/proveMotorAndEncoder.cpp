#include "Encoder.h"
#include "Motor.h"

#include <iostream>
#include <wiringPi.h>
#include <cstdint>
#include <cstdlib>
#include <cassert>

//Right motor Pins
constexpr std::uint8_t PWM_right_pin{23};
constexpr std::uint8_t right_forward_pin{5};
constexpr std::uint8_t right_backward_pin{4};

//left motor Pins
constexpr std::uint8_t PWM_left_pin{1};
constexpr std::uint8_t left_forward_pin{2};
constexpr std::uint8_t left_backward_pin{0};

//encoders Pins
constexpr std::uint8_t right_encoder_pin{29};
constexpr std::uint8_t left_encoder_pin{7};

//Parameters
constexpr double wheelCircumference{0.225};
constexpr int pulsesPerTurn{40};

void rightCounter(void);
void leftCounter(void);

Encoder right_encoder{right_encoder_pin, pulsesPerTurn, wheelCircumference, (*rightCounter)};
Encoder left_encoder{left_encoder_pin, pulsesPerTurn, wheelCircumference, (*leftCounter)};

Motor right_motor{PWM_right_pin, right_forward_pin, right_backward_pin};
Motor left_motor{PWM_left_pin, left_forward_pin, left_backward_pin};

int main(int argc, char const *argv[])
{
	if (wiringPiSetup()==-1)
	{
		exit(1);
	}
	std::cout << "Wiring setup completed.\n";

	std::cout << "Enter a PWM signal percentage (35-100): ";

	int percentage{0};
	std::cin >> percentage;

	assert(percentage>=35 && percentage<=100);

	right_motor.setForwardDirection();
	left_motor.setForwardDirection();

	int secDelay{3000};

	//this five rows have been added in order to cancel out the initial encoder noise which would affect the rotations computations
	//when the motor is stopped
	right_motor.setPWM(percentage);
	left_motor.setPWM(percentage);
	delay(100);
	left_encoder.getRotations(secDelay, true);
	right_encoder.getRotations(secDelay, true);

	while(percentage>=35)
	{
		right_motor.setPWM(percentage);
		left_motor.setPWM(percentage);

		std::cout << "The motor is running with a " << percentage << "% PWM signal.\n";
		delay(secDelay);

		std::cout << "After " << secDelay/1000.0 << " seconds, the encoders have read a RPM of:\nl: " << left_encoder.getRotations(secDelay, true) << "\tr:" << right_encoder.getRotations(secDelay,true) << "\n\n";
		
		percentage -= 10;

	}

	return 0;
}


void rightCounter(void)
{
	if (right_motor.isMoving())
	{
		right_encoder.increaseCount();
	}
	
	return;
}

void leftCounter(void)
{
	if (left_motor.isMoving())
	{
		//std::cout << "count\n";
		left_encoder.increaseCount();
	}
	
	return;
}