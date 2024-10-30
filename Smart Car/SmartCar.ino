#include <BluetoothSerial.h>

BluetoothSerial bt;
// Motor A (Right) and Motor B (Left)
int enA = 13, inA1 = 14, inA2 = 12, speedA = 255;
int enB = 25, inB1 = 26, inB2 = 27, speedB = 150;
char mode = 'C'; // 'C' for Car mode, 'A' for Arm mode

void setup() {
  Serial.begin(9600);
  bt.begin("esp32-RC");
  pinMode(enA, OUTPUT);
  pinMode(inA1, OUTPUT);
  pinMode(inA2, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(inB1, OUTPUT);
  pinMode(inB2, OUTPUT);
}

void loop() {
  if (bt.available() > 0) {
    char data = bt.read();
    Serial.println(data);
    
    // Switch modes
    if (data == 'x') {
      mode = 'C'; // Switch to Car mode
      Serial.println("Switched to Car mode");
    } else if (data == 'X') {
      mode = 'A'; // Switch to Arm mode
      Serial.println("Switched to Arm mode");
    }
    
    // Call car() or arm() based on the mode
    if (mode == 'C') {
      car(data);
    } else if (mode == 'A') {
      arm();
    }
  }
}

void car(char data) {
  switch (data) {
    case 'F': // Right
      digitalWrite(inA1, HIGH);
      digitalWrite(inA2, LOW);
      analogWrite(enA, speedA);
      digitalWrite(inB1, LOW);
      digitalWrite(inB2, HIGH);
      analogWrite(enB, speedB);
      break;

    case 'B': // Backward
      digitalWrite(inA1, LOW);
      digitalWrite(inA2, HIGH);
      analogWrite(enA, speedA);
      digitalWrite(inB1, HIGH);
      digitalWrite(inB2, LOW);
      analogWrite(enB, speedB);
      break;

    case 'S': // Stop
      analogWrite(enA, 0);
      analogWrite(enB, 0);
      break;

    case 'R': // Forward
      digitalWrite(inA1, HIGH);
      digitalWrite(inA2, LOW);
      analogWrite(enA, speedA);
      digitalWrite(inB1, HIGH);
      digitalWrite(inB2, LOW);
      analogWrite(enB, speedB);
      break;

    case 'L': // Backward
      digitalWrite(inA1, LOW);
      digitalWrite(inA2, HIGH);
      analogWrite(enA, speedA);
      digitalWrite(inB1, LOW);
      digitalWrite(inB2, HIGH);
      analogWrite(enB, speedB);
      break;

    case 'G': // Forward-Left
      digitalWrite(inA1, LOW);
      digitalWrite(inA2, LOW);
      analogWrite(enA, speedA / 2);
      digitalWrite(inB1, LOW);
      digitalWrite(inB2, HIGH);
      analogWrite(enB, speedB);
      break;

    case 'I': // Forward-Right
      digitalWrite(inA1, HIGH);
      digitalWrite(inA2, LOW);
      analogWrite(enA, speedA);
      digitalWrite(inB1, LOW);
      digitalWrite(inB2, LOW);
      analogWrite(enB, speedB / 2);
      break;

    case 'H': // Backward-Left
      digitalWrite(inA1, LOW);
      digitalWrite(inA2, LOW);
      analogWrite(enA, speedA / 2);
      digitalWrite(inB1, HIGH);
      digitalWrite(inB2, LOW);
      analogWrite(enB, speedB);
      break;

    case 'J': // Backward-Right
      digitalWrite(inA1, LOW);
      digitalWrite(inA2, HIGH);
      analogWrite(enA, speedA);
      digitalWrite(inB1, LOW);
      digitalWrite(inB2, LOW);
      analogWrite(enB, speedB / 2);
      break;

    case '0': speedA = 0; speedB = 0; break;
    case '1': speedA = speedB = 30; break;
    case '2': speedA = speedB = 60; break;
    case '3': speedA = speedB = 90; break;
    case '4': speedA = speedB = 120; break;
    case '5': speedA = speedB = 150; break;
    case '6': speedA = speedB = 180; break;
    case '7': speedA = speedB = 200; break;
    case '8': speedA = speedB = 220; break;
    case '9': speedA = speedB = 240; break;
    case 'q': speedA = speedB = 255; break;

    case 'D':
      speedA = 0;
      speedB = 0;
      analogWrite(enA, 0);
      analogWrite(enB, 0);
      break;

    default:
      break;
  }
}

void arm() {
  Serial.println("ARM ROBOT");
}
