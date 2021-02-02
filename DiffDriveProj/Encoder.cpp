#include "Encoder.h"

#include <iostream>


double Encoder::getRotations(double delayRatioPerSeconds, bool RPM)
{
	double rotations{getCountTurnRatio()*delayRatioPerSeconds};

	if (RPM)
	{
		return rotations*60; // RPM
	}
	return rotations; //RPS
}


double Encoder::getSpeed(double delayRatioPerSeconds)
{
	if (m_wheelCircumference<=0.0)
	{
		std::cerr << "The wheel circumference has NOT been initialized.\nYou MUST assign a value to the circumference if you want to use this method.\n";
	}

	//compute the RPS with getRotations and then multiply them for the wheel circumference
	//the counter is reset by the getRotations function. 
	auto speed{getRotations(delayRatioPerSeconds,false)*getWheelCircumference()};

	return speed; // m/s
}