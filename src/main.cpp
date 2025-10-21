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
  delay(2500);
  digitalWrite(PIN_BUZZER, HIGH); // Turn the buzzer on
  delay(1000);                  // Keep it on for 1 second
  digitalWrite(PIN_BUZZER, LOW);
}

// Helpers to map ON/OFF to the module's polarity
inline void relayOn()  { digitalWrite(RELAY_PIN, RELAY_ACTIVE_LOW ? LOW  : HIGH); }
inline void relayOff() { digitalWrite(RELAY_PIN, RELAY_ACTIVE_LOW ? HIGH : LOW ); }

void setup() {
  myStepper.setSpeed(10);

  int id = scheduler.every(5000, stepMotor);
  int buzzer = scheduler.every(5000, playBuzzer);

  pinMode(RELAY_PIN, OUTPUT);
  pinMode(PIN_BUZZER, OUTPUT);

  // Make sure we're OFF at boot
  // TODO: WRONG GENERATED CODE. RELAYOFF IS RELAYON
  relayOff();
  delay(20); 
}


// TODO: Put arduino to sleep instead?
void loop() {
  scheduler.run();
}