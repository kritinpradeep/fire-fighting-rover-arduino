// 🔥 Fire Fighting Rover Code

// Motor Pins
int motorLeft1 = 2;
int motorLeft2 = 3;
int motorRight1 = 4;
int motorRight2 = 5;

// Flame Sensor
int flameSensor = A0;

// Ultrasonic Sensor
int trigPin = 6;
int echoPin = 7;

// Relay (Water Pump)
int pumpRelay = 8;

// Threshold
int flameThreshold = 300;

long duration;
int distance;

void setup() {
  Serial.begin(9600);

  pinMode(motorLeft1, OUTPUT);
  pinMode(motorLeft2, OUTPUT);
  pinMode(motorRight1, OUTPUT);
  pinMode(motorRight2, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(pumpRelay, OUTPUT);

  digitalWrite(pumpRelay, LOW);
}

void loop() {
  int flameValue = analogRead(flameSensor);

  distance = getDistance();

  Serial.print("Flame: ");
  Serial.print(flameValue);
  Serial.print(" Distance: ");
  Serial.println(distance);

  // 🔥 Fire detected
  if (flameValue < flameThreshold) {
    stopMotors();
    activatePump();
  }
  else {
    deactivatePump();

    // 🚧 Obstacle avoidance
    if (distance < 20) {
      stopMotors();
      delay(500);
      turnRight();
      delay(500);
    } else {
      moveForward();
    }
  }

  delay(100);
}

// 🚗 Movement Functions

void moveForward() {
  digitalWrite(motorLeft1, HIGH);
  digitalWrite(motorLeft2, LOW);
  digitalWrite(motorRight1, HIGH);
  digitalWrite(motorRight2, LOW);
}

void stopMotors() {
  digitalWrite(motorLeft1, LOW);
  digitalWrite(motorLeft2, LOW);
  digitalWrite(motorRight1, LOW);
  digitalWrite(motorRight2, LOW);
}

void turnRight() {
  digitalWrite(motorLeft1, HIGH);
  digitalWrite(motorLeft2, LOW);
  digitalWrite(motorRight1, LOW);
  digitalWrite(motorRight2, HIGH);
}

// 🔥 Pump Control

void activatePump() {
  digitalWrite(pumpRelay, HIGH);
}

void deactivatePump() {
  digitalWrite(pumpRelay, LOW);
}

// 📏 Distance Function

int getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  int dist = duration * 0.034 / 2;

  return dist;
}