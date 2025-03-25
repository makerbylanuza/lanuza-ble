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
  
  // Configurar el servicio y la característica BLE
  pService = pServer->createService(serviceUUID);
  pCharacteristic = pService->createCharacteristic(
    characteristicUUID,
    BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_NOTIFY  // Agregar NOTIFY
  );
  
  pCharacteristic->addDescriptor(new BLE2902());

  // Configurar los callbacks
  pServer->setCallbacks(new MyServerCallbacks(this));
  pCharacteristic->setCallbacks(new MyCharacteristicCallbacks(this));
  
  pService->start();
}

String LanuzaBLE::getMACAddress() {
  // Obtener la dirección MAC del dispositivo
  return BLEDevice::getAddress().toString().c_str();  // Devuelve la dirección MAC en formato string
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
    Serial.println("No hay clientes conectados, no se envia dato.");
  }
}

// Definir el comportamiento de los callbacks
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