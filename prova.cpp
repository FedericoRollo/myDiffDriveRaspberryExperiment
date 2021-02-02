#include <wiringPi.h>
#include <iostream>
#include <cstdlib>
#include <array>

constexpr int PWM_right_pin{23};
constexpr int right_forward_pin{5};
constexpr int right_backward_pin{4};

constexpr int right_encoder_pin{29};
constexpr int left_encoder_pin{7};

static int count{0};

void counter(void)
{
	++count;
	delay(5); //DON'T decrease the delay otherwise the raspbarry restart itself..

	return;
}

int readCount()
{
	auto temp=count;
	count=0;

	return temp;
}

int main(int argc, char const *argv[])
{
	if (wiringPiSetup()==-1)
	{
		exit(1);
	}
	std::cout << "Connection established\n";

	pinMode(right_encoder_pin, INPUT);

	pinMode(PWM_right_pin, PWM_OUTPUT);
	pinMode(right_forward_pin, OUTPUT);
	pinMode(right_backward_pin, OUTPUT);

	wiringPiISR(right_encoder_pin, INT_EDGE_BOTH, counter);

	digitalWrite(right_forward_pin,HIGH);
	digitalWrite(right_backward_pin,LOW);

	pwmWrite(PWM_right_pin, 600);

	while(1)
	{
		std::cout << readCount() << '\n';
		delay(1000);
	}


	
/*
	


	for (int i = 0; i < 10; ++i)
	{

		delay(1000);

		std::cout << "Pulses after 1 sec: " << readCount() <<'\n';

	}
*/

	//pwmWrite(PWM_right_pin, 0);

	return 0;
}