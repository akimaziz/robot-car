#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

#define in1 2
#define in2 12
#define in3 13
#define in4 A5
#define enA 3
#define enB 11

int M1_Speed = 80; // speed of motor 1 (adjust as needed)
int M2_Speed = 80; // speed of motor 2 (adjust as needed)
int LeftRotationSpeed = 110;  // Left Rotation Speed (adjust as needed)
int RightRotationSpeed = 110; // Right Rotation Speed (adjust as needed)

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

  if (RIGHT_SENSOR == LOW && LEFT_SENSOR == LOW) {
    forward(); // Move forward
  } else if (RIGHT_SENSOR == LOW && LEFT_SENSOR == HIGH) {
    slightRight(); // Slight right adjustment
  } else if (RIGHT_SENSOR == HIGH && LEFT_SENSOR == LOW) {
    slightLeft(); // Slight left adjustment
  } else if (RIGHT_SENSOR == HIGH && LEFT_SENSOR == HIGH) {
    if (cornerDetected()) {
      stopForCorner(); // Stop before the corner
      delay(1000); // Delay to stabilize the robot
      rotateRight(); // Rotate right at 90-degree corner
      delay(1000); // Delay for the rotation
      startTime = millis(); // Reset the start time for movement after the corner
    } else {
      Stop();  // Stop
    }
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

void slightRight() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);

  analogWrite(enA, LeftRotationSpeed);
  analogWrite(enB, RightRotationSpeed);
}

void slightLeft() {
  digitalWrite(in1, LOW);
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

  analogWrite(enA, 0); // Stop the motors
  analogWrite(enB, 0);
}

bool cornerDetected() {
  // Implement your corner detection logic here
  // Return true if a corner is detected, false otherwise
  // You can use sensor readings or any other technique to detect the corner
}

void stopForCorner() {
  // Implement any necessary actions to stop before the corner
  // For example, you can call the Stop() function to stop the motors
}

void rotateRight() {
  // Implement the rotation logic to turn right at a 90-degree corner
  // Adjust the motor speeds and rotation speeds as needed
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  analogWrite(enA, LeftRotationSpeed);
  analogWrite(enB, RightRotationSpeed);
  // Adjust the delay or use other techniques for rotating at 90-degree
}
