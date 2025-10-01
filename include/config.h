#pragma once

// number of steps the stepper motor takes by default
constexpr long STEPS_PER_REV_DEFAULT = 2048;

// stepper motor pins from driver board
constexpr unsigned char PIN_STEPPER_IN1 = 8;
constexpr unsigned char PIN_STEPPER_IN2 = 9;
constexpr unsigned char PIN_STEPPER_IN3 = 10;
constexpr unsigned char PIN_STEPPER_IN4 = 11;

// how many jobs can the scheduler store
constexpr unsigned char MAX_JOBS = 8;