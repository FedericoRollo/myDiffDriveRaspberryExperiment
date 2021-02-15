#include "Encoder.h"
#include "Motor.h"
#include "costants.h"

#include <iostream>
#include <wiringPi.h>
#include <cstdint>
#include <cstdlib>
#include <fstream>

//forward declaration
void discardFirstEncoderInput(double percentage);
void rightCounter(void);
void leftCounter(void);

//global Encoders declaration
Encoder right_encoder{right_encoder_pin, pulsesPerTurn, wheelCircumference, (*rightCounter)};
Encoder left_encoder{left_encoder_pin, pulsesPerTurn, wheelCircumference, (*leftCounter)};

//Motors declaration
Motor right_motor{PWM_right_pin, right_forward_pin, right_backward_pin};
Motor left_motor{PWM_left_pin, left_forward_pin, left_backward_pin};

int main(int argc, char const *argv[])
{
	// setup the wiringPi library
	if (wiringPiSetup()==-1)
	{
		exit(1);
	}	
	std::cout << "Wiring setup completed.\n";

	//set forward motion for both the motors
	right_motor.setForwardDirection();
	left_motor.setForwardDirection();


	int secDelay{500};

	std::ofstream dataUp("dataUp.txt");
	std::ofstream dataDown("dataDown.txt");

	//dataFile.open("data.txt");

	

	for (double currPWM = 30.0; currPWM < 100; currPWM+=0.1)
	{
		discardFirstEncoderInput(currPWM);

		std::cout << currPWM <<'\n';
		delay(secDelay);

		dataUp << currPWM << ' ' << left_encoder.getRotations(secDelay,true) << ' ' << right_encoder.getRotations(secDelay,true) << '\n';

	}
	for (double currPWM = 100.0; currPWM > 0; currPWM-=0.1)
	{
		discardFirstEncoderInput(currPWM);


		std::cout << currPWM<<'\n';	
		delay(secDelay);

		dataDown << currPWM << ' ' << left_encoder.getRotations(secDelay,true) << ' ' << right_encoder.getRotations(secDelay,true) << '\n';

	}

	dataUp.close();
	dataDown.close();

	return 0;
}

//this function is essentrial to cancell the encoder initial noise error 
void discardFirstEncoderInput(double percentage)
{
	//this five rows have been added in order to cancel out the initial encoder noise which would affect the rotations computations
	//when the motor is stopped
	right_motor.setPWM(percentage);
	left_motor.setPWM(percentage);
	delay(100); // this is the minimal delay to use before read the values
	left_encoder.resetCount();
	right_encoder.resetCount();

}

// right counter function
void rightCounter(void)
{
	if (right_motor.isMoving())
	{
		right_encoder.increaseCount();
	}
	
	return;
}

// left counter function
void leftCounter(void)
{
	if (left_motor.isMoving())
	{
		//std::cout << "count\n";
		left_encoder.increaseCount();
	}
	
	return;
}