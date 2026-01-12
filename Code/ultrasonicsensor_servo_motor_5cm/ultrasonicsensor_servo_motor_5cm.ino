#include <Servo.h>


Servo myservo;


const int trigPin = 6;
const int echoPin = 7;


float duration, distance;


// Servo target positions
int servoOpen = 180;
int servoClosed = 0;


void setup() {
  myservo.attach(9);
  myservo.write(servoClosed); // start closed


  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}


void loop() {


  // ----- FAST ultrasonic measurement -----
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);


  duration = pulseIn(echoPin, HIGH, 25000); // timeout prevents long waits
  distance = (duration * 0.0343) / 2;


  Serial.print("Distance: ");
  Serial.println(distance);


  // ----- REACTION WITHOUT BLOCKING -----
  if (distance > 0 && distance <= 5) {
    myservo.write(servoOpen);   // open instantly
  } else {
    myservo.write(servoClosed); // close instantly
  }


  delay(50); // small delay for smoother readings (20 times per second)
}


