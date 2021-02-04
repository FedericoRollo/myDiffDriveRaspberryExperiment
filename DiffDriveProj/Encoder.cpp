#include "Encoder.h"

#include <iostream>


double Encoder::getRotations(int secDelay, bool RPM)
{
	double delayRatioPerSeconds{1000.0/secDelay};

	double rotations{getCountTurnRatio()*delayRatioPerSeconds};

	if (RPM)
	{
		return rotations*60; // RPM
	}
	return rotations; //RPS
}


double Encoder::getSpeed(int secDelay)
{
	if (m_wheelCircumference<=0.0)
	{
		std::cerr << "The wheel circumference has NOT been initialized.\nYou MUST assign a valid value to the circumference if you want to use this method.\n";
	}

	//compute the RPS with getRotations and then multiply them for the wheel circumference
	//the counter is reset by the getRotations function. 
	auto speed{getRotations(secDelay,false)*getWheelCircumference()};

	std::cout << "Rotation speed: " << speed <<'\n';

	return speed; // cm/s
}