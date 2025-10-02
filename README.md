A simple line-following robot equipped with basic sensors to detect obstacles. It can follow lines on the floor, stop when it encounters an object, navigate around it, and return to the path. This project demonstrates fundamental robotics concepts like sensor-based navigation, obstacle avoidance, and autonomous movement in a real-world environment.

## Features

- **Line Following**: Uses IR sensors to detect and follow black lines on a white surface
- **Obstacle Detection**: Ultrasonic sensor detects obstacles in the robot's path
- **Obstacle Avoidance**: Automatically navigates around obstacles
- **Path Return**: Returns to the original line path after avoiding obstacles
- **Real-time Monitoring**: Serial output for debugging and monitoring robot behavior

## Hardware Requirements

### Components List

| Component | Quantity | Description |
|-----------|----------|-------------|
| Arduino Uno/Nano | 1 | Microcontroller board |
| L298N Motor Driver | 1 | Dual H-Bridge motor driver |
| DC Motors | 2 | Geared DC motors for wheels |
| Wheels | 2 | Robot wheels (compatible with DC motors) |
| Caster Wheel | 1 | Front/rear support wheel |
| IR Sensors | 2 | Line detection sensors |
| HC-SR04 | 1 | Ultrasonic distance sensor |
| 9V Battery | 1 | Power supply for motors |
| Jumper Wires | - | For connections |
| Chassis | 1 | Robot base platform |

## Circuit Connections

### Motor Driver (L298N) Connections
- **Left Motor**:
  - IN1 → Arduino Pin 5
  - IN2 → Arduino Pin 6
- **Right Motor**:
  - IN3 → Arduino Pin 9
  - IN4 → Arduino Pin 10
- **Power**:
  - 12V → 9V Battery (+)
  - GND → Battery (-) and Arduino GND

### Sensor Connections
- **Left IR Sensor**:
  - VCC → Arduino 5V
  - GND → Arduino GND
  - OUT → Arduino A0
- **Right IR Sensor**:
  - VCC → Arduino 5V
  - GND → Arduino GND
  - OUT → Arduino A1
- **Ultrasonic Sensor (HC-SR04)**:
  - VCC → Arduino 5V
  - GND → Arduino GND
  - TRIG → Arduino Pin 3
  - ECHO → Arduino Pin 4

## Installation & Setup

### 1. Hardware Assembly
1. Mount the motors on the chassis
2. Attach wheels to the motors
3. Install the caster wheel for support
4. Mount the Arduino board on the chassis
5. Connect the motor driver to the motors
6. Position IR sensors at the front bottom (facing down)
7. Mount the ultrasonic sensor at the front (facing forward)
8. Make all electrical connections as per the circuit diagram above

