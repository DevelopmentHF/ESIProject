#pragma once

// number of steps the stepper motor takes by default
constexpr long STEPS_PER_REV_DEFAULT = 2048;

// stepper motor pins from driver board
constexpr unsigned char PIN_STEPPER_IN1 = 8;
constexpr unsigned char PIN_STEPPER_IN2 = 9;
constexpr unsigned char PIN_STEPPER_IN3 = 10;
constexpr unsigned char PIN_STEPPER_IN4 = 11;

constexpr unsigned char RELAY_PIN = 13;
const bool RELAY_ACTIVE_LOW = false; 

constexpr unsigned char PIN_BTN = 2;
constexpr unsigned char PIN_BUZZER = 4;

constexpr unsigned int DISPENSE_DURATION_SECONDS = 10;