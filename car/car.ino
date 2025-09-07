#include <SoftwareSerial.h>
#define IN1 2
#define IN2 3
#define IN3 4
#define IN4 5
//#define EN1 6
//#define EN2 5

SoftwareSerial bt(11, 10);  // RX, TX

char data;

void setup() {
  Serial.begin(9600);
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



void loop()

{
  while (bt.available()) {
    {
      data = bt.read();
      Serial.println(data);
    }


    switch (data) {
      case 'F':
        //Serial.println("Forward");
        forward();
        break;


      case 'B':
        //Serial.println("Reverse");
        reverse();
        break;


      case 'L':
        //Serial.println("Left");
        left();
        break;
      case 'R':
        //Serial.println("Right");
        right();
        break;


      case 'S':
        //Serial.println("Stop");
        stoprobot();
        break;
    }
  }
  if (bt.available() < 0) {
    //Serial.println("No Bluetooth Data ");
  }
  delay(100);
}

void forward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delay(20);
}

void reverse() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  delay(20);
}

void left() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  delay(20);
}

void right() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delay(20);
}

void stoprobot() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  delay(20);
}