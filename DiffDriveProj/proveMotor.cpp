#include <cstdlib>
#include <iostream>
#include <wiringPi.h>
#include <cstdint>

#include "Motor.h"


//Right motor Pins
constexpr std::uint8_t PWM_right_pin{23};
constexpr std::uint8_t right_forward_pin{5};
constexpr std::uint8_t right_backward_pin{4};

//left motor Pins
constexpr std::uint8_t PWM_left_pin{1};
constexpr std::uint8_t left_forward_pin{2};
constexpr std::uint8_t left_backward_pin{0};

int main(int argc, char const *argv[])
{	
	//setup the wiring pi library
	if (wiringPiSetup() == -1)
	{
		exit(1);
	}
	std::cout << "Connection established\n";

	Motor right_motor{PWM_right_pin, right_forward_pin, right_backward_pin};

	right_motor.setForwardDirection();
	std::cout << "Direction set to Forward\n";

	int percentage{0};

	for (int i = 0; i < 3; ++i)
	{
		std::cout << "Enter a velocity percentage(0-100): ";
		std::cin >> percentage;

		right_motor.setPWM(percentage);
	}

	delay(3000);
	right_motor.setPWM(0);
	right_motor.setBackwardDirection();
	std::cout << "Direction set to Backward\n";

	for (int i = 0; i < 3; ++i)
	{
		std::cout << "Enter a velocity percentage(0-100): ";
		std::cin >> percentage;
		
		right_motor.setPWM(percentage);
	}

	delay(3000);

	std::cout << "Stop!\n";
	right_motor.setPWM(0);

	return 0;
}