### 2. Software Setup
1. Install Arduino IDE from [arduino.cc](https://www.arduino.cc/en/software)
2. Clone this repository:
   ```bash
   git clone https://github.com/Osita16/Ware-to-Follow.git
   ```
3. Open `bolt.ino` in Arduino IDE
4. Select your Arduino board: Tools → Board → Arduino Uno/Nano
5. Select the correct COM port: Tools → Port → [Your Port]
6. Upload the code to your Arduino

### 3. Calibration
1. **IR Sensor Calibration**:
   - Place sensors over white surface and note the reading
   - Place sensors over black line and note the reading
   - Adjust `LINE_THRESHOLD` value in code (typically around 512)
   - Lower values = darker surface, Higher values = lighter surface

2. **Obstacle Detection**:
   - Test ultrasonic sensor at different distances
   - Adjust `OBSTACLE_DISTANCE` (default: 15cm) based on your needs
   - Adjust `SAFE_DISTANCE` (default: 20cm) for safe clearance

3. **Motor Speed Tuning**:
   - Adjust `NORMAL_SPEED`, `TURN_SPEED`, and `SLOW_SPEED` values
   - Test on your track and fine-tune for smooth operation

## Usage

1. **Prepare the Track**:
   - Create a black line track on a white surface using black tape
   - Ensure the line is about 2-3cm wide
   - Make sure the surface is flat and even

2. **Power On**:
   - Connect the 9V battery to the motor driver
   - Connect Arduino to power or computer (for monitoring)
   - The robot will wait 4 seconds before starting

3. **Operation**:
   - Place BOLT on the black line
   - The robot will automatically start following the line
   - When an obstacle is detected, it will stop and navigate around it
   - After avoiding the obstacle, it will search for and return to the line

4. **Monitoring**:
   - Open Serial Monitor in Arduino IDE (Tools → Serial Monitor)
   - Set baud rate to 9600
   - View real-time sensor readings and robot state

## How It Works

### Line Following Algorithm
The robot uses two IR sensors positioned on either side of the line:
- **Both sensors on line**: Move forward
- **Left sensor on line**: Turn left
- **Right sensor on line**: Turn right
- **No sensors on line**: Continue forward slowly while searching

### Obstacle Avoidance Algorithm
When an obstacle is detected (distance < 15cm):
1. **Stop**: Robot halts immediately
2. **Turn Right**: Rotates to avoid obstacle
3. **Move Forward**: Travels past the obstacle
4. **Turn Left**: Realigns toward original path
5. **Search for Line**: Looks for the black line
6. **Resume**: Returns to line following mode

### State Machine
The robot operates using a state machine with four states:
- `LINE_FOLLOWING`: Normal operation, following the line
- `OBSTACLE_DETECTED`: Obstacle found, preparing to avoid
- `AVOIDING_OBSTACLE`: Executing avoidance maneuver
- `RETURNING_TO_LINE`: Searching for and returning to line

## Customization

### Adjusting Parameters
Edit these values in `bolt.ino` to customize behavior:

```cpp
// Motor Speeds (0-255)
#define NORMAL_SPEED 150    // Speed for straight movement
#define TURN_SPEED 120      // Speed for turning
#define SLOW_SPEED 100      // Speed for careful movement

// Distances (in cm)
#define OBSTACLE_DISTANCE 15  // When to detect obstacle
#define SAFE_DISTANCE 20      // When obstacle is clear

// Sensor Threshold (0-1023)
#define LINE_THRESHOLD 512    // Line detection sensitivity
```

### Modifying Avoidance Strategy
The `avoidObstacle()` function contains the avoidance logic. You can modify:
- Timing of each phase (currently 800ms for turns, 1500ms for forward)
- Direction of avoidance (change turnRight to turnLeft)
- Number of phases in the avoidance sequence

## Troubleshooting

| Problem | Solution |
|---------|----------|
| Robot doesn't follow line | Calibrate IR sensors, adjust LINE_THRESHOLD |
| Robot is too fast/slow | Adjust NORMAL_SPEED, TURN_SPEED values |
| Doesn't detect obstacles | Check ultrasonic sensor connections, adjust OBSTACLE_DISTANCE |
| Motors don't move | Check motor driver connections and power supply |
| Erratic behavior | Ensure good power supply, check for loose connections |
| Can't find line after avoidance | Increase timing in avoidance phases, adjust turn angles |

## Serial Monitor Output

When connected to Serial Monitor, you'll see:
```
BOLT - Line Following Robot Initialized
Starting in 2 seconds...
State: 0 | Distance: 45 cm | L_IR: 234 | R_IR: 567
State: 0 | Distance: 12 cm | L_IR: 543 | R_IR: 556
Obstacle detected!
Starting obstacle avoidance...
State: 2 | Distance: 25 cm | L_IR: 123 | R_IR: 145
Searching for line...
Line found! Resuming line following.
```

## Contributing

Contributions are welcome! Feel free to:
- Report bugs
- Suggest new features
- Submit pull requests
- Improve documentation

## License

This project is open source and available for educational purposes.

## Author

Created as a demonstration of fundamental robotics concepts including sensor-based navigation, obstacle avoidance, and autonomous movement.

## Acknowledgments

- Arduino community for excellent documentation
- Robotics enthusiasts for inspiration and support
