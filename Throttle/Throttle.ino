// Tortuga v1.0

// Pendiente: Comprarle el café al creador:
// https://github.com/Gruppio/Throttle

#include <Arduino.h>
#include <Throttle.h>

const int BOTON_PIN_ENTRADA = 23;
const int BOTON_PIN_SALIDA = 22;

const int RELAY_ENTRADA = 16;
const int RELAY_SALIDA = 27;

const int ESPERA_MS_ENTRADA_DESPUES = 1250;
const int ESPERA_MS_SALIDA_DESPUES = 1250;

// int ledState = LOW;

Throttle botonEntrada = Throttle(BOTON_PIN_ENTRADA, INPUT_PULLUP);
Throttle botonSalida = Throttle(BOTON_PIN_SALIDA, INPUT_PULLUP);

void setup() {
  Serial.begin(115200);
  Serial.println("Iniciando...");
  
  pinMode(RELAY_ENTRADA, OUTPUT);
  pinMode(RELAY_SALIDA, OUTPUT);
  // digitalWrite(RELAY_ENTRADA, HIGH);
  
  // digitalWrite(RELAY_ENTRADA, ledState);
}

void detectarEntrada() {
  // Serial.println(botonEntrada.fell());
  botonEntrada.update();
  if (botonEntrada.fell()) {
     Serial.println("Se marcó la entrada!");
     // Serial.println(ledState);
     activarRelayEntrada();
     delay(ESPERA_MS_ENTRADA_DESPUES);
   }
}

void detectarSalida() {
  // Serial.println(botonSalida.fell());
  botonSalida.update();
  if (botonSalida.fell()) {
     Serial.println("Se marcó la salida!");
     // Serial.println(ledState);
     activarRelaySalida();
     delay(ESPERA_MS_SALIDA_DESPUES);
   }
}

void activarRelayEntrada() {
  // ledState = !ledState;
  digitalWrite(RELAY_ENTRADA, HIGH);
  delay(500);
  // ledState = !ledState;
  digitalWrite(RELAY_ENTRADA, LOW);
}

void activarRelaySalida() {
  // ledState = !ledStat e;
  digitalWrite(RELAY_SALIDA, HIGH);
  delay(500);
  //ledState = !ledState;
  digitalWrite(RELAY_SALIDA, LOW);
}

void loop() {
   detectarEntrada();
   detectarSalida();
}
