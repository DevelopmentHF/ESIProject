#include <Stepper.h>
#include <Arduino.h>
#include <Scheduler.h>
#include "config.h"
#include <EEPROM.h>

// Pins entered in sequence IN1-IN3-IN2-IN4 for proper step sequence
Stepper myStepper = Stepper(STEPS_PER_REV_DEFAULT, 
                            PIN_STEPPER_IN1, 
                            PIN_STEPPER_IN3, 
                            PIN_STEPPER_IN2, 
                            PIN_STEPPER_IN4);

Scheduler scheduler;

int spinnerID, buzzerID;
int numRotations;

const int EE_ADDR = 0;  // where to store the int (uses 2 bytes on AVR)


void playBuzzer() {
  // alert user
  digitalWrite(PIN_BUZZER, HIGH);
}

void turnOffBuzzer() {
  digitalWrite(PIN_BUZZER, LOW);
}

// save an int to EEPROM
void saveInt(int value) {
  EEPROM.put(EE_ADDR, value); 
}

// load an int from EEPROM
int loadInt() {
  int value;
  EEPROM.get(EE_ADDR, value);
  return value;
}

void stepMotor() {
  // test step 45 deg
  myStepper.step(STEPS_PER_REV_DEFAULT / 8);

  if (numRotations == 8) {
    numRotations = 1;
  } else {
    numRotations++;
  }

  saveInt(numRotations);
}

// Helpers to map ON/OFF to the module's polarity
inline void relayOn()  { digitalWrite(RELAY_PIN, RELAY_ACTIVE_LOW ? LOW  : HIGH); }
inline void relayOff() { digitalWrite(RELAY_PIN, RELAY_ACTIVE_LOW ? HIGH : LOW ); }

void setup() {
  myStepper.setSpeed(10);

  int savedRotations = loadInt();
  if (savedRotations > 8 || savedRotations < 1) {
    numRotations = 1;
  } else {
    numRotations = savedRotations;
  }


  spinnerID = scheduler.every(DISPENSE_DURATION_MS, stepMotor);
  buzzerID = scheduler.every(DISPENSE_DURATION_MS, playBuzzer);

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

  // turn off alarm
  if (digitalRead(PIN_BTN) == LOW) {
    turnOffBuzzer();
  }

  // on refill day
  if (numRotations % 8 == 0) {
    scheduler.setEnable(spinnerID, false);
    scheduler.setEnable(buzzerID, false);

    playBuzzer();

    // move back to square 1.
    if (digitalRead(PIN_BTN) == LOW) {
      stepMotor();
      
      turnOffBuzzer();

      scheduler.setEnable(spinnerID, true);
      scheduler.setEnable(buzzerID, true);
    }
  }

}