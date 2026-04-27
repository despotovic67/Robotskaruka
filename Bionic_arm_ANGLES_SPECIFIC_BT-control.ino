
#include <ESP32Servo.h>
#include "BluetoothSerial.h"

BluetoothSerial SerialBT;
Servo pa, kp, sp, dm, mp, zg;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("RoboRuka"); // Bluetooth ime uređaja

  pa.attach(15);
  kp.attach(27);
  sp.attach(25);
  dm.attach(14);
  mp.attach(23);
  zg.attach(22);
}

// Komande:
// 1 = pa otvori   (pa -> 0)
// 2 = kp otvori   (kp -> 60)
// 3 = sp otvori   (sp -> 55)
// 4 = dm otvori   (dm -> 108)
// 5 = mp otvori   (mp -> 103)
// 6 = mp zatvori  (mp -> 0)
// 7 = dm zatvori  (dm -> 0)
// 8 = sp zatvori  (sp -> 180)
// * = kp zatvori  (kp -> 170)
// 0 = pa zatvori  (pa -> 55)
// # = sve otvori
// 9 = sve zatvori

void handleCommand(char cmd) {
  switch (cmd) {
    case '1': pa.write(0);    break;
    case '2': kp.write(60);   break;
    case '3': sp.write(55);   break;
    case '4': dm.write(108);  break;
    case '5': mp.write(103);  break;
    case '6': mp.write(0);    break;
    case '7': dm.write(0);    break;
    case '8': sp.write(180);  break;
    case '*': kp.write(170);  break;
    case '0': pa.write(55);   break;
    case '#':
      pa.write(0); kp.write(60); sp.write(55);
      dm.write(0); mp.write(0);
      break;
    case '9':
      pa.write(55); kp.write(170); sp.write(180);
      dm.write(108); mp.write(103);
      break;
  }
}

void loop() {
  if (SerialBT.available()) {
    char c = (char)SerialBT.read();
    handleCommand(c);
    SerialBT.print("OK:");
    SerialBT.println(c);
  }
  if (Serial.available()) {
    char c = (char)Serial.read();
    handleCommand(c);
  }
}
