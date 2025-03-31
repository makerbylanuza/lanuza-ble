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

### How do I initialise the BLE device?

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

### How do I find out my ESP32's MAC address?

Although using a MAC address is not required to use this library, it can help differentiate between several options when using more than one ESP32. To do this, LanuzaBLE incorporates a function, `getMACaddress()`, to get it. An example is shown below:
```C++
#include <LanuzaBLE.h>

LanuzaBLE myBLE;

void setup() {
  Serial.begin(115200);

  Serial.print("ESP32 MAC address: ");
  Serial.println(myBLE.getMACAddress());
}
```

### Preparing to send and receive data

In order to use your BLE device to send and receive data, you must first register callbacks. Callbacks are functions that you have to define in your code, but that, after being registered, are run automatically by the LanuzaBLE library. So, first you must create these callbacks by creating functions in your code before the `void setup()` function. A callback can be defined for when a device connects, for when a device disconnects, and for when something is received. Then, they must be registered in the `void setup()` after initialization with the `onConnect()`, `onDisconnect()` and `onWrite()` functions. Finally, one can make the device start communicating by using the `startAdvertising()` function. An example is shown below.
```C++
#include <LanuzaBLE.h>

#define DEVICE_NAME "ESP32_BLE"
#define SERVICE_UUID "12345678-1234-1234-1234-123456789012"
#define CHARACTERISTIC_UUID "87654321-4321-4321-4321-098765432109"

LanuzaBLE myBLE;

void onConnect() {
  Serial.println("A device connected!");
}

void onDisconnect() {
  Serial.println("A device disconnected...");
}

void onWrite(String value) {
  Serial.print("Data received: ");
  Serial.println(value);
}

void setup() {
  Serial.begin(115200);
  myBLE.begin(DEVICE_NAME, SERVICE_UUID, CHARACTERISTIC_UUID);

  myBLE.onConnect(onConnect);
  myBLE.onDisconnect(onDisconnect);
  myBLE.onWrite(onWrite);

  myBLE.startAdvertising();
}
```

Defining and registering all callbacks is not necessary.

### How do I see if a device has connected or disconnected to mine?

To see if a device has connected or disconnected, we must know that when either of these happen, the respective callbacks are run by the library. Therefore, we can define what we want our program to do when these happen,. such as in the example above, where text is printed in the Serial Monitor in these cases.

### How do I send a message?

To send a message, one must use the `sendData()` function provided by the library, which accepts as an argument a variable of `String` type being the data to send. An example is shown below, sending the string `"Hello World!"` every 5 seconds.

```C++
#include <LanuzaBLE.h>

#define DEVICE_NAME "ESP32_BLE"
#define SERVICE_UUID "12345678-1234-1234-1234-123456789012"
#define CHARACTERISTIC_UUID "87654321-4321-4321-4321-098765432109"

const String message = "Hello World!";
const int freq = 5000;

LanuzaBLE myBLE;

void onConnect() {
  Serial.println("A device connected!");
}

void onDisconnect() {
  Serial.println("A device disconnected...");
}

void setup() {
  Serial.begin(115200);
  myBLE.begin(DEVICE_NAME, SERVICE_UUID, CHARACTERISTIC_UUID);

  myBLE.onConnect(onConnect);
  myBLE.onDisconnect(onDisconnect);
  
  myBLE.startAdvertising();
}

void loop() {
  myBLE.sendData(message);
  delay(freq);
}
```

In order to see the text sent, you can use an app such as BLE Scanner (https://play.google.com/store/apps/details?id=com.macdom.ble.blescanner). Please note that the `NOTIFY` property must be enabled in the app in order to read the data. If no one is connected to your device, the message will not be sent.

### How can I see the messages I receive?

Similarly to how you can see if a device connects or disconnects from yours by using the callbacks, you can see if anything is sent to you with the callback registered with the `onWrite()` function. This calback will execute every time you receive data, but it has a special characteristic that must be taken into account when defining it. This callback function must have a `String` type argument, which will correspond to the data received whenever the function is run. Therefore, one can print on the Serial Monitor any data received like in the example in the _Preparing to send and receive data_ section.
