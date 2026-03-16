#include <Throttle.h>
#include <esp_system.h>

#define DEBUG 1

#define LED_BLINK_IN 360 // 2 times
#define LED_BLINK_OUT 180 // 4 times

#define AUTO_RESTART_MINUTES 43200

const int PIN_BUTTON_IN  = 26;
const int PIN_BUTTON_OUT = 27;

const int PIN_RASPBERRY_IN = 32;
const int PIN_RASPBERRY_OUT = 33;

const int PIN_INTERNAL_LED = 2;

const int MS_DELAY_THROTTLE = 1250;
const int MS_RELAY_PULSE = 500;

const unsigned long AUTO_RESTART_MS =
  (unsigned long)AUTO_RESTART_MINUTES * 60UL * 1000UL;

unsigned long ledLastToggle = 0;
bool ledState = false;

unsigned long bootTime = 0;

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
  { Throttle(PIN_BUTTON_IN, INPUT_PULLUP), PIN_RASPBERRY_IN, "In", 0, 0, false, false, LED_BLINK_IN },
  { Throttle(PIN_BUTTON_OUT, INPUT_PULLUP), PIN_RASPBERRY_OUT, "Out", 0, 0, false, false, LED_BLINK_OUT }
};

const int CONTROL_COUNT = sizeof(controls) / sizeof(controls[0]);

void start();
void processControl(Control &c);
void updateRelay(Control &c);
void updateInternalLed();
void checkAutoRestart();
void showMessage(const char* message);

void setup() {
  Serial.begin(115200);

  start();

  bootTime = millis();

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

  checkAutoRestart();

  delay(1);
}

void processControl(Control &c) {
  c.button.update();

  if (c.wasLocked && (long)(millis() - c.lockUntil) >= 0) {
    char buffer[32];
    snprintf(buffer, sizeof(buffer), "%s Unlocked", c.name);
    showMessage(buffer);
    c.wasLocked = false;
  }

  if ((long)(millis() - c.lockUntil) < 0) {
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
  if (c.relayActive && (long)(millis() - c.relayUntil) >= 0) {
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
    ledState = false;
    return;
  }

  if ((long)(millis() - ledLastToggle) >= interval) {
    ledLastToggle = millis();
    ledState = !ledState;
    digitalWrite(PIN_INTERNAL_LED, ledState);
  }
}

void checkAutoRestart() {
  if (AUTO_RESTART_MINUTES == 0) {
    return;
  }

  if ((long)(millis() - bootTime) >= AUTO_RESTART_MS) {
    showMessage("Auto restart");

    delay(100);

    ESP.restart();
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