#define BUTTON_PIN 4
#define MOTOR1_PIN 15
#define MOTOR2_PIN 2
#define MOTOR3_PIN 16
#define MOTOR4_PIN 17
#define TRIG_PIN 5
#define ECHO_PIN 18

bool detectionActive = false;  // Detection starts after the button is pressed
bool buttonPressed = false;    // To track the button press state

void setup() {
  // Initialize serial communication
  Serial.begin(115200);

  // Set the motor pins as OUTPUT
  pinMode(MOTOR1_PIN, OUTPUT);
  pinMode(MOTOR2_PIN, OUTPUT);
  pinMode(MOTOR3_PIN, OUTPUT);
  pinMode(MOTOR4_PIN, OUTPUT);

  // Set the button and ultrasonic pins
  pinMode(BUTTON_PIN, INPUT_PULLUP);  // Button uses pull-up resistor
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Ensure motors are off at the start
  stopMotors();
}

void loop() {
  // Check if the button is pressed
  if (digitalRead(BUTTON_PIN) == LOW && !buttonPressed) {
    delay(50); // Debounce delay
    if (digitalRead(BUTTON_PIN) == HIGH) {
      // Button pressed, perform motor test
      Serial.println("Button pressed. Performing motor test.");
      buttonPressed = true;  // Mark button as pressed

      motorTest();  // Test each motor
      detectionActive = true;  // Start distance detection after test

      Serial.println("Object detection started.");
    }
  }

  // If detection is active, perform object detection
  if (detectionActive) {
    // Measure distance using the ultrasonic sensor
    long duration, distance;

    // Send a 10 microsecond pulse to TRIG_PIN
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    // Read the pulse from ECHO_PIN
    duration = pulseIn(ECHO_PIN, HIGH);

    // Calculate distance in cm
    distance = (duration / 2) / 29.1;

    Serial.print("Distance: ");
    Serial.println(distance);

    // If distance is less than or equal to 150 cm, vibrate all motors
    if (distance <= 150) {
      vibrateAllMotorsLong();
    } else {
      stopMotors();
    }

    delay(500); // Wait for half a second before the next reading
  }
}

void motorTest() {
  // Vibrate each motor one by one for 1 second
  Serial.println("Testing motors...");
  digitalWrite(MOTOR1_PIN, HIGH);
  delay(1000);  // Vibrate for 1 second
  digitalWrite(MOTOR1_PIN, LOW);

  digitalWrite(MOTOR2_PIN, HIGH);
  delay(1000);  // Vibrate for 1 second
  digitalWrite(MOTOR2_PIN, LOW);

  digitalWrite(MOTOR3_PIN, HIGH);
  delay(1000);  // Vibrate for 1 second
  digitalWrite(MOTOR3_PIN, LOW);

  digitalWrite(MOTOR4_PIN, HIGH);
  delay(1000);  // Vibrate for 1 second
  digitalWrite(MOTOR4_PIN, LOW);

  Serial.println("Motor test complete.");
}

void vibrateAllMotorsLong() {
  // Vibrate all motors for 1 second (long duration)
  digitalWrite(MOTOR1_PIN, HIGH);
  digitalWrite(MOTOR2_PIN, HIGH);
  digitalWrite(MOTOR3_PIN, HIGH);
  digitalWrite(MOTOR4_PIN, HIGH);
  delay(1000);  // Vibrate for 1 second
  stopMotors();  // Stop motors after vibration
}

void stopMotors() {
  // Turn off all motors
  digitalWrite(MOTOR1_PIN, LOW);
  digitalWrite(MOTOR2_PIN, LOW);
  digitalWrite(MOTOR3_PIN, LOW);
  digitalWrite(MOTOR4_PIN, LOW);
}
