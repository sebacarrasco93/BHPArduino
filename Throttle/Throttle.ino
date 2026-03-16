#include <Throttle.h>

#define DEBUG 1

#define LED_BLINK_IN 360 // 2 times
#define LED_BLINK_OUT 180 // 4 times

const int PIN_BUTTON_IN  = 26;
const int PIN_BUTTON_OUT = 27;

const int PIN_RELAY_IN  = 32;
const int PIN_RELAY_OUT = 33;

const int PIN_INTERNAL_LED = 2;

const int MS_DELAY_THROTTLE = 1250;
const int MS_RELAY_PULSE = 500;

unsigned long INTERNAL_LED_LAST_TOGGLE = 0;
bool INTERNAL_LED_STATE = false;

struct Control {
  Throttle button;
  int relayPin;
  const char* name;
  unsigned long lockUntil;
  unsigned long relayUntil;
  bool wasLocked;
  bool relayActive;
  int ledInterval;
};

Control controls[] = {
  { Throttle(PIN_BUTTON_IN, INPUT_PULLUP),  PIN_RELAY_IN,  "In",  0, 0, false, false, LED_BLINK_IN },
  { Throttle(PIN_BUTTON_OUT, INPUT_PULLUP), PIN_RELAY_OUT, "Out", 0, 0, false, false, LED_BLINK_OUT }
};

const int CONTROL_COUNT = sizeof(controls) / sizeof(controls[0]);

void start();
void processControl(Control &c);
void updateRelay(Control &c);
void updateInternalLed();
void showMessage(const char* message);

void setup() {
  Serial.begin(115200);

  start();

  pinMode(PIN_INTERNAL_LED, OUTPUT);

  for (int i = 0; i < CONTROL_COUNT; i++) {
    pinMode(controls[i].relayPin, OUTPUT);
    digitalWrite(controls[i].relayPin, LOW);
  }
}

void loop() {
  for (int i = 0; i < CONTROL_COUNT; i++) {
    processControl(controls[i]);
  }

  for (int i = 0; i < CONTROL_COUNT; i++) {
    updateRelay(controls[i]);
  }

  updateInternalLed();
}

void processControl(Control &c) {
  c.button.update();

  if (c.wasLocked && millis() >= c.lockUntil) {
    char buffer[32];
    snprintf(buffer, sizeof(buffer), "%s Unlocked", c.name);
    showMessage(buffer);
    c.wasLocked = false;
  }

  if (millis() < c.lockUntil) {
    return;
  }

  if (c.button.fell()) {

    char buffer[32];
    snprintf(buffer, sizeof(buffer), "%s Locked (detected)", c.name);
    showMessage(buffer);

    digitalWrite(c.relayPin, HIGH);

    c.relayActive = true;
    c.relayUntil = millis() + MS_RELAY_PULSE;

    c.lockUntil = millis() + MS_DELAY_THROTTLE;
    c.wasLocked = true;
  }
}

void updateRelay(Control &c) {
  if (c.relayActive && millis() >= c.relayUntil) {
    digitalWrite(c.relayPin, LOW);
    c.relayActive = false;
  }
}

void updateInternalLed() {
  int interval = 0;

  for (int i = 0; i < CONTROL_COUNT; i++) {

    if (controls[i].wasLocked) {

      if (interval == 0 || controls[i].ledInterval < interval) {
        interval = controls[i].ledInterval;
      }

    }
  }

  if (interval == 0) {
    digitalWrite(PIN_INTERNAL_LED, LOW);
    INTERNAL_LED_STATE = false;
    return;
  }

  if (millis() - INTERNAL_LED_LAST_TOGGLE >= interval) {
    INTERNAL_LED_LAST_TOGGLE = millis();
    INTERNAL_LED_STATE = !INTERNAL_LED_STATE;
    digitalWrite(PIN_INTERNAL_LED, INTERNAL_LED_STATE);
  }
}

void start() {
  Serial.println("");
  Serial.println("");
  Serial.println("---------------------");
  Serial.println("    CEPBoard 2.0     ");
  Serial.println("---------------------");
  Serial.println("     By SextaNet     ");
  Serial.println("");
  Serial.println("");
}

void showMessage(const char* message) {
  #if DEBUG
    Serial.println(message);
  #endif
}