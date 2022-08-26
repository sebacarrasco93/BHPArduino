// Wiegand
const int RELAY_ENTRADA = 22;
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

  // attachInterrupt(RELAY_ENTRADA, buscarSiHayEntrada, FALLING);
  // attachInterrupt(RELAY_ENTRADA, buscarSiHayEntrada, RISING);
  attachInterrupt(digitalPinToInterrupt(RELAY_ENTRADA), buscarSiHayEntrada, CHANGE);
  attachInterrupt(digitalPinToInterrupt(RELAY_SALIDA), buscarSiHaySalida, CHANGE);
}

// void contadorDeTiempo() {
//   static unsigned long ultimaVezPresionado = 0;
//   unsigned long horaInterruptor = millis();
// }

void buscarSiHayEntrada() {
  static unsigned long ultimaVezPresionadoEntrada = 0;
  unsigned long horaInterruptorEntrada = millis();

  estadoRelayEntrada = digitalRead(RELAY_ENTRADA);
  // Serial.println(estadoRelayEntrada);
  if (estadoRelayEntrada == HIGH) {
    if (horaInterruptorEntrada - ultimaVezPresionadoEntrada > DELAY_ESPERA_ENTRADA) {
      cuentaEntradas++;
      Serial.println(millis());
      Serial.println("Se pulsó el relay de entrada! Activando botón de entrada... ");
      Serial.print(cuentaEntradas);
      Serial.println();
      digitalWrite(BOTON_ENTRADA, HIGH);
      delay(10);
      digitalWrite(BOTON_ENTRADA, LOW);
      Serial.println("Se soltó el botón de entrada");
      delay(DELAY_ESPERA_ENTRADA);

      ultimaVezPresionadoEntrada = horaInterruptorEntrada;
    }
  }
}

void buscarSiHaySalida() {
  static unsigned long ultimaVezPresionadoSalida = 0;
  unsigned long horaInterruptorSalida = millis();

  estadoRelaySalida = digitalRead(RELAY_SALIDA);
  // Serial.println(estadoRelayEntrada);
  if (estadoRelayEntrada == HIGH) {
    if (horaInterruptorSalida - ultimaVezPresionadoSalida > DELAY_ESPERA_SALIDA) {
      cuentaSalidas++;
      Serial.println(millis());
      Serial.println("Se pulsó el relay de salida! Activando botón de salida... ");
      Serial.print(cuentaSalidas);
      Serial.println();
      digitalWrite(BOTON_SALIDA, HIGH);
      delay(10);
      digitalWrite(BOTON_SALIDA, LOW);
      Serial.println("Se soltó el botón de salida");
      delay(DELAY_ESPERA_SALIDA);

      ultimaVezPresionadoSalida = horaInterruptorSalida;
    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  // Serial.println("Estoy en el loop");
  // buscarSiHayEntrada();
  // buscarSiHaySalida();
}
