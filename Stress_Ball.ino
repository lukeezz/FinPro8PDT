#include <Keyboard.h>

const int fsrPin = A0;
const int switchPin = 10;  // Pin saklar selektor
const int threshold = 1000;

bool isPressed = false;

void setup() {        
  pinMode(switchPin, INPUT);  // Mode input untuk saklar
                                                           
  Serial.begin(300);
  while (!Serial);  // Tunggu hingga serial siap
  Keyboard.begin();
}

void loop() {
  int fsrReading = analogRead(fsrPin);
  int switchState = digitalRead(switchPin);  // Baca status saklar

  Serial.print("FSR: ");
  Serial.print(fsrReading);
  Serial.print(" | Mode: ");
  Serial.println(switchState == HIGH ? "KEYBOARD" : "READ ONLY");

  if (switchState == HIGH) {
    // Mode KEYBOARD
    if (fsrReading > threshold && !isPressed) {
      Keyboard.press(' ');
      isPressed = true;
    } else if (fsrReading <= threshold && isPressed) {
      Keyboard.release(' ');
      isPressed = false;
    }
  } else {
    // Mode READ ONLY
    if (isPressed) {
      Keyboard.release(' ');  // Pastikan tombol dilepas jika mode berubah
      isPressed = false;
    }
  }

  delay(10);
}

