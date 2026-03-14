// CEPBoard v1.1

// Throttle library: https://github.com/Gruppio/Throttle

#include <Arduino.h>
#include <Throttle.h>

const bool DEBUG = true;

const int BOTON_PIN_ENTRADA = 23;
const int BOTON_PIN_SALIDA = 22;

const int RELAY_ENTRADA = 18;
const int RELAY_SALIDA = 19;

const int ESPERA_MS_ENTRADA_DESPUES = 1250;
const int ESPERA_MS_SALIDA_DESPUES = 1250;


Throttle botonEntrada = Throttle(BOTON_PIN_ENTRADA, INPUT_PULLUP);
Throttle botonSalida = Throttle(BOTON_PIN_SALIDA, INPUT_PULLUP);

void setup() {
  Serial.begin(115200);
  showMessage("Iniciando...");
  
  pinMode(RELAY_ENTRADA, OUTPUT);
  pinMode(RELAY_SALIDA, OUTPUT);
}

void showMessage(char *message) {
  if (DEBUG) {
    Serial.println(message);
  }
}

void detectarEntrada() {
  botonEntrada.update();
  if (botonEntrada.fell()) {
     showMessage("Se marcó la entrada!");
     activarRelayEntrada();
     delay(ESPERA_MS_ENTRADA_DESPUES);
   }
}

void detectarSalida() {
  botonSalida.update();
  if (botonSalida.fell()) {
     showMessage("Se marcó la salida!");
     activarRelaySalida();
     delay(ESPERA_MS_SALIDA_DESPUES);
   }
}

void activarRelayEntrada() {
  digitalWrite(RELAY_ENTRADA, HIGH);
  delay(500);
  digitalWrite(RELAY_ENTRADA, LOW);
}

void activarRelaySalida() {
  digitalWrite(RELAY_SALIDA, HIGH);
  delay(500);
  digitalWrite(RELAY_SALIDA, LOW);
}

void loop() {
   detectarEntrada();
   detectarSalida();
}
