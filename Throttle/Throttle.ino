#include <Throttle.h>

#define DEBUG 1

const int PIN_BUTTON_IN  = 18;
const int PIN_BUTTON_OUT = 19;

const int PIN_RELAY_IN  = 22;
const int PIN_RELAY_OUT = 23;

const int MS_DELAY_THROTTLE = 1250;
const int MS_RELAY_PULSE = 500;

struct Control {
  Throttle button;
  int relayPin;
  const char* name;
  unsigned long lockUntil;
  unsigned long relayUntil;
  bool wasLocked;
  bool relayActive;
};

Control controls[] = {
  { Throttle(PIN_BUTTON_IN, INPUT_PULLUP),  PIN_RELAY_IN,  "In",  0, 0, false, false },
  { Throttle(PIN_BUTTON_OUT, INPUT_PULLUP), PIN_RELAY_OUT, "Out", 0, 0, false, false }
};

const int CONTROL_COUNT = sizeof(controls) / sizeof(controls[0]);

void start();
void processControl(Control &c);
void updateRelay(Control &c);
void showMessage(const char* message);

void setup() {
  Serial.begin(115200);

  start();

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
    snprintf(buffer, sizeof(buffer), "%s detected - Locked", c.name);
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

void start() {
  Serial.println("---------------------");
  Serial.println("    CEPBoard 2.0     ");
  Serial.println("---------------------");
  Serial.println("     By SextaNet     ");
  Serial.println("");
}

void showMessage(const char* message) {
  #if DEBUG
    Serial.println(message);
  #endif
}