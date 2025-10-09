#include <Stepper.h>
#include <Arduino.h>
#include <Scheduler.h>
#include "config.h"

// Pins entered in sequence IN1-IN3-IN2-IN4 for proper step sequence
Stepper myStepper = Stepper(STEPS_PER_REV_DEFAULT, 
                            PIN_STEPPER_IN1, 
                            PIN_STEPPER_IN3, 
                            PIN_STEPPER_IN2, 
                            PIN_STEPPER_IN4);

Scheduler scheduler;

void stepMotor() {
  // test step 45 deg
  myStepper.step(STEPS_PER_REV_DEFAULT / 8);
}

void setup() {
  myStepper.setSpeed(10);

  int id = scheduler.every(5000, stepMotor);
}

void loop() {
  scheduler.run();
}