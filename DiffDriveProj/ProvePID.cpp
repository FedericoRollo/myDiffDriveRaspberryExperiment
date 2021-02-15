#include "Encoder.h"
#include "Motor.h"
#include "costants.h"
#include "myPID.h"

#include <iostream>
#include <wiringPi.h>
#include <cstdint>
#include <cstdlib>
#include <cassert>

//forward declaration
void discardFirstEncoderInput(int percentage);
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

	double speedRef{50};
	//PID declaring
	myPID left_PID{5.0,0.0,0.0,&speedRef,left_motor,left_encoder};
	myPID right_PID{5.0,0.0,0.0,&speedRef,right_motor,right_encoder};

	int secDelay{100};

	discardFirstEncoderInput(speedRef);

    for (int i = 0; i < 50; ++i)
    {	
    	left_PID.computeStep(secDelay);
    	right_PID.computeStep(secDelay);



    	delay(secDelay);
    }
	return 0;
}

//this function is essentrial to cancell the encoder initial noise error 
void discardFirstEncoderInput(int percentage)
{
	//this five rows have been added in order to cancel out the initial encoder noise which would affect the rotations computations
	//when the motor is stopped
	right_motor.setSpeed(percentage);
	left_motor.setSpeed(percentage);
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