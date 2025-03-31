# LanuzaBLE

LanuzaBLE is a library for ESP32 designed in order to allow communication between ESP32 boards with Bluetooth Low Energy capabilities and other BLE devices. Please read this tutorial in order to learn how to use it.

## How to install this library

1. Go to https://github.com/makerbylanuza/lanuza-ble/.
2. Click on the green Code button located in the upper right corner.
3. Click on the Download ZIP option.
4. Create a new sketch on Arduino IDE.
5. Go to Sketch > Include library > Add .ZIP library
6. Select the ZIP file you downloaded
7. You now have LanuzaBLE available for use in your Arduino IDE projects!

## How to use this library

To use this library, please first install it using the steps above. Then, open one of the examples include in the library by opening Arduino IDE and going to File > Examples > Custom library examples > LanuzaBLE, or follow these instructions.

### How do I include this library in an Arduino IDE sketch?

Just include the following code at the top of your sketch:
```C++
#include <LanuzaBLE.h>
```
After that, you can use all of the functions explained below.

### How do I initalise the BLE device?

In order to use the library, you must first create an object of the `LanuzaBLE` class. Do this by adding to your sketch the following line before the `void setup()` function:
```C++
LanuzaBLE myBLE;
```

Then, in the `void setup()` function, you will have to initialise the device by using the `begin()` function on it, specifying the device name, the service UUID and the characteristic UUID. These three parameters will define your device, being unique to it. First, you'll have to define them vefore the `void setup()` function, and then use them to initialize the device, such as in the following example. Please note that it is reccommended for the serial port to be started beforehand.
```C++
#include <LanuzaBLE.h>

#define DEVICE_NAME "ESP32_BLE"
#define SERVICE_UUID "12345678-1234-1234-1234-123456789012"
#define CHARACTERISTIC_UUID "87654321-4321-4321-4321-098765432109"

LanuzaBLE myBLE;

void setup() {
  Serial.begin(115200);
  myBLE.begin(DEVICE_NAME, SERVICE_UUID, CHARACTERISTIC_UUID);
}
```
