// CEPBoard v1.1

// Throttle library: https://github.com/Gruppio/Throttle

#include <Arduino.h>
#include <Throttle.h>

const bool DEBUG = true;

const int PIN_BUTTON_IN = 18;
const int PIN_BUTTON_OUT = 19;

const int PIN_RELAY_IN = 22;
const int PIN_RELAY_OUT = 23;

const int MS_DELAY_THROTTLE = 1250; //1250
const int MS_DELAY_GENERAL = 500;

Throttle buttonIn = Throttle(PIN_BUTTON_IN, INPUT_PULLUP);
Throttle buttonOut = Throttle(PIN_BUTTON_OUT, INPUT_PULLUP);

void setup() {
  Serial.begin(115200);

  welcome();
  
  pinMode(PIN_RELAY_IN, OUTPUT);
  pinMode(PIN_RELAY_OUT, OUTPUT);
}

void detectIn() {
  buttonIn.update();
  if (buttonIn.fell()) {
     showMessage("In marked!");
     triggerRelay();
     delay(MS_DELAY_THROTTLE);
   }
}

void detectOut() {
  buttonOut.update();
  if (buttonOut.fell()) {
     showMessage("Out marked!");
     triggerRelayOut();
     delay(MS_DELAY_THROTTLE);
   }
}

void triggerRelay() {
  digitalWrite(PIN_RELAY_IN, HIGH);
  delay(MS_DELAY_GENERAL);
  digitalWrite(PIN_RELAY_IN, LOW);
}

void triggerRelayOut() {
  digitalWrite(PIN_RELAY_OUT, HIGH);
  delay(MS_DELAY_GENERAL);
  digitalWrite(PIN_RELAY_OUT, LOW);
}

void welcome() {
  Serial.println("Starting CEPBoard...");
  Serial.println("By SextaNet to BHP");
}

void showMessage(char *message) {
  if (DEBUG) {
    Serial.println(message);
  }
}

void loop() {
  detectIn();
  detectOut();
}
