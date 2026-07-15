#include <Servo.h>


// Servo angles
#define LEFT 0
#define FORWARD 90
#define RIGHT 180


Servo servo_motor;


// -------------------------
// Motor Pins
// -------------------------
int motorControl = 11;    // PWM Enable (Motor 1)
int motor2Control = 3;    // PWM Enable (Motor 2) -- moved from pin 9 to avoid
                           // conflict with the Servo library's use of Timer1,
                           // which disables PWM on pins 9 and 10 once a
                           // servo is attached.


int motor1pin1 = 12;      // IN1
int motor1pin2 = 13;      // IN2
int motor2pin1 = 7;       // IN3
int motor2pin2 = 8;       // IN4


// -------------------------
// Ultrasonic Sensor Pins
// -------------------------
const int trigPin = 5;
const int echoPin = 6;


float duration;
float distance;


// -------------------------
// Servo sweep state
// -------------------------
int servoAngle = FORWARD;
int servoStep = 2;        // degrees per step -- increase for faster sweep


void setup() {


  // Servo (signal wire on pin 10)
  servo_motor.attach(10);
  servo_motor.write(servoAngle);


  // Ultrasonic Sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);


  Serial.begin(9600);


  // Motor pins
  pinMode(motorControl, OUTPUT);
  pinMode(motor2Control, OUTPUT);


  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);


  // Set motor speed
  analogWrite(motorControl, 120);
  analogWrite(motor2Control, 120);


  // Drive both motors forward -- left running continuously
  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor1pin2, LOW);


  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);
}


void loop() {


  // -------------------------
  // Continuous servo sweep (non-blocking, no long delay())
  // -------------------------
  servoAngle += servoStep;
  if (servoAngle >= RIGHT || servoAngle <= LEFT) {
    servoStep = -servoStep;   // reverse direction at each end
  }
  servo_motor.write(servoAngle);


  // -------------------------
  // Measure Distance for the ultrasonic sensor
  // -------------------------
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);


  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);


  digitalWrite(trigPin, LOW);


  duration = pulseIn(echoPin, HIGH);


  distance = (duration * 0.0343) / 2.0;


  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");


  // Motors are never touched here, so they keep driving forward continuously
  delay(20);   // small delay controls sweep speed -- lower = faster sweep
}

