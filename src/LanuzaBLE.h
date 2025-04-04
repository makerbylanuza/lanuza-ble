#include <Arduino.h> 
#ifndef LANUZABLE_H
#define LANUZABLE_H

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

class LanuzaBLE {
  public:
    LanuzaBLE();
    void begin(const char* deviceName, const char* serviceUUID, const char* characteristicUUID);
    void onConnect(void (*callback)());
    void onDisconnect(void (*callback)());
    void onWrite(void (*callback)(String));
    void setCharacteristicValue(String value);
    String getMACAddress(); 
    void startAdvertising();
    void stopAdvertising();
    void sendData(String value);

  private:
    BLEServer *pServer;
    BLEService *pService;
    BLECharacteristic *pCharacteristic;
    void (*onConnectCallback)();
    void (*onDisconnectCallback)();
    void (*onWriteCallback)(String);

    // Non static callback classes
    class MyServerCallbacks : public BLEServerCallbacks {
      public:
        MyServerCallbacks(LanuzaBLE *lanuzaBLE);
        void onConnect(BLEServer* pServer) override;
        void onDisconnect(BLEServer* pServer) override;

      private:
        LanuzaBLE *lanuzaBLEInstance;
    };

    class MyCharacteristicCallbacks : public BLECharacteristicCallbacks {
      public:
        MyCharacteristicCallbacks(LanuzaBLE *lanuzaBLE);
        void onWrite(BLECharacteristic* pCharacteristic) override;

      private:
        LanuzaBLE *lanuzaBLEInstance;
    };
};

#endif
