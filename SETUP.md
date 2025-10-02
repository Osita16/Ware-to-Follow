# BOLT Robot - Setup and Calibration Guide

## Quick Start Guide

Follow these steps to get your BOLT robot up and running:

1. [Hardware Assembly](#hardware-assembly)
2. [Software Installation](#software-installation)
3. [Sensor Calibration](#sensor-calibration)
4. [Testing](#testing)
5. [Track Preparation](#track-preparation)
6. [First Run](#first-run)

---

## Hardware Assembly

### Step 1: Chassis Preparation
1. Lay out all components on your workspace
2. Identify mounting locations on chassis for:
   - Arduino board (center)
   - Motor driver (near motors)
   - Battery holder (rear or bottom)
   - Sensors (front)

### Step 2: Motor Installation
1. Mount DC motors on chassis sides
2. Attach wheels to motor shafts
3. Secure with screws or hot glue
4. Install caster wheel at front or rear
5. Test wheels spin freely

### Step 3: Electronics Mounting
1. **Arduino**: Mount in center using screws or standoffs
2. **L298N**: Mount near motors using screws
3. **Battery**: Secure battery holder with velcro or holder
4. **Sensors**: 
   - IR sensors at front-bottom facing down
   - Ultrasonic at front facing forward

### Step 4: Wiring
Follow the connections in [CIRCUIT.md](CIRCUIT.md):
1. Connect motors to L298N
2. Wire L298N control pins to Arduino
3. Connect sensors to Arduino
4. Establish common ground
5. Connect battery to L298N
6. Double-check all connections

### Step 5: Cable Management
1. Bundle wires with zip ties
2. Secure to chassis to prevent tangling
3. Ensure no wires near moving parts
4. Label connections for easy troubleshooting

---

## Software Installation

### Prerequisites
- Computer with USB port
- Arduino IDE (version 1.8.x or later)
- USB cable for Arduino

### Installation Steps

#### 1. Install Arduino IDE
- Download from [arduino.cc](https://www.arduino.cc/en/software)
- Install following the platform-specific instructions
- Launch Arduino IDE

#### 2. Get the Code
```bash
git clone https://github.com/Osita16/Ware-to-Follow.git
cd Ware-to-Follow
```

Or download ZIP from GitHub and extract.

#### 3. Open the Sketch
1. Launch Arduino IDE
2. File → Open
3. Navigate to `bolt.ino`
4. Open the file

#### 4. Select Board and Port
1. Tools → Board → Arduino Uno (or your board)
2. Tools → Port → Select your Arduino port
   - Windows: COM3, COM4, etc.
   - Mac: /dev/cu.usbmodem*
   - Linux: /dev/ttyACM0, /dev/ttyUSB0

#### 5. Upload Code
1. Click Upload button (→) or Sketch → Upload
2. Wait for "Done uploading" message
3. Check for any errors

---

## Sensor Calibration

Proper calibration is crucial for optimal performance.

### IR Sensor Calibration

#### What You Need
- White surface (paper or board)
- Black tape or marker (for line)
- Serial Monitor

#### Calibration Procedure

**Step 1: Connect and Monitor**
```
1. Upload the code to Arduino
2. Open Serial Monitor (Tools → Serial Monitor)
3. Set baud rate to 9600
4. Place robot on white surface
```

**Step 2: Read White Surface Values**
```
1. Observe L_IR and R_IR values in Serial Monitor
2. Write down these values (e.g., L_IR: 234, R_IR: 256)
3. These are your "white surface" readings
```

**Step 3: Read Black Line Values**
```
1. Place robot so sensors are over black line
2. Observe L_IR and R_IR values
3. Write down these values (e.g., L_IR: 723, R_IR: 745)
4. These are your "black line" readings
```

**Step 4: Calculate Threshold**
```
Threshold = (White_Value + Black_Value) / 2

Example:
White average: 245
Black average: 734
Threshold = (245 + 734) / 2 = 489.5 ≈ 490
```

**Step 5: Update Code**
```cpp
// In bolt.ino, update this line:
#define LINE_THRESHOLD 490  // Your calculated value
```

**Step 6: Re-upload**
```
1. Upload modified code
2. Test on line to verify detection
3. Adjust if necessary
```

#### Troubleshooting IR Sensors
| Problem | Solution |
|---------|----------|
| Always high readings | Sensors too close to surface |
| Always low readings | Sensors too far from surface |
| No variation | Check sensor power and connections |
| One sensor not working | Verify analog pin connection |

### Ultrasonic Sensor Calibration

#### Testing Distance Measurement

**Step 1: Open Serial Monitor**
```
1. Upload code with DEBUG_MODE enabled
2. Open Serial Monitor at 9600 baud
3. Observe distance readings
```

**Step 2: Verify Accuracy**
```
1. Place obstacle at known distance (e.g., 10cm)
2. Check if reading matches (Distance: 10 cm)
3. Test at various distances: 5cm, 10cm, 15cm, 20cm, 30cm
4. Readings should be accurate ±1cm
```

**Step 3: Adjust Detection Distance**
```cpp
// Modify these values based on your needs:
#define OBSTACLE_DISTANCE 15  // When to stop (cm)
#define SAFE_DISTANCE 20      // When obstacle is clear (cm)
```

**Step 4: Considerations**
- Sensor works best between 2cm and 400cm
- Soft or angled surfaces may give poor readings
- Temperature affects speed of sound slightly
- Small objects may not be detected

#### Troubleshooting Ultrasonic Sensor
| Problem | Solution |
|---------|----------|
| Always 0 cm | Check TRIG/ECHO connections |
| Erratic readings | Ensure stable mounting |
| No detection | Object too small or soft |
| Wrong distance | Verify nothing obstructing sensor |

---

## Motor Speed Calibration

### Default Values
```cpp
#define NORMAL_SPEED 150   // 0-255
#define TURN_SPEED 120     // 0-255
#define SLOW_SPEED 100     // 0-255
```

### Adjustment Procedure

**Step 1: Test Current Speeds**
```
1. Upload code with default values
2. Observe robot behavior
3. Note if robot is too fast/slow
```

**Step 2: Adjust as Needed**

For **NORMAL_SPEED**:
- Too slow: Increase value (try 170)
- Too fast: Decrease value (try 130)
- Target: Steady, controlled movement

For **TURN_SPEED**:
- Can't turn: Increase value (try 140)
- Turns too fast: Decrease value (try 100)
- Target: Smooth, accurate turns

For **SLOW_SPEED**:
- Not moving: Increase value (try 120)
- Too fast for searching: Decrease value (try 80)
- Target: Slow, controlled search

**Step 3: Balance Left and Right**
```
If robot veers to one side:
1. Motors may have different speeds
2. Add differential in code:
   - LEFT_SPEED_ADJUST (multiplier)
   - RIGHT_SPEED_ADJUST (multiplier)
3. Or adjust mechanically (wheel alignment)
```

### Fine-Tuning Tips
- Make small adjustments (±10-20)
- Test after each change
- Consider battery level affects speed
- Lower values = more control, higher = more speed
- Never exceed 255 (maximum PWM value)

---

## Testing

### Pre-Flight Checklist
- [ ] All connections secure
- [ ] Battery charged
- [ ] Motors spin freely
- [ ] Sensors mounted properly
- [ ] Code uploaded successfully
- [ ] Serial Monitor working (for debugging)

### Component Tests

#### Test 1: Motor Test
```
Objective: Verify all motors work correctly

1. Place robot on blocks (wheels off ground)
2. Power on
3. Robot should initialize and attempt to move
4. Verify:
   - Both motors spin
   - Forward direction is correct
   - Turning works properly
   - Motors stop on command
```

#### Test 2: IR Sensor Test
```
Objective: Verify line detection

1. Place robot on white surface
2. Open Serial Monitor
3. Check L_IR and R_IR values (should be low)
4. Move sensors over black line
5. Values should increase significantly
6. Both sensors should respond similarly
```

#### Test 3: Ultrasonic Test
```
Objective: Verify obstacle detection

1. Open Serial Monitor
2. Place hand at various distances
3. Verify distance readings:
   - 5cm, 10cm, 15cm, 20cm
4. Remove hand, reading should be 0 or very high
5. Detection should be consistent
```

#### Test 4: Integrated Test (No Track)
```
Objective: Test complete system without line

1. Place robot on open floor (no line)
2. Power on and observe
3. Should move forward searching for line
4. Place obstacle in front
5. Should stop when obstacle detected
6. Should attempt avoidance maneuver
```

---

## Track Preparation

### Creating Your Test Track

#### Materials Needed
- White surface (poster board, floor tiles, or paper)
- Black electrical tape (2-3cm wide) or black marker
- Measuring tape
- Level surface

#### Track Design

**Simple Track** (Recommended for testing):
```
1. Straight line: 2 meters long
2. Curve: Gentle 90° turn
3. Return straight: 1 meter
4. Width: 2-3cm black line
```

**Intermediate Track**:
```
1. Multiple turns (left and right)
2. Varying curve radii
3. Straight sections between turns
4. Total length: 3-5 meters
```

**Advanced Track**:
```
1. Sharp turns (90° angles)
2. S-curves
3. Tight loops
4. Mixed straight and curved sections
```

#### Track Guidelines
- **Line Width**: 2-3cm (wider than sensor spacing)
- **Surface**: Matte finish (avoid glossy surfaces)
- **Contrast**: High contrast between line and background
- **Smoothness**: Flat, even surface
- **Lighting**: Consistent, avoid direct sunlight on sensors
- **Curves**: Start with gentle curves, progress to sharper

#### Adding Obstacles
```
1. Place obstacles at various points on track
2. Use solid objects (boxes, blocks, cans)
3. Minimum size: 5cm x 5cm x 5cm
4. Distance from line: 5-10cm ahead
5. Start with stationary obstacles
```

---

## First Run

### Launch Procedure

**Step 1: Pre-Run Checks**
```
- [ ] Track is properly laid out
- [ ] Battery is charged and connected
- [ ] All connections are secure
- [ ] Power switch is accessible
- [ ] Serial Monitor open (optional, for monitoring)
```

**Step 2: Robot Placement**
```
1. Place robot centered on black line
2. Both IR sensors should be over or near line
3. Facing forward along track direction
4. No obstacles immediately in front
```

**Step 3: Initialization**
```
1. Power on the robot
2. Wait for initialization (4 seconds)
3. Serial Monitor will show:
   "BOLT - Line Following Robot Initialized"
   "Starting in 2 seconds..."
4. Robot will begin moving automatically
```

**Step 4: Observe Behavior**
```
Expected behavior:
✓ Follows line smoothly
✓ Corrects when deviating
✓ Stops for obstacles
✓ Navigates around obstacles
✓ Returns to line after avoidance
✓ Continues following line
```

**Step 5: Monitor Serial Output**
```
Watch for:
- State changes (0=following, 1=detected, 2=avoiding, 3=returning)
- Distance readings
- IR sensor values
- Any error conditions
```

### What to Expect

#### Normal Operation
- Smooth forward movement on straight sections
- Gentle corrections to stay on line
- Brief pauses at sharp turns
- Confident navigation around obstacles
- Quick return to line tracking

#### Common Issues
| Observation | Likely Cause | Solution |
|-------------|--------------|----------|
| Veers off line | IR sensors need calibration | Recalibrate LINE_THRESHOLD |
| Too fast | Speed too high | Reduce NORMAL_SPEED |
| Jerky movements | Loop delay too short | Increase LOOP_DELAY |
| Doesn't detect obstacles | Ultrasonic issue | Check mounting/connections |
| Can't find line after avoiding | Avoidance timing wrong | Adjust timing parameters |
| One wheel faster | Motor imbalance | Adjust individual motor speeds |

### Emergency Stop
- Disconnect battery
- Or press Arduino reset button
- Or pick up robot (motors will continue spinning but robot won't move)

---

## Advanced Calibration

### Obstacle Avoidance Timing

The avoidance maneuver has multiple phases:

```cpp
// Phase 0: Turn right away from obstacle
AVOID_TURN_TIME = 800ms     // Adjust for sharper/gentler turn

// Phase 1: Move forward past obstacle  
AVOID_FORWARD_TIME = 1500ms  // Adjust for obstacle size

// Phase 2: Turn left toward line
AVOID_TURN_TIME = 800ms      // Should match phase 0

// Phase 3: Move forward to line
LINE_SEARCH_TIME = 1000ms    // Adjust if can't find line
```

**Tuning Tips**:
- Increase turn time for sharper turns
- Increase forward time for larger obstacles
- Adjust based on your track layout
- Test with different obstacle positions

### Environmental Calibration

#### Lighting Conditions
```
- Bright light: May need higher LINE_THRESHOLD
- Dim light: May need lower LINE_THRESHOLD
- Changing light: Use average conditions
- Direct sunlight: Avoid if possible (sensor interference)
```

#### Surface Variations
```
- Glossy surface: May cause reflections, adjust sensor angle
- Textured surface: May need to lower sensors
- Uneven surface: May need suspension/flexible mounting
- Colored surface: Calibrate specifically for that color
```

### Performance Optimization

**Speed vs. Accuracy Trade-off**:
```
Higher speed = Less accurate line following
Lower speed = More accurate but slower completion

Balance based on your needs:
- Competition: Optimize speed with acceptable accuracy
- Demonstration: Optimize smooth, reliable operation
- Learning: Start slow, increase as stability improves
```

---

## Maintenance

### Regular Checks
- [ ] Tighten all screws and connections
- [ ] Check battery charge level
- [ ] Clean sensors (dust can affect readings)
- [ ] Verify wheels spin freely
- [ ] Inspect wires for damage
- [ ] Test on known track configuration

### Battery Care
- Recharge after each session
- Don't over-discharge
- Store at partial charge (50-70%)
- Check for swelling or damage
- Replace when performance degrades

### Sensor Maintenance
- Wipe IR sensors with soft cloth
- Keep ultrasonic sensor clean
- Check sensor alignment
- Verify secure mounting

---

## Next Steps

Once your robot is working reliably:

1. **Optimize**: Fine-tune for speed and accuracy
2. **Challenge**: Create more complex tracks
3. **Expand**: Add more sensors or features
4. **Experiment**: Try different algorithms
5. **Share**: Document your experience and improvements

---

## Support

If you encounter issues:
1. Check this guide's troubleshooting sections
2. Review [CIRCUIT.md](CIRCUIT.md) for wiring
3. Consult README.md for general information
4. Open an issue on GitHub
5. Check Serial Monitor for debug information

Happy Building! 🤖
