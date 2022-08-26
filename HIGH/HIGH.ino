// Wiegand
const int RELAY_ENTRADA = 18;
const int RELAY_SALIDA = 19;

// Botones a simular, que van a la RPI
const int BOTON_ENTRADA = 16;
const int BOTON_SALIDA = 23;

const int DELAY_ESPERA_ENTRADA = 2000;
const int DELAY_ESPERA_SALIDA = 2000;

// Variables
int estadoRelayEntrada = HIGH;
int estadoRelaySalida = HIGH;

// Contadores
int cuentaEntradas = 0;
int cuentaSalidas = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println(".");
  Serial.println("Iniciando");

  pinMode(RELAY_ENTRADA, INPUT_PULLDOWN);
  pinMode(RELAY_SALIDA, INPUT_PULLDOWN);
}

void buscarSiHayEntrada() {
  estadoRelayEntrada = digitalRead(RELAY_ENTRADA);
  // Serial.println(estadoRelayEntrada);
  if (estadoRelayEntrada == HIGH) {
    cuentaEntradas = cuentaEntradas + 1;
    Serial.println("Se pulsó el relay de entrada! Activando botón de entrada... ");
    Serial.print(cuentaEntradas);
    Serial.println();
    digitalWrite(BOTON_ENTRADA, HIGH);
    digitalWrite(BOTON_ENTRADA, LOW);
    Serial.println("Se soltó el botón de entrada");
    delay(DELAY_ESPERA_ENTRADA);
  }
}

void buscarSiHaySalida() {
  estadoRelaySalida = digitalRead(RELAY_SALIDA);
  // Serial.println(estadoRelaySalida);
  if (estadoRelaySalida == HIGH) {
    Serial.println("Se pulsó el relay de salida! Activando botón de salida...");
    digitalWrite(BOTON_SALIDA, HIGH);
    digitalWrite(BOTON_SALIDA, LOW);
    Serial.println("Se soltó el botón de salida");
    delay(DELAY_ESPERA_ENTRADA);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  // Serial.println("Estoy en el loop");
  buscarSiHayEntrada();
  buscarSiHaySalida();
}
