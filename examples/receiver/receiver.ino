// Add LanuzaBLE library
#include <LanuzaBLE.h>

// Define initialization data
#define DEVICE_NAME "ESP32_BLE"
#define SERVICE_UUID "12345678-1234-1234-1234-123456789012"
#define CHARACTERISTIC_UUID "87654321-4321-4321-4321-098765432109"

// Create an object in the LanuzaBLE class
LanuzaBLE myBLE;

// Define what to do in each callback
void onConnect() {
  Serial.println("A device connected to yours!");
}

void onDisconnect() {
  Serial.println("A device disconnected from yours...");
}

void onWrite(String value) {
  Serial.print("Received data: ");
  Serial.println(value);
}

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  delay(1000);
    
  // Initialize BLE device using the device name and the service and characteristic UUIDs
  myBLE.begin(DEVICE_NAME, SERVICE_UUID, CHARACTERISTIC_UUID);

  // Show ESP32 MAC address
  String macAddress = myBLE.getMACAddress();
  Serial.print("ESP32 MAC address: ");
  Serial.println(macAddress);

  // Register callbacks
  myBLE.onConnect(onConnect);
  myBLE.onDisconnect(onDisconnect);
  myBLE.onWrite(onWrite);

  // Initialize BLE advertising (start communicating)
  myBLE.startAdvertising();
  Serial.println("Waiting for BLE connections...");
}

void loop() {
  // The library manages everything with callbacks, no loop is needed
}
