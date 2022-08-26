// Relay, que vienen del Wiegand
const int RELAY_ENTRADA = 18;
const int RELAY_SALIDA = 19;

// Botón a simular, que van a la Raspberry Pi
const int BOTON_ENTRADA = 32;
const int BOTON_SALIDA = 33;

// Tiempos de espera
const int MS_ESPERA_ENTRADA = 500;
const int MS_ESPERA_SALIDA = 500;

// Variables
int estadoRelayEntrada = 0;
int estadoRelaySalida = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial1.begin(9600);
  Serial.println("Iniciando solucion...");
  Serial1.println("A 9600...")

  pinMode(RELAY_ENTRADA, OUTPUT);
  pinMode(RELAY_SALIDA, OUTPUT);

  pinMode(BOTON_ENTRADA, INPUT);
  pinMode(BOTON_SALIDA, INPUT);
}

void buscarSiHayEntrada() {
  estadoRelayEntrada = digitalRead(RELAY_ENTRADA);

  if (estadoRelayEntrada == HIGH) {
    Serial.println('Se pulsó el relay de entrada: Activando botón de entrada');
    digitalWrite(BOTON_ENTRADA, HIGH);
    digitalWrite(BOTON_ENTRADA, LOW);
    delay(MS_ESPERA_ENTRADA);
    Serial.println('Se soltó el botón de entrada');
    // digitalWrite(BOTON_ENTRADA, LOW);
  }
}

void buscarSiHaySalida() {
  estadoRelaySalida = digitalRead(RELAY_SALIDA);

  if (estadoRelaySalida == HIGH) {
    Serial.println('Se pulsó el relay de salida: Activando botón de salida');
    digitalWrite(BOTON_SALIDA, HIGH);
    digitalWrite(BOTON_SALIDA, LOW);
    delay(MS_ESPERA_SALIDA);
    Serial.println('Se soltó el botón de salida');
    // digitalWrite(BOTON_SALIDA, LOW);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  buscarSiHayEntrada();
  buscarSiHaySalida();
}
