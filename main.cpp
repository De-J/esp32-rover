#include <TinyGPS++.h>
#include <HardwareSerial.h>
#include <BluetoothSerial.h>

int i = 0; 
TinyGPSPlus gps;
BluetoothSerial SerialBT;      //Bluetooth Serial
HardwareSerial SerialPort(2);  //Serial port for UART communication

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32-BT-SLAVE");
  SerialPort.begin(9600, SERIAL_8N1, 16, 17);
}

void loop() {
  String data = "";
  UserGPS user;  // defined in loop so that previous values get erased with each cycle
  if (SerialBT.available()) {
    while (SerialBT.available()) {
      char c = SerialBT.read();
      data += c;
    }
    data.trim();
    if (i > 5) {
      /* 
      Starting to encode data after a couple of void loops 
      may help in avoiding garbage values on startup. 
      */
      user.encode(data);
    }
    Serial.print("User location:\n");
    Serial.print(user.location.lat(), 6);
    Serial.print(' ');
    Serial.println(user.location.lng(), 6);
    
    if (SerialPort.available()) {

      gps.encode(SerialPort.read());
      Serial.print("Rover location:\n");
      Serial.print(gps.location.lat(), 6);
      Serial.print(' ');
      Serial.println(gps.location.lng(), 6);
     
    }
    
    delay(3000);
    i++;
  }
}