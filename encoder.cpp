#include <wiringPi.h>
#include <iostream>
#include <cstdlib>
#include <array>

//right motor pins
constexpr int PWM_right_pin{23};
constexpr int right_forward_pin{5};
constexpr int right_backward_pin{4};

//left motor Pins
const int PWM_left_pin{1};
const int left_forward_pin{2};
const int left_backward_pin{0};

//encoders pins
constexpr int right_encoder_pin{29};
constexpr int left_encoder_pin{7};

//pulses per encoder turn
constexpr int pulsesPerTurn{40};

//Encoder counters
static int count_right{0};
static int count_left{0};

//Callback function for the right counter
void rightCounter(void)
{
	++count_right;
	delay(5);
	return;
}

//Callback function for the left counter
void leftCounter(void)
{
	++count_left;
	delay(5);
	return;
}

//read and reinitialize the right encoder counter
int readRightCount()
{
	auto temp=count_right;
	count_right=0;
	return temp;
}

//read and reinitialize the left encoder counter
int readLeftCount()
{
	auto temp=count_left;
	count_left=0;
	return temp;
}

//*******MAIN*******//
int main(int argc, char const *argv[])
{
	//setup the wiring pi library
	if (wiringPiSetup()==-1)
	{
		exit(1);
	}
	std::cout << "Connection established\n";

	// pin mode declaration input, output, pwm_output
	pinMode(right_encoder_pin, INPUT);
	pinMode(left_encoder_pin, INPUT); /////

	pinMode(PWM_right_pin, PWM_OUTPUT);
	pinMode(right_forward_pin, OUTPUT);
	pinMode(right_backward_pin, OUTPUT);

	pinMode(PWM_left_pin, PWM_OUTPUT);
	pinMode(left_forward_pin, OUTPUT);
	pinMode(left_backward_pin, OUTPUT);

	//declaration of the interrupt function for the encoder counters
	wiringPiISR(right_encoder_pin, INT_EDGE_BOTH, rightCounter);
	wiringPiISR(left_encoder_pin, INT_EDGE_BOTH, leftCounter);

	//number of readings for the encoder counters
	constexpr int numberTrials{20};

	//array used to store the counters for statistics purposes
	std::array<int,numberTrials> rightPulses{};
	std::array<int,numberTrials> leftPulses{};

	//settings of motors pins for direction and pwm intensity
	digitalWrite(right_forward_pin,HIGH);
	digitalWrite(right_backward_pin,LOW);
	pwmWrite(PWM_right_pin, 1000);

	digitalWrite(left_forward_pin,HIGH);
	digitalWrite(left_backward_pin,LOW);
	pwmWrite(PWM_left_pin, 1000);

	int secDelay{100};

	// count the pulses of the encoders
	for (int i = 0; i < numberTrials; ++i)
	{
		// reading delay
		delay(secDelay);

		//read and reset the encoder counters
		auto rightCurrPulses{readRightCount()};
		auto leftCurrPulses{readLeftCount()};

		//store the current counter in the arrays
		rightPulses[i]=rightCurrPulses;
		leftPulses[i]=leftCurrPulses;

		std::cout << "Counter after 1 sec\n" << "l: " <<leftCurrPulses <<"\tr: " <<rightCurrPulses<<'\n';
	}

	int totRightPulses{0};
	int totLeftPulses{0};

	//sum all the pulses for statatistics puposes
	for (int i = 0; i < numberTrials; ++i)
	{
		totRightPulses+=rightPulses[i];
		totLeftPulses+=leftPulses[i];
	}

	//computation of the right and left turns mean
	double rightMean{static_cast<double>(totRightPulses/numberTrials)};
	double leftMean{static_cast<double>(totLeftPulses/numberTrials)};

	//this variable represent the constant ratio between one second and the encoder reading delay
	//it is used to compute the mean round per second from the encoder reading mean
	const double roundPerSecondRatio{1000./secDelay};

	double rightTurns{(rightMean/pulsesPerTurn)*roundPerSecondRatio};
	double leftTurns{(leftMean/pulsesPerTurn)*roundPerSecondRatio};

	std::cout << "\nThe wheels has performed:\nl: " << leftTurns*60 <<" RPM\tr:" << rightTurns*60 << " RPM\n";

	//stop the wheels.. otherwise you should run after your mobile robot :) 
	pwmWrite(PWM_right_pin, 0);
	pwmWrite(PWM_left_pin, 0);


	return 0;
}