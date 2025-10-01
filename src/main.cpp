#include <Stepper.h>
#include <Arduino.h>
#include "config.h"

// Pins entered in sequence IN1-IN3-IN2-IN4 for proper step sequence
Stepper myStepper = Stepper(STEPS_PER_REV_DEFAULT, 
                            PIN_STEPPER_IN1, 
                            PIN_STEPPER_IN3, 
                            PIN_STEPPER_IN2, 
                            PIN_STEPPER_IN4);

void setup() {
  
}

void loop() {
  // Rotate CW slowly at 5 RPM
  myStepper.setSpeed(5);
  myStepper.step(STEPS_PER_REV_DEFAULT);
  delay(1000);

  // Rotate CCW quickly at 10 RPM
  myStepper.setSpeed(10);
  myStepper.step(-STEPS_PER_REV_DEFAULT);
  delay(1000);
}