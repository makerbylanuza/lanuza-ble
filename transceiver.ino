// Incluimos la biblioteca LanuzaBLE
#include <LanuzaBLE.h>

// Definimos datos para la inicialización
#define DEVICE_NAME "ESP32_BLE"
#define SERVICE_UUID "12345678-1234-1234-1234-123456789012"
#define CHARACTERISTIC_UUID "87654321-4321-4321-4321-098765432109"

// Definimos mensaje y frecuencia de envío
const String message = "Hola desde ESP32";
const int freq = 5000;

// Creamos un objeto de la clase LanuzaBLE
LanuzaBLE myBLE;

// Definimos qué hacer en los callbacks
void onConnect() {
  Serial.println("Dispositivo conectado");
}

void onDisconnect() {
  Serial.println("Dispositivo desconectado");
}

void onWrite(String value) {
  Serial.print("Dato recibido: ");
  Serial.println(value);
}

void setup() {
  Serial.begin(115200);
    
  // Iniciar BLE con nombre del dispositivo, UUID del servicio y característica
  myBLE.begin(DEVICE_NAME, SERVICE_UUID, CHARACTERISTIC_UUID);

  // Mostrar la dirección MAC del dispositivo
  String macAddress = myBLE.getMACAddress();
  Serial.print("Dirección MAC del ESP32: ");
  Serial.println(macAddress);

  // Definir callbacks
  myBLE.onConnect(onConnect);
  myBLE.onDisconnect(onDisconnect);
  myBLE.onWrite(onWrite);

  // Iniciar publicidad BLE
  myBLE.startAdvertising();
  Serial.println("Esperando conexiones BLE...");
}

void loop() {
  // Enviamos el mensaje y esperamos
  myBLE.sendData(message);
  delay(freq);
}
