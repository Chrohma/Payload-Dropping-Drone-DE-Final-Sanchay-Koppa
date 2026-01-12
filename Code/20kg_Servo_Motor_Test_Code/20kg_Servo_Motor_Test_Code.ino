#include <ESP32Servo.h>
Servo myservo;
const int trigPin = 10;
const int echoPin = 9;
const int servoPin = 12;
// TODO: Set your limit switch pins here
const int limitSwitch1 = 13;  // Replace with your GPIO pin
const int limitSwitch2 = 14;  // Replace with your GPIO pin
float duration, distance;
// Servo positions
int servoClosed = 45;       // Changed to 45 degrees
int servoOpen = 0;      // Starting position
int currentPosition = 0;
// State machine
enum State {
  WAITING,           // Waiting for object detection
  GRIPPING,          // Slowly moving to 45° (gripping)
  HOLDING            // Holding after grip detected
};
State currentState = WAITING;
void setup() {
  // Timer allocation
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  
  myservo.setPeriodHertz(50);
  myservo.attach(servoPin, 500, 2500);
  myservo.write(servoClosed); // start at 0°
  currentPosition = servoClosed;
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(limitSwitch1, INPUT_PULLUP);  // Use internal pullup
  pinMode(limitSwitch2, INPUT_PULLUP);  // Use internal pullup
  
  Serial.begin(115200);
  delay(1000);
  Serial.println("ESP32-S3 Gripper Control Started");
  Serial.println("Servo at 0° - Ready");
}
void loop() {
  // ----- Read ultrasonic sensor -----
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH, 25000);
  distance = (duration * 0.0343) / 2;
  
  // ----- Read limit switches (both should be LOW/0V when gripping) -----
  bool switch1Pressed = (digitalRead(limitSwitch1) == LOW);
  bool switch2Pressed = (digitalRead(limitSwitch2) == LOW);
  bool bothPressed = switch1Pressed && switch2Pressed;
  
  // ----- State Machine -----
  switch(currentState) {
    
    case WAITING:
      Serial.print("WAITING | Distance: ");
      Serial.print(distance);
      Serial.println(" cm");
      
      if (distance > 0 && distance <= 5) {
        Serial.println(">>> Object detected! Starting grip...");
        currentState = GRIPPING;
      }
      break;
      
    case GRIPPING:
      Serial.print("GRIPPING | Position: ");
      Serial.print(currentPosition);
      Serial.print("° | Switches: ");
      Serial.print(switch1Pressed ? "PRESSED" : "open");
      Serial.print(", ");
      Serial.println(switch2Pressed ? "PRESSED" : "open");
      
      // Check if both limit switches are pressed (0V detected)
      if (bothPressed) {
        Serial.println(">>> GRIP COMPLETE! Holding position at ");
        Serial.print(currentPosition);
        Serial.println("°");
        currentState = HOLDING;
      } else if (currentPosition > servoOpen) {
        // Slowly grip (increase angle by 2 degrees each step)
        currentPosition -= 2;
        myservo.write(currentPosition);
        delay(50);  // Adjust this for gripping speed (higher = slower)
      } else {
        // Reached 45° without detecting grip
        Serial.println(">>> Reached 45° without grip detection - HOLDING");
        currentState = HOLDING;
      }
      break;
      
    case HOLDING:
      Serial.println("HOLDING position");
      // Hold current position indefinitely
      // (Add your release condition here if needed)
      delay(500);
      break;
  }
  
  delay(50);
}
