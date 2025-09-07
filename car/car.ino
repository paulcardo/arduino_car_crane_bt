#include <SoftwareSerial.h>
#include <Servo.h>

Servo servo1;
Servo servo2;

// car
#define IN1 2
#define IN2 3
#define IN3 4
#define IN4 5
//crane
#define SM1 7  // Servo 1
#define SML 8  // Servo 2

SoftwareSerial bt(11, 10);  // RX, TX

/***********************  D E B U G  ****************************/
// "true" when is Debug, it must show logs in the Serial Monitor.
// "false" when is production.
/****************************************************************/
bool isDebug = true;

char data;

int eje1 = 90;
int eje2 = 90;
int maxOpen = 45;
int maxDown = 45;

void setup() {
  if (isDebug) {
    Serial.begin(9600);
    Serial.println("Hi Setup");
  }
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  //pinMode(EN1, OUTPUT);
  //pinMode(EN2, OUTPUT);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  //analogWrite(EN1,63);
  //analogWrite(EN2,63);
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
      case 'S':
        stopCar();
        break;
      // servo 1
      case 'D':
        if (eje1 < 90 + maxOpen) {
          eje1++;
          log(String(eje1));
          servo1.write(eje1);
        }
        break;
      case 'I':
        if (eje1 > 90 - maxOpen) {
          eje1--;
          log(String(eje1));
          servo1.write(eje1);
        }
        break;
      // servo 1
      case 'G':
        if (eje2 < 90 + maxDown) {
          eje2++;
          log(String(eje2));
          servo1.write(eje2);
        }
        break;
      case 'H':
        if (eje2 > 90 - maxDown) {
          eje2--;
          log(String(eje2));
          servo1.write(eje2);
        }
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
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delay(20);
}

void reverse() {
  log("reverse");
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  delay(20);
}

void left() {
  log("left");
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  delay(20);
}

void right() {
  log("right");
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delay(20);
}

void stopCar() {
  log("stop");
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  delay(20);
}

// Crane

void resetServos() {
  log("resetServos");
  servo1.write(90);
  servo2.write(90);
  delay(100);
}