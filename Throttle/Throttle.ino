// CEPBoard v2.0
// Throttle library: https://github.com/Gruppio/Throttle

#include <Throttle.h>

#define DEBUG 1

const int PIN_BUTTON_IN  = 18;
const int PIN_BUTTON_OUT = 19;

const int PIN_RELAY_IN  = 22;
const int PIN_RELAY_OUT = 23;

const int MS_DELAY_THROTTLE = 1250;
const int MS_DELAY_GENERAL  = 500;

Throttle buttonIn(PIN_BUTTON_IN, INPUT_PULLUP);
Throttle buttonOut(PIN_BUTTON_OUT, INPUT_PULLUP);

unsigned long lockUntilIn  = 0;
unsigned long lockUntilOut = 0;

void start();

void detectIn();
void detectOut();

void executeAndLock(const char* action, void (*func)(), unsigned long &lockVar);

void triggerRelayIn();
void triggerRelayOut();

void showMessage(const char* message);

void setup() {

  Serial.begin(115200);

  start();

  pinMode(PIN_RELAY_IN, OUTPUT);
  pinMode(PIN_RELAY_OUT, OUTPUT);

  digitalWrite(PIN_RELAY_IN, LOW);
  digitalWrite(PIN_RELAY_OUT, LOW);
}

void loop() {

  detectIn();
  detectOut();
}

void detectIn() {

  buttonIn.update();

  if (buttonIn.fell()) {
    executeAndLock("In", triggerRelayIn, lockUntilIn);
  }
}

void detectOut() {

  buttonOut.update();

  if (buttonOut.fell()) {
    executeAndLock("Out", triggerRelayOut, lockUntilOut);
  }
}

void executeAndLock(const char* action, void (*func)(), unsigned long &lockVar) {

  if (millis() < lockVar) {
    return;
  }

  char buffer[32];

  snprintf(buffer, sizeof(buffer), "%s detected - Locked", action);

  showMessage(buffer);

  func();

  lockVar = millis() + MS_DELAY_THROTTLE;
}

void triggerRelayIn() {
  digitalWrite(PIN_RELAY_IN, HIGH);
  delay(MS_DELAY_GENERAL);
  digitalWrite(PIN_RELAY_IN, LOW);
}

void triggerRelayOut() {
  digitalWrite(PIN_RELAY_OUT, HIGH);
  delay(MS_DELAY_GENERAL);
  digitalWrite(PIN_RELAY_OUT, LOW);
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