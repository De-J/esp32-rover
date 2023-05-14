#include "BluetoothSerial.h"

// Motor A
int ENA = 14,
    IN1 = 27,
    IN2 = 26;

// Motor B
int ENB = 25,
    IN3 = 33,
    IN4 = 32;

// Setting PWM properties
// If the motor makes a high-pitched buzzing noise then try adjusting the FREQUENCY.
const int FREQUENCY = 150,
          RESOLUTION = 8,
          PWM_CHANNEL_A = 0,
          PWM_CHANNEL_B = 1,
          DUTY_CYCLE = 150;

BluetoothSerial SerialBT;
// HardwareSerial SerialPort(2);

void setup() {
  // sets the pins as outputs:
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // configure LED PWM functionalitites
  ledcSetup(PWM_CHANNEL_A, FREQUENCY, RESOLUTION);
  ledcSetup(PWM_CHANNEL_B, FREQUENCY, RESOLUTION);

  // attach the channel to the GPIO to be controlled
  ledcAttachPin(ENA, PWM_CHANNEL_A);
  ledcAttachPin(ENB, PWM_CHANNEL_B);

  ledcWrite(PWM_CHANNEL_A, DUTY_CYCLE);
  ledcWrite(PWM_CHANNEL_B, DUTY_CYCLE);


  Serial.begin(115200);
  SerialBT.begin("ESP32-BT-SLAVE");  // beginning bluetooth service
  // SerialPort.begin(9600, SERIAL_8N1, 16, 17); // streaming GPS data at SerialPort
}

void loop() {
  while (SerialBT.available()) {
    int x = SerialBT.read();
    Serial.println(x);
    if (x > 48 && x < 58) {
      char c = char(x);
      switch (c) {
        case '1':
          Forward();
          break;
        case '2':
          Right();
          break;
        case '3':
          Left();
          break;
        case '4':
          Reverse();
          break;
      }
      delay(2000);
      Halt();
    }
  }
}

void moveInCircle() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void Forward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);  
  digitalWrite(IN4, LOW);
}

void Reverse() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void Right() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void Left() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void Halt() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}