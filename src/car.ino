#include <SoftwareSerial.h>
#include <L298NX2.h>

const int RX_PIN = 7;
const int TX_PIN = 8;

const int EN_A = 9;
const int IN1_A = 3;
const int IN2_A = 4;

const int EN_B = 10;
const int IN1_B = 5;
const int IN2_B = 6;

const int COMMAND_EXECUTION_INTERVAL = 150;


SoftwareSerial commandReceiver(RX_PIN, TX_PIN);

// Initialize both motors
L298NX2 motors(EN_A, IN1_A, IN2_A, EN_B, IN1_B, IN2_B);

unsigned long lastCommandTimestamp = 0;

void setup() {
  Serial.begin(9600);
  commandReceiver.begin(9600);
}

struct commandStruct {
  bool isValid;
  bool leftForward;
  byte leftSpeed;
  bool rightForward;
  byte rightSpeed;
};

struct commandStruct receiveNextCommand() {
    struct commandStruct command;

    command.isValid = true;

    {
      
      if (commandReceiver.read() != '[') {
        command.isValid = false;
      }

      
      if (command.isValid) {
        byte nextByte = commandReceiver.read();
        if (nextByte == '+') {
          command.leftForward = true;
        } else if (nextByte == '-') {
          command.leftForward = false;
        } else {
          command.isValid = false;
        }
      }

      if (command.isValid) {
        command.leftSpeed = commandReceiver.read();
      }

      if (command.isValid) {
        if (commandReceiver.read() != ',') {
          command.isValid = false;
        }
      }
      
      if (command.isValid) {
        byte nextByte = commandReceiver.read();
        if (nextByte == '+') {
          command.rightForward = true;
        } else if (nextByte == '-') {
          command.rightForward = false;
        } else {
          command.isValid = false;
        }
      }

      if (command.isValid) {
        command.rightSpeed = commandReceiver.read();
      }
      
      if (command.isValid) {
        if (commandReceiver.read() != ']') {
          command.isValid = false;
        }
      }
    } while (!command.isValid)

    return command;
}

void loop() {
    if (commandReceiver.available() >=7 ) {

      struct commandStruct nextCommand = receiveNextCommand();

      if (nextCommand.isValid) {

        lastCommandTimestamp = millis();
         
        motors.setSpeedA(nextCommand.leftSpeed);

        Serial.print(" speedA: ");
        Serial.print(nextCommand.leftSpeed);

        if (nextCommand.leftForward) {
          motors.forwardA();
        } else {
          motors.backwardA();
        }

        motors.setSpeedB(nextCommand.rightSpeed);

        Serial.print(" speedB: ");
        Serial.print(nextCommand.rightSpeed);

        if (nextCommand.rightForward) {
          motors.forwardB();
        } else {
          motors.backwardB();
        }

        Serial.println();
      } else {
        Serial.println("Error: command is not valid!");
      }
    }
  if (millis() - lastCommandTimestamp > COMMAND_EXECUTION_INTERVAL) {
    Serial.println("STOP");
    motors.stop();
  }
}
