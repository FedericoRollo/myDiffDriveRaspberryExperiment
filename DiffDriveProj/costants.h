#ifndef COSTANTS_H
#define COSTANTS_H

//Right motor Pins
constexpr std::uint8_t PWM_right_pin{23};
constexpr std::uint8_t right_forward_pin{5};
constexpr std::uint8_t right_backward_pin{4};

//left motor Pins
constexpr std::uint8_t PWM_left_pin{1};
constexpr std::uint8_t left_forward_pin{2};
constexpr std::uint8_t left_backward_pin{0};

//encoders Pins
constexpr std::uint8_t right_encoder_pin{29};
constexpr std::uint8_t left_encoder_pin{7};

//Parameters
constexpr double wheelCircumference{0.225};
constexpr int pulsesPerTurn{40};

#endif