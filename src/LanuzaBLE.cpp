#include "LanuzaBLE.h"
#include <Arduino.h> 

LanuzaBLE::LanuzaBLE() {
  onConnectCallback = nullptr;
  onDisconnectCallback = nullptr;
  onWriteCallback = nullptr;
}

void LanuzaBLE::begin(const char* deviceName, const char* serviceUUID, const char* characteristicUUID) {
  BLEDevice::init(deviceName);
  pServer = BLEDevice::createServer();
  
  // Configurate BLE service and characteristic
  pService = pServer->createService(serviceUUID);
  pCharacteristic = pService->createCharacteristic(
    characteristicUUID,
    BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_NOTIFY
  );
  
  pCharacteristic->addDescriptor(new BLE2902());

  // Configurate callbacks
  pServer->setCallbacks(new MyServerCallbacks(this));
  pCharacteristic->setCallbacks(new MyCharacteristicCallbacks(this));
  
  pService->start();
}

String LanuzaBLE::getMACAddress() {
  // Get ESP32 MAC address
  return BLEDevice::getAddress().toString().c_str();  // Returns MAC address as a string
}

void LanuzaBLE::onConnect(void (*callback)()) {
  onConnectCallback = callback;
}

void LanuzaBLE::onDisconnect(void (*callback)()) {
  onDisconnectCallback = callback;
}

void LanuzaBLE::onWrite(void (*callback)(String)) {
  onWriteCallback = callback;
}

void LanuzaBLE::setCharacteristicValue(String value) {
  pCharacteristic->setValue(value.c_str());
}

void LanuzaBLE::startAdvertising() {
  BLEAdvertising* pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->start();
}

void LanuzaBLE::stopAdvertising() {
  BLEDevice::getAdvertising()->stop();
}

void LanuzaBLE::sendData(String value) {
  if (pCharacteristic && pServer->getConnectedCount() > 0) {  
    pCharacteristic->setValue(value.c_str());  
    pCharacteristic->notify();  
    Serial.print("Enviando por BLE: ");
    Serial.println(value);
  } else {
    Serial.println("There is no one connected, no data is being sent.");
  }
}

// Define callback behaviour
LanuzaBLE::MyServerCallbacks::MyServerCallbacks(LanuzaBLE *lanuzaBLE) {
  lanuzaBLEInstance = lanuzaBLE;
}

void LanuzaBLE::MyServerCallbacks::onConnect(BLEServer* pServer) {
  if (lanuzaBLEInstance->onConnectCallback) lanuzaBLEInstance->onConnectCallback();
}

void LanuzaBLE::MyServerCallbacks::onDisconnect(BLEServer* pServer) {
  if (lanuzaBLEInstance->onDisconnectCallback) lanuzaBLEInstance->onDisconnectCallback();
}

LanuzaBLE::MyCharacteristicCallbacks::MyCharacteristicCallbacks(LanuzaBLE *lanuzaBLE) {
  lanuzaBLEInstance = lanuzaBLE;
}

void LanuzaBLE::MyCharacteristicCallbacks::onWrite(BLECharacteristic* pCharacteristic) {
  if (lanuzaBLEInstance->onWriteCallback) lanuzaBLEInstance->onWriteCallback(pCharacteristic->getValue().c_str());
}
