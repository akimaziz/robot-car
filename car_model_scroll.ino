#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

#define in1 2
#define in2 12
#define in3 13
#define in4 A5
#define enA 3
#define enB 11

int M1_Speed = 80; // speed of motor 1
int M2_Speed = 80; // speed of motor 2
int LeftRotationSpeed = 250;  // Left Rotation Speed
int RightRotationSpeed = 250; // Right Rotation Speed

unsigned long startTime; // Start time of the movement
unsigned long elapsedTime; // Elapsed time since the movement started

void setup() {
  lcd.begin(16, 2);

  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);

  pinMode(A2, INPUT); // initialize Left sensor as an input
  pinMode(A1, INPUT); // initialize Right sensor as an input

  startTime = millis(); // Initialize the start time
}

void loop() {
  int LEFT_SENSOR = digitalRead(A2);
  int RIGHT_SENSOR = digitalRead(A1);

  if (RIGHT_SENSOR == 0 && LEFT_SENSOR == 0) {
    forward(); // FORWARD
  } else if (RIGHT_SENSOR == 0 && LEFT_SENSOR == 1) {
    right(); // Move Right
  } else if (RIGHT_SENSOR == 1 && LEFT_SENSOR == 0) {
    left(); // Move Left
  } else if (RIGHT_SENSOR == 1 && LEFT_SENSOR == 1) {
    Stop();  // STOP
  }

  // Calculate the elapsed time
  elapsedTime = millis() - startTime;

  // Print the time elapsed and speed values on the LCD keypad shield
  lcd.setCursor(0, 0);
  lcd.print("Elapsed: ");
  lcd.print(elapsedTime / 1000); // Convert milliseconds to seconds
  lcd.print("s");

  lcd.setCursor(0, 1);
  lcd.print(" R=");
  lcd.print(RightRotationSpeed);
  lcd.print(", L=");
  lcd.print(LeftRotationSpeed);

  delay(100);
}

void forward() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  analogWrite(enA, M1_Speed);
  analogWrite(enB, M2_Speed);
}

void backward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  analogWrite(enA, M1_Speed);
  analogWrite(enB, M2_Speed);
}

void right() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  analogWrite(enA, LeftRotationSpeed);
  analogWrite(enB, RightRotationSpeed);
}

void left() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  analogWrite(enA, LeftRotationSpeed);
  analogWrite(enB, RightRotationSpeed);
}

void Stop() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
