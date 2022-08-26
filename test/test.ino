// Wiegand
const int RELAY_ENTRADA = 18;
const int RELAY_SALIDA = 19;

// Botones a simular, que van a la RPI
const int BOTON_ENTRADA = 16;
const int BOTON_SALIDA = 23;

const DELAY_ESPERA_ENTRADA = 500;
const DELAY_ESPERA_SALIDA = 500;

// Variables
int estadoRelayEntrada = LOW;
int estadoRelaySalida = LOW;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println(".");
  Serial.println("Iniciando");

  pinMode(RELAY_ENTRADA, INPUT_PULLUP);
  pinMode(RELAY_SALIDA, INPUT_PULLUP);
}

void buscarSiHayEntrada() {
  estadoRelayEntrada = digitalRead(RELAY_ENTRADA);
  // Serial.println(estadoRelayEntrada);
  if (estadoRelayEntrada == LOW) {
    Serial.println("Se pulsó el relay de entrada! Activando botón de entrada...");
    digitalWrite(BOTON_ENTRADA, HIGH);
    digitalWrite(BOTON_ENTRADA, LOW);
    Serial.println("Se soltó el botón de entrada");
    delay(MS_ESPERA_ENTRADA);
  }
}

void buscarSiHaySalida() {
  estadoRelaySalida = digitalRead(RELAY_SALIDA);
  // Serial.println(estadoRelaySalida);
  if (estadoRelaySalida == LOW) {
    Serial.println("Se pulsó el relay de salida! Activando botón de salida...");
    digitalWrite(BOTON_SALIDA, HIGH);
    digitalWrite(BOTON_SALIDA, LOW);
    Serial.println("Se soltó el botón de salida");
    delay(MS_ESPERA_ENTRADA);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  // Serial.println("Estoy en el loop");
  buscarSiHayEntrada();
  buscarSiHaySalida();
}
