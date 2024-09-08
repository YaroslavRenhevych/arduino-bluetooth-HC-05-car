#include <SoftwareSerial.h>

const int RX_PIN = 2;
const int TX_PIN = 3;

const int TRANSMITTER_ENABLE_PIN = 4;

const int leftJoystickVrxPin = A0;
const int rightJoystickVrxPin = A1;

const int LEFT_JOYSTICK_CENTER_VALUE = 510;
const int RIGHT_JOYSTICK_CENTER_VALUE = 506;

SoftwareSerial commandTransmitter(RX_PIN, TX_PIN);

void setup() {
  Serial.begin(9600);
  commandTransmitter.begin(9600);

  pinMode(TRANSMITTER_ENABLE_PIN, INPUT);
}

void loop() {

  int leftThrottle = analogRead(leftJoystickVrxPin);
  int rightThrottle = analogRead(rightJoystickVrxPin);

  Serial.print("LeftThrottle: ");
  Serial.print(leftThrottle);

  Serial.print("; RightThrottle: ");
  Serial.print(rightThrottle);

  if (digitalRead(TRANSMITTER_ENABLE_PIN) == HIGH) {
    Serial.print(" Connected. Command: ");

    commandTransmitter.write('[');
    Serial.print("[");

    if (leftThrottle >= LEFT_JOYSTICK_CENTER_VALUE) {
      commandTransmitter.write('+');
      Serial.print("+");
      commandTransmitter.write(map(leftThrottle, LEFT_JOYSTICK_CENTER_VALUE, 1023, 0, 255));
      Serial.print(map(leftThrottle, LEFT_JOYSTICK_CENTER_VALUE, 1023, 0, 255));
    } else {
      commandTransmitter.write('-');
      Serial.print("-");
      commandTransmitter.write(map(leftThrottle, LEFT_JOYSTICK_CENTER_VALUE, 0, 0, 255));
      Serial.print(map(leftThrottle, LEFT_JOYSTICK_CENTER_VALUE, 0, 0, 255));
    }


    commandTransmitter.write(',');
    Serial.print(",");

    if (rightThrottle >= RIGHT_JOYSTICK_CENTER_VALUE) {
      commandTransmitter.write('+');
      Serial.print("+");
      commandTransmitter.write(map(rightThrottle, RIGHT_JOYSTICK_CENTER_VALUE, 1023, 0, 255));
      Serial.print(map(rightThrottle, RIGHT_JOYSTICK_CENTER_VALUE, 1023, 0, 255));
    } else {
      commandTransmitter.write('-');
      Serial.print("-");
      commandTransmitter.write(map(rightThrottle, RIGHT_JOYSTICK_CENTER_VALUE, 0, 0, 255));
      Serial.print(map(rightThrottle, RIGHT_JOYSTICK_CENTER_VALUE, 0, 0, 255));
    }

    commandTransmitter.write(']');
    Serial.print("]");
    commandTransmitter.flush();
    
    delay(50);
  } else {
    Serial.print(" Disconnected. ");
  }

  Serial.println();
}
