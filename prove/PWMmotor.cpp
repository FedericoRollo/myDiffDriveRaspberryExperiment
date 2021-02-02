#include <wiringPi.h>
#include <stdio.h>
#include <cstdlib>
#include <iostream>

//Right motor Pins
const int PWM_right_pin{23};
const int right_forward_pin{5};
const int right_backward_pin{4};

//left motor Pins
const int PWM_left_pin{1};
const int left_forward_pin{2};
const int left_backward_pin{0};

//Encoder pins


int main(int argc, char const *argv[])
{

	//setup the wiring pi library
	if (wiringPiSetup() == -1)
	{
		exit(1);
	}
	std::cout << "Connection established\n";

	//select the pinmode for the
	pinMode(left_forward_pin, OUTPUT);
	pinMode(left_backward_pin, OUTPUT);
	pinMode(right_forward_pin, OUTPUT);
	pinMode(right_backward_pin, OUTPUT);

	pinMode(PWM_right_pin, PWM_OUTPUT);
	pinMode(PWM_left_pin, PWM_OUTPUT);

	std::cout << "PinMode set\n";
	
	digitalWrite(left_forward_pin,HIGH);
	digitalWrite(left_backward_pin,LOW);
	digitalWrite(right_forward_pin,HIGH);
	digitalWrite(right_backward_pin,LOW);
	
	std::cout << "3\n";
	pwmWrite(PWM_right_pin, 900);
	pwmWrite(PWM_left_pin, 900);
	delay(4000);

	pwmWrite(PWM_right_pin, 0);
	pwmWrite(PWM_left_pin, 0);
	
	return 0;
}