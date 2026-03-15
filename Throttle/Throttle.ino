// CEPBoard v1.1

// Throttle library: https://github.com/Gruppio/Throttle

#include <Arduino.h>
#include <Throttle.h>

const bool DEBUG = true;

const int PIN_BUTTON_IN = 18;
const int PIN_BUTTON_OUT = 19;

const int PIN_RELAY_IN = 22;
const int PIN_RELAY_OUT = 23;

const int MS_DELAY_IN = 1250;
const int MS_DELAY_OUT = 1250;

Throttle buttonIn = Throttle(PIN_BUTTON_IN, INPUT_PULLUP);
Throttle buttonOut = Throttle(PIN_BUTTON_OUT, INPUT_PULLUP);

void setup() {
  Serial.begin(115200);
  showMessage("Starting CEPBoard...");
  
  pinMode(PIN_RELAY_IN, OUTPUT);
  pinMode(PIN_RELAY_OUT, OUTPUT);
}

void showMessage(char *message) {
  if (DEBUG) {
    Serial.println(message);
  }
}

void detectIn() {
  buttonIn.update();
  if (buttonIn.fell()) {
     showMessage("In marked!");
     activarRelayEntrada();
     delay(MS_DELAY_IN);
   }
}

void detectOut() {
  buttonOut.update();
  if (buttonOut.fell()) {
     showMessage("Out marked!");
     activarRelaySalida();
     delay(MS_DELAY_OUT);
   }
}

void activarRelayEntrada() {
  digitalWrite(PIN_RELAY_IN, HIGH);
  delay(500);
  digitalWrite(PIN_RELAY_IN, LOW);
}

void activarRelaySalida() {
  digitalWrite(PIN_RELAY_OUT, HIGH);
  delay(500);
  digitalWrite(PIN_RELAY_OUT, LOW);
}

void loop() {
  detectIn();
  detectOut();
}
