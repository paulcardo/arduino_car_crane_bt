#include <SoftwareSerial.h>
#include <Servo.h>

Servo servo1;
Servo servo2;

// car
#define LM1 7  // motor Driver in1
#define LM2 5  // motor Driver in2
#define ENA 6  // (PWM pin) motor Driver enA

#define ENB 3  // (PWM pin) motor Driver enB
#define RM1 4  // motor Driver in3
#define RM2 2  // motor Driver in4

//crane
#define SM1 8  // Servo 1
#define SML 13  // Servo 2

SoftwareSerial bt(10, 11);  // RX, TX

/***********************  D E B U G  ****************************/
// "true" when is Debug, it must show logs in the Serial Monitor.
// "false" when is production.
/****************************************************************/
bool isDebug = true;

char data;

int eje1 = 90;
int eje2 = 90;
int maxOpen = 30;
int maxDown = 40;

void setup() {
  if (isDebug) {
    Serial.begin(9600);
    Serial.println("Hi Setup");
  }
  pinMode(LM1, OUTPUT);
  pinMode(LM2, OUTPUT);
  pinMode(RM1, OUTPUT);
  pinMode(RM2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  digitalWrite(LM1, LOW);
  digitalWrite(LM2, LOW);
  digitalWrite(RM1, LOW);
  digitalWrite(RM2, LOW);
   // set motor's speed
  analogWrite(ENA, 75);
  analogWrite(ENB, 75);
  bt.begin(9600);

  servo1.attach(SM1);
  servo2.attach(SML);

  stopCar();
  resetServos();
}


void loop() {
  while (bt.available()) {
    {
      data = bt.read();
      if (isDebug) {
        Serial.println(data);
      }
    }

    switch (data) {
      // car
      case 'F':
        forward();
        break;
      case 'B':
        reverse();
        break;
      case 'L':
        left();
        break;
      case 'R':
        right();
        break;
      case 's':
        stopCar();
        break;
      // servo 1
      case 'A':
        if (eje1 < 90 + maxOpen) {
          eje1++;
          log(String(eje1));
          servo1.write(eje1);
        }
        break;
      case 'D':
        if (eje1 > 90 - maxOpen) {
          eje1--;
          log(String(eje1));
          servo1.write(eje1);
        }
        break;
      // servo 2
      case 'S':
        if (eje2 < 90 + maxDown) {
          eje2++;
          log(String(eje2));
          servo2.write(eje2);
        }
        break;
      case 'W':
        if (eje2 > 90 - maxDown) {
          eje2--;
          log(String(eje2));
          servo2.write(eje2);
        }
        break;
      case 'Y':
       resetServos();
       break;
    }
  }
  if (bt.available() < 0) {
    log("No Bluetooth Data ");
  }
  delay(100);
}

void log(String msg) {
  if (isDebug) {
    Serial.println(msg);
  }
}

// Car

void forward() {
  log("forward");
  digitalWrite(LM1, HIGH);
  digitalWrite(LM2, LOW);
  digitalWrite(RM1, LOW);
  digitalWrite(RM2, HIGH);
  delay(20);
}

void reverse() {
  log("reverse");
  digitalWrite(LM1, LOW);
  digitalWrite(LM2, HIGH);
  digitalWrite(RM1, HIGH);
  digitalWrite(RM2, LOW);
  delay(20);
}

void left() {
  log("left");
  digitalWrite(LM1, HIGH);
  digitalWrite(LM2, LOW);
  digitalWrite(RM1, HIGH);
  digitalWrite(RM2, LOW);
  delay(20);
}

void right() {
  log("right");
  digitalWrite(LM1, LOW);
  digitalWrite(LM2, HIGH);
  digitalWrite(RM1, LOW);
  digitalWrite(RM2, HIGH);
  delay(20);
}

void stopCar() {
  log("stop");
  digitalWrite(LM1, LOW);
  digitalWrite(LM2, LOW);
  digitalWrite(RM1, LOW);
  digitalWrite(RM2, LOW);
  delay(20);
}

// Crane

void resetServos() {
  log("resetServos");
  servo1.write(90);
  servo2.write(90);
  delay(100);
  eje1 = 90;
  eje2 = 90;
  log(String(eje1) + String(eje2));
}