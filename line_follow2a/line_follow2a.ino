// The Smart Rover Project
//
// Meet Rover! A little bot whose job is to follow black lines in a warehouse.
//
// THE PROBLEM: Rover is good at following lines, but it can't see obstacles
// and crashes into them. We need to help fix its code!

// --- Rover's Parts List ---
// Controller
#include <Arduino.h>

// Motor Driver (L298N)
#define MOTOR_A_IN1 2
#define MOTOR_A_IN2 3
#define MOTOR_B_IN3 4
#define MOTOR_B_IN4 5

// Line Following Sensors (IR Sensors)
#define IR_SENSOR_LEFT  A0
#define IR_SENSOR_RIGHT A1

// "Eyes" for Obstacles (Ultrasonic Sensor)
#define ULTRASONIC_TRIG 9
#define ULTRASONIC_ECHO 10

void setup() {
  // Getting Rover ready for work!
  Serial.begin(9600);

  // Set up all the pins for the motors and sensors.
  // [Your pinMode() setup code goes here]

  Serial.println("Rover is ready! Starting line following...");
}

// --- Rover's Abilities ---

/**
 * @brief This is Rover's main skill: following a black line.
 * It uses the IR sensors to know if it's on the path.
 */
void follow_the_line() {
  // The logic for line following goes here.
  // Example:
  // if (the left sensor sees the line) { turn right a little }
  // if (the right sensor sees the line) { turn left a little }
  // else { move forward }
  Serial.println("Following the line...");
  delay(100); // A small delay to simulate movement.
}

/**
 * @brief This is the code to help Rover avoid things.
 * BUT, IT'S NEVER USED in the main loop! This is what we need to fix.
 */
void avoid_obstacle() {
  Serial.println("!!! Obstacle avoidance code is here, but not being used !!!");
  // The logic for avoiding an obstacle would go here:
  // 1. Stop the motors.
  // 2. Back up a little.
  // 3. Turn one way.
  // 4. Move forward to get around the object.
  // 5. Turn back to find the line again.
}

// --- Rover's Main Brain ---

void loop() {
  // ===================== THE BIG PROBLEM IS HERE =====================
  // Rover's brain is currently stuck in a simple loop.
  // It only ever calls the follow_the_line() function.
  // It NEVER checks its ultrasonic "eyes" to see if something is in front of it.
  // This is why it keeps crashing!
  // ===================================================================

  // Right now, Rover only does one thing, over and over again.
  follow_the_line();
}