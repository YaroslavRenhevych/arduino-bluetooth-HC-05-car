# arduino-bluetooth-HC-05-car
Car + remote controller based on Arduino microcontrollers and HC-05 bluetooth modules

Communication technology: Bluetooth

Libraries:
https://github.com/Arduino-IRremote
https://github.com/AndreaLombardo/L298N


Components for a remote controller:
- Arduino Nano Every
- Bluetooth module HC-05
- 2 x Joystick
- 3 x kOhm resistor
- jumpers
  
Components for a car:
- Arduino UNO
- Bluetooth module HC-05
- Motor driver L298N
- 3 x kOhm resistor
- 2 x batteries 18650
- 4 x motors
- jumpers
- 4 x wheels
- chassis



How to set up car and controller:
1) connect the car's HC-05 to Serial monitor
2) check HC-05 address using command AT+ADDR?
3) connect the controller's HC-05 to Serial monitor
4) change controller's HC-05 role to master(AT+ROLE=1) and bind to car's HC-05(AT+BIND=[car's HC-05 address])
5) upload the sketch `car.ino` to the car
6) upload the sketch `controller.ino` to the controller
7) power car
8) power controller


RC distance: 3 meters
