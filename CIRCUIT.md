# BOLT Robot - Circuit Diagram

## Overview
This document provides detailed wiring instructions for the BOLT line-following robot with obstacle avoidance capabilities.

## Component Pin Mappings

### Arduino Uno Pin Usage
| Arduino Pin | Component | Description |
|-------------|-----------|-------------|
| 3 | HC-SR04 TRIG | Ultrasonic sensor trigger |
| 4 | HC-SR04 ECHO | Ultrasonic sensor echo |
| 5 | L298N IN1 | Left motor forward |
| 6 | L298N IN2 | Left motor backward |
| 9 | L298N IN3 | Right motor forward |
| 10 | L298N IN4 | Right motor backward |
| A0 | Left IR OUT | Left IR sensor output |
| A1 | Right IR OUT | Right IR sensor output |
| 5V | Sensors VCC | Power for sensors |
| GND | Common Ground | Ground for all components |

## Detailed Wiring Instructions

### 1. L298N Motor Driver Connections

#### Power Connections
```
L298N → Power Source
├── 12V Terminal → 9V Battery Positive (+)
├── GND → 9V Battery Negative (-)
└── GND → Arduino GND (Common Ground)
```

#### Motor Connections
```
L298N → Motors
├── OUT1 → Left Motor Wire 1
├── OUT2 → Left Motor Wire 2
├── OUT3 → Right Motor Wire 1
└── OUT4 → Right Motor Wire 2
```

#### Control Connections
```
L298N → Arduino
├── IN1 → Digital Pin 5 (Left Motor Forward)
├── IN2 → Digital Pin 6 (Left Motor Backward)
├── IN3 → Digital Pin 9 (Right Motor Forward)
└── IN4 → Digital Pin 10 (Right Motor Backward)
```

**Note**: Remove jumpers on L298N for speed control if present.

### 2. IR Sensor Connections

#### Left IR Sensor
```
Left IR Sensor → Arduino
├── VCC → 5V
├── GND → GND
└── OUT → A0
```

#### Right IR Sensor
```
Right IR Sensor → Arduino
├── VCC → 5V
├── GND → GND
└── OUT → A1
```

**Mounting**: Position sensors 1-2cm above ground, facing downward, spaced to straddle the line.

### 3. HC-SR04 Ultrasonic Sensor

```
HC-SR04 → Arduino
├── VCC → 5V
├── GND → GND
├── TRIG → Digital Pin 3
└── ECHO → Digital Pin 4
```

**Mounting**: Mount at front of robot, facing forward, about 5-10cm above ground.

## Circuit Diagram (Text-Based)

```
                                   BOLT ROBOT WIRING
                                   
                         +-------------------+
                         |   Arduino Uno     |
                         |                   |
    HC-SR04              |  3 TRIG           |
      [VCC]--------------|  5V               |
      [TRIG]-------------|  3                |
      [ECHO]-------------|  4                |
      [GND]--------------|  GND              |
                         |                   |
    Left IR              |                   |
      [VCC]--------------|  5V               |
      [OUT]--------------|  A0               |
      [GND]--------------|  GND              |
                         |                   |
    Right IR             |                   |
      [VCC]--------------|  5V               |
      [OUT]--------------|  A1               |
      [GND]--------------|  GND              |
                         |                   |
                         |  5  --------------|----> L298N IN1
                         |  6  --------------|----> L298N IN2
                         |  9  --------------|----> L298N IN3
                         |  10 --------------|----> L298N IN4
                         |  GND -------------|----> L298N GND
                         +-------------------+
                         
                         +-------------------+
                         |   L298N Driver    |
                         |                   |
    9V Battery           | 12V               |
      [+]----------------|                   |
      [-]----------------|  GND              |
                         |                   |
    Left Motor           | OUT1              |
      [Wire1]------------|                   |
      [Wire2]------------| OUT2              |
                         |                   |
    Right Motor          | OUT3              |
      [Wire1]------------|                   |
      [Wire2]------------| OUT4              |
                         +-------------------+
```

## Power Supply Considerations

### Battery Requirements
- **Voltage**: 9V recommended (can use 7.4V - 12V)
- **Type**: Li-ion rechargeable or 9V alkaline
- **Capacity**: Minimum 500mAh for 30 minutes runtime

### Power Distribution
1. **Motor Power**: 9V battery → L298N → Motors
2. **Arduino Power**: USB (for programming/testing) or external power jack
3. **Sensor Power**: Arduino 5V regulated output

### Important Notes
- **Common Ground**: Ensure all grounds are connected together
- **Separate Power**: Motors powered by battery, Arduino can be powered separately
- **Current Protection**: L298N can handle up to 2A per channel
- **Voltage Drop**: Expect voltage drop under load, may affect motor speed

## Testing Connections

### Continuity Check
Before powering on, verify:
- [ ] No short circuits between VCC and GND
- [ ] All connections are secure
- [ ] Correct polarity for power connections
- [ ] Motor wires properly connected

### Component Testing
Test each component individually:
1. **Motors**: Apply power directly, verify rotation
2. **IR Sensors**: Read analog values in Serial Monitor
3. **Ultrasonic**: Test distance measurement
4. **Motor Driver**: Test with simple forward/backward code

## Troubleshooting

| Issue | Possible Cause | Solution |
|-------|---------------|----------|
| Motors not spinning | No power to L298N | Check battery connection |
| One motor not working | Loose connection | Check motor and L298N connections |
| IR sensors no reading | Wrong pin or no power | Verify VCC, GND, and analog pins |
| Ultrasonic no reading | Incorrect trigger/echo | Verify pin 3 (TRIG) and 4 (ECHO) |
| Erratic behavior | Poor ground connection | Ensure common ground |
| Motors too slow | Low battery | Replace/recharge battery |

## Safety Warnings

⚠️ **Important Safety Information**:
- Never short-circuit the battery
- Disconnect power when making changes
- Use appropriate wire gauge for motor currents
- Ensure proper ventilation if using enclosed battery
- Monitor battery temperature during operation
- Don't reverse polarity of power connections

## Additional Notes

### Sensor Placement
- **IR Sensors**: 
  - Distance from ground: 1-2cm
  - Spacing: Should straddle the line width
  - Angle: Perpendicular to ground
  
- **Ultrasonic Sensor**:
  - Height: 5-10cm from ground
  - Angle: Parallel to ground, facing forward
  - Clear field of view (no obstructions)

### Wire Management
- Use appropriate wire lengths to avoid tangling
- Secure wires to chassis to prevent disconnection
- Label wires for easy troubleshooting
- Use different colors for VCC, GND, and signals

### Mounting Tips
- Secure Arduino firmly to prevent vibration damage
- Mount motor driver away from Arduino to reduce noise
- Use standoffs or foam to isolate components
- Ensure sensors are securely mounted and aligned

## Tools Required
- Soldering iron (for permanent connections)
- Wire strippers
- Screwdriver
- Multimeter (for testing)
- Zip ties or tape (for cable management)

## Upgrade Options
- Add more IR sensors for better line tracking
- Add LED indicators for status
- Add buzzer for audio feedback
- Implement Bluetooth module for remote control
- Add OLED display for status information
