# Ware-to-Follow 🚀

![Rover Robot](https://placehold.co/800x250/77aaff/FFFFFF/png?text=Help+Me+Learn+to+See!)

## Meet Rover, a Little Robot with a Big Problem!

Welcome to the Smart Rover Project! Our friend Rover is a helper bot designed to follow black lines in a warehouse.  

**The Problem:** Rover can follow lines but doesn’t see obstacles. Sometimes it crashes into boxes.  

**Our Goal:** Upgrade Rover’s code so it can see obstacles, stop, and navigate safely.

---

## 📝 To-Do List

Tasks for contributors (details in the [**Issues Tab**](https://github.com/YourUsername/smart-rover-project/issues)):

- Teach Rover to stop when something is in front.
- Help Rover return to the line after avoiding obstacles.
- Add a beeping alert when an obstacle is detected.
- Adjust sensors for better line-following.
- Create a wiring diagram for others to build Rover.

---

## 🛠️ Hardware Requirements

| Component | Quantity | Description |
|-----------|----------|-------------|
| Arduino Uno/Nano | 1 | Microcontroller |
| L298N Motor Driver | 1 | Dual H-Bridge |
| DC Motors | 2 | Geared motors |
| Wheels | 2 | Compatible with DC motors |
| Caster Wheel | 1 | Support wheel |
| IR Sensors | 2 | Line detection |
| HC-SR04 | 1 | Ultrasonic sensor |
| 9V Battery | 1 | Power supply |
| Jumper Wires | - | Connections |
| Chassis | 1 | Robot base |

---

## Circuit Connections

**Motor Driver (L298N):**

- Left Motor: IN1 → Pin 5, IN2 → Pin 6  
- Right Motor: IN3 → Pin 9, IN4 → Pin 10  
- Power: 12V → Battery +, GND → Battery - & Arduino GND  

**Sensors:**

- Left IR Sensor: VCC → 5V, GND → GND, OUT → A0  
- Right IR Sensor: VCC → 5V, GND → GND, OUT → A1  
- Ultrasonic HC-SR04: VCC → 5V, GND → GND, TRIG → Pin 3, ECHO → Pin 4  

---

## Installation & Setup

### 1. Hardware Assembly

1. Mount motors and wheels on chassis.  
2. Attach caster wheel for support.  
3. Mount Arduino board.  
4. Connect motor driver to motors.  
5. Install IR sensors at front bottom.  
6. Mount ultrasonic sensor at the front.  
7. Make all connections as per circuit above.  

### 2. Software Setup

1. Install [Arduino IDE](https://www.arduino.cc/en/software)  
2. Clone the repository:
```bash
git clone https://github.com/Osita16/Ware-to-Follow.git
