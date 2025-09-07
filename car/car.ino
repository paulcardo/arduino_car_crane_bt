#include <SoftwareSerial.h>
#include <Servo.h>

Servo servoNeck;
Servo servoArm;

// car
#define IN1 2
#define IN2 3
#define IN3 4
#define IN4 5
//crane
#define SM1 7  // Servo neck
#define SML 8  // Servo arm

SoftwareSerial bt(11, 10);  // RX, TX

/***********************  D E B U G  ****************************/
// "true" when is Debug, it must show logs in the Serial Monitor.
// "false" when is production.
/****************************************************************/
bool isDebug = true;

char data;

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
        stoprobot();
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

void stoprobot() {
  log("stop");
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  delay(20);
}