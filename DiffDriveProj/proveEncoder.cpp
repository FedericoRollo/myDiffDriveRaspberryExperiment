#include "Encoder.h"
#include <iostream>
#include <cstdint>
#include <wiringPi.h>

constexpr std::uint8_t right_encoder_pin{29};
constexpr std::uint8_t left_encoder_pin{7};

constexpr double wheelCircumference{0.225};
constexpr int pulsesPerTurn{40};

//this two function are needed because the interrupts don't work with class member function(increaseCount())
//using function pointers instead this limit can be overcomemed but the solution is not really elegant..
void rightCounter(void);
void leftCounter(void);

//the encoders are declared global otherwhise the counter function cannot see them (out of scope)
Encoder right_encoder{right_encoder_pin, pulsesPerTurn, wheelCircumference, (*rightCounter) };
Encoder left_encoder{left_encoder_pin, pulsesPerTurn, wheelCircumference, (*leftCounter) };

int main(int argc, char const *argv[])
{
	if(wiringPiSetup()==-1)
	{
		exit(1);
	}

	int secDelay{1000};
	double delayRatioPerSeconds{1000.0/secDelay};

	while(1)
	{
		delay(secDelay);
		std::cout << "count: " << right_encoder.getRotations(delayRatioPerSeconds) <<"\n";
		
	}

	
	return 0;
}

void rightCounter(void)
{
	right_encoder.increaseCount();
}

void leftCounter(void)
{
	left_encoder.increaseCount();
}