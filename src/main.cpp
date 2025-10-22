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

void playBuzzer() {
  // alert user
  digitalWrite(PIN_BUZZER, HIGH);
}

void turnOffBuzzer() {
  digitalWrite(PIN_BUZZER, LOW);
}

// Helpers to map ON/OFF to the module's polarity
inline void relayOn()  { digitalWrite(RELAY_PIN, RELAY_ACTIVE_LOW ? LOW  : HIGH); }
inline void relayOff() { digitalWrite(RELAY_PIN, RELAY_ACTIVE_LOW ? HIGH : LOW ); }

void setup() {
  myStepper.setSpeed(10);

  int id = scheduler.every(DISPENSE_DURATION_SECONDS, stepMotor);
  int buzzer = scheduler.every(DISPENSE_DURATION_SECONDS, playBuzzer);

  pinMode(RELAY_PIN, OUTPUT);
  pinMode(PIN_BTN, INPUT_PULLUP); // pullup when not pressed.
  pinMode(PIN_BUZZER, OUTPUT);

  // Make sure we're OFF at boot
  relayOff();
  delay(20); 
  relayOn();
}


void loop() {
  scheduler.run();

  if (digitalRead(PIN_BTN) == LOW) {
    turnOffBuzzer();
  }
}