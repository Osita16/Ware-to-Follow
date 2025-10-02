/*
 * Configuration File for BOLT Robot
 * 
 * This file contains all pin definitions, speed settings, and
 * calibration parameters. Modify these values to customize
 * your robot's behavior without changing the main code.
 */

#ifndef CONFIG_H
#define CONFIG_H

// ========================================
// MOTOR DRIVER PIN DEFINITIONS (L298N)
// ========================================
#define LEFT_MOTOR_PIN1 5      // Left motor forward
#define LEFT_MOTOR_PIN2 6      // Left motor backward
#define RIGHT_MOTOR_PIN1 9     // Right motor forward
#define RIGHT_MOTOR_PIN2 10    // Right motor backward

// ========================================
// IR SENSOR PIN DEFINITIONS
// ========================================
#define LEFT_IR_SENSOR A0      // Left IR sensor analog input
#define RIGHT_IR_SENSOR A1     // Right IR sensor analog input

// ========================================
// ULTRASONIC SENSOR PIN DEFINITIONS
// ========================================
#define TRIG_PIN 3             // HC-SR04 trigger pin
#define ECHO_PIN 4             // HC-SR04 echo pin

// ========================================
// MOTOR SPEED SETTINGS (0-255)
// ========================================
// Adjust these values based on your motors and desired performance
#define NORMAL_SPEED 150       // Speed for straight line following
#define TURN_SPEED 120         // Speed for turning maneuvers
#define SLOW_SPEED 100         // Speed for careful/searching movement

// ========================================
// OBSTACLE DETECTION SETTINGS
// ========================================
#define OBSTACLE_DISTANCE 15   // Distance in cm to trigger obstacle detection
#define SAFE_DISTANCE 20       // Distance in cm considered safe after avoidance

// ========================================
// LINE DETECTION SETTINGS
// ========================================
// IR sensor analog reading threshold
// Values above this are considered "on line" (typically dark surface)
// Range: 0-1023, typical value: 512
// Calibrate by testing on your specific surface and line
#define LINE_THRESHOLD 512

// ========================================
// TIMING SETTINGS (milliseconds)
// ========================================
#define AVOID_TURN_TIME 800    // Time to turn during obstacle avoidance
#define AVOID_FORWARD_TIME 1500 // Time to move forward past obstacle
#define LINE_SEARCH_TIME 1000  // Time to search for line after avoidance

// ========================================
// SERIAL COMMUNICATION
// ========================================
#define SERIAL_BAUD_RATE 9600  // Serial communication speed

// ========================================
// CALIBRATION SETTINGS
// ========================================
#define STARTUP_DELAY 2000     // Initial delay before starting (ms)
#define CALIBRATION_DELAY 2000 // Calibration preparation time (ms)
#define LOOP_DELAY 50          // Main loop delay for stability (ms)

// ========================================
// DEBUG SETTINGS
// ========================================
// Set to true to enable verbose serial output
#define DEBUG_MODE true

#endif // CONFIG_H
