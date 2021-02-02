#ifndef ENCODER_H
#define ENCODER_H

#include <cstdint>
#include <iostream>
#include <wiringPi.h>

class Encoder
{
private:

	const std::uint8_t m_encoderPin{};

	const int m_pulsesPerTurn{};

	//in meters
	const double m_wheelCircumference{};

	// m_count is used as an iteger but defining it as double it simplifies some double casting in the class
	int m_count{0};

public:

	Encoder(std::uint8_t encoder_pin, int pulsesPerTurn, double wheelCircumference=0.0, void (*counter)(void) = nullptr):
		m_encoderPin{encoder_pin},
		m_pulsesPerTurn{pulsesPerTurn},
		m_wheelCircumference{wheelCircumference}
	{
		wiringPiSetup();
		//set the pin mode
		pinMode(m_encoderPin, INPUT);
		//set the interrupt counter
		wiringPiISR(m_encoderPin, INT_EDGE_BOTH, counter);
		//encoderInit();
	}

	void increaseCount(){++m_count;}

	int getCount()
	{
		auto temp{m_count};
		m_count = 0;
		return temp;
	}

	double getCountTurnRatio(){return getCount()/static_cast<double>(m_pulsesPerTurn);}

	double getWheelCircumference(){return m_wheelCircumference;}

	double getRotations(double delayRatioPerSeconds, bool RPM=true);

	double getSpeed(double delayRatioPerSeconds);

};

#endif