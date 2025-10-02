/*
 * BOLT - Line Following Robot with Obstacle Avoidance
 * 
 * This robot can:
 * - Follow lines on the floor using IR sensors
 * - Detect obstacles using an ultrasonic sensor
 * - Navigate around obstacles and return to the line
 * - Demonstrate autonomous movement in real-world environments
 * 
 * Hardware Requirements:
 * - Arduino board (Uno/Nano)
 * - L298N Motor Driver
 * - 2x DC Motors
 * - 2x IR Sensors for line detection
 * - HC-SR04 Ultrasonic Sensor for obstacle detection
 * - Power supply (9V battery)
 */

// Motor Driver Pins (L298N)
#define LEFT_MOTOR_PIN1 5
#define LEFT_MOTOR_PIN2 6
#define RIGHT_MOTOR_PIN1 9
#define RIGHT_MOTOR_PIN2 10

// IR Sensor Pins
#define LEFT_IR_SENSOR A0
#define RIGHT_IR_SENSOR A1

// Ultrasonic Sensor Pins
#define TRIG_PIN 3
#define ECHO_PIN 4

// Motor Speed Settings
#define NORMAL_SPEED 150
#define TURN_SPEED 120
#define SLOW_SPEED 100

// Obstacle Detection Settings
#define OBSTACLE_DISTANCE 15  // Distance in cm to detect obstacle
#define SAFE_DISTANCE 20      // Safe distance to resume line following

// Line Detection Thresholds
#define LINE_THRESHOLD 512    // Analog reading threshold for line detection

// Robot States
enum RobotState {
  LINE_FOLLOWING,
  OBSTACLE_DETECTED,
  AVOIDING_OBSTACLE,
  RETURNING_TO_LINE
};

RobotState currentState = LINE_FOLLOWING;
unsigned long obstacleAvoidStartTime = 0;
unsigned long avoidancePhase = 0;

void setup() {
  // Initialize Serial Communication
  Serial.begin(9600);
  Serial.println("BOLT - Line Following Robot Initialized");
  
  // Initialize Motor Pins
  pinMode(LEFT_MOTOR_PIN1, OUTPUT);
  pinMode(LEFT_MOTOR_PIN2, OUTPUT);
  pinMode(RIGHT_MOTOR_PIN1, OUTPUT);
  pinMode(RIGHT_MOTOR_PIN2, OUTPUT);
  
  // Initialize IR Sensor Pins
  pinMode(LEFT_IR_SENSOR, INPUT);
  pinMode(RIGHT_IR_SENSOR, INPUT);
  
  // Initialize Ultrasonic Sensor Pins
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  // Stop motors initially
  stopMotors();
  
  // Calibration delay
  delay(2000);
  Serial.println("Starting in 2 seconds...");
  delay(2000);
}

void loop() {
  // Read sensors
  int leftIR = analogRead(LEFT_IR_SENSOR);
  int rightIR = analogRead(RIGHT_IR_SENSOR);
  long distance = getDistance();
  
  // Debug output
  Serial.print("State: ");
  Serial.print(currentState);
  Serial.print(" | Distance: ");
  Serial.print(distance);
  Serial.print(" cm | L_IR: ");
  Serial.print(leftIR);
  Serial.print(" | R_IR: ");
  Serial.println(rightIR);
  
  // State machine for robot behavior
  switch (currentState) {
    case LINE_FOLLOWING:
      if (distance > 0 && distance < OBSTACLE_DISTANCE) {
        currentState = OBSTACLE_DETECTED;
        Serial.println("Obstacle detected!");
      } else {
        followLine(leftIR, rightIR);
      }
      break;
      
    case OBSTACLE_DETECTED:
      stopMotors();
      delay(500);
      currentState = AVOIDING_OBSTACLE;
      obstacleAvoidStartTime = millis();
      avoidancePhase = 0;
      Serial.println("Starting obstacle avoidance...");
      break;
      
    case AVOIDING_OBSTACLE:
      avoidObstacle();
      break;
      
    case RETURNING_TO_LINE:
      if (isOnLine(leftIR, rightIR)) {
        currentState = LINE_FOLLOWING;
        Serial.println("Line found! Resuming line following.");
      } else {
        searchForLine();
      }
      break;
  }
  
  delay(50);  // Small delay for stability
}

// Function to follow the line
void followLine(int leftIR, int rightIR) {
  bool leftOnLine = (leftIR > LINE_THRESHOLD);
  bool rightOnLine = (rightIR > LINE_THRESHOLD);
  
  if (leftOnLine && rightOnLine) {
    // Both sensors on line - move forward
    moveForward(NORMAL_SPEED);
  } else if (leftOnLine && !rightOnLine) {
    // Left sensor on line - turn left
    turnLeft(TURN_SPEED);
  } else if (!leftOnLine && rightOnLine) {
    // Right sensor on line - turn right
    turnRight(TURN_SPEED);
  } else {
    // Lost line - move forward slowly while searching
    moveForward(SLOW_SPEED);
  }
}

// Function to check if robot is on the line
bool isOnLine(int leftIR, int rightIR) {
  return (leftIR > LINE_THRESHOLD || rightIR > LINE_THRESHOLD);
}

// Obstacle avoidance algorithm
void avoidObstacle() {
  unsigned long elapsedTime = millis() - obstacleAvoidStartTime;
  
  // Multi-phase obstacle avoidance
  if (avoidancePhase == 0) {
    // Phase 0: Turn right to avoid obstacle
    turnRight(TURN_SPEED);
    if (elapsedTime > 800) {
      avoidancePhase = 1;
      obstacleAvoidStartTime = millis();
    }
  } else if (avoidancePhase == 1) {
    // Phase 1: Move forward past obstacle
    moveForward(NORMAL_SPEED);
    long distance = getDistance();
    if (elapsedTime > 1500 || (distance > SAFE_DISTANCE)) {
      avoidancePhase = 2;
      obstacleAvoidStartTime = millis();
    }
  } else if (avoidancePhase == 2) {
    // Phase 2: Turn left to align back
    turnLeft(TURN_SPEED);
    if (elapsedTime > 800) {
      avoidancePhase = 3;
      obstacleAvoidStartTime = millis();
    }
  } else if (avoidancePhase == 3) {
    // Phase 3: Move forward to return to line
    moveForward(NORMAL_SPEED);
    if (elapsedTime > 1000) {
      currentState = RETURNING_TO_LINE;
      Serial.println("Searching for line...");
    }
  }
}

// Function to search for the line
void searchForLine() {
  // Slowly move forward while turning slightly to find the line
  turnLeft(SLOW_SPEED);
}

// Get distance from ultrasonic sensor
long getDistance() {
  // Clear the trigger pin
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  
  // Send 10 microsecond pulse
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  // Read the echo pin
  long duration = pulseIn(ECHO_PIN, HIGH, 30000);  // 30ms timeout
  
  // Calculate distance in cm
  long distance = duration * 0.034 / 2;
  
  // Return 0 if no valid reading
  return (duration == 0) ? 0 : distance;
}

// Motor control functions
void moveForward(int speed) {
  analogWrite(LEFT_MOTOR_PIN1, speed);
  analogWrite(LEFT_MOTOR_PIN2, 0);
  analogWrite(RIGHT_MOTOR_PIN1, speed);
  analogWrite(RIGHT_MOTOR_PIN2, 0);
}

void moveBackward(int speed) {
  analogWrite(LEFT_MOTOR_PIN1, 0);
  analogWrite(LEFT_MOTOR_PIN2, speed);
  analogWrite(RIGHT_MOTOR_PIN1, 0);
  analogWrite(RIGHT_MOTOR_PIN2, speed);
}

void turnLeft(int speed) {
  analogWrite(LEFT_MOTOR_PIN1, 0);
  analogWrite(LEFT_MOTOR_PIN2, speed);
  analogWrite(RIGHT_MOTOR_PIN1, speed);
  analogWrite(RIGHT_MOTOR_PIN2, 0);
}

void turnRight(int speed) {
  analogWrite(LEFT_MOTOR_PIN1, speed);
  analogWrite(LEFT_MOTOR_PIN2, 0);
  analogWrite(RIGHT_MOTOR_PIN1, 0);
  analogWrite(RIGHT_MOTOR_PIN2, speed);
}

void stopMotors() {
  analogWrite(LEFT_MOTOR_PIN1, 0);
  analogWrite(LEFT_MOTOR_PIN2, 0);
  analogWrite(RIGHT_MOTOR_PIN1, 0);
  analogWrite(RIGHT_MOTOR_PIN2, 0);
}
