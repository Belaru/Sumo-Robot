# 🤖 Sumo Robot

An autonomous sumo-style combat robot built for competition. This robot is designed to detect lines, avoid falling off the ring, and push opponents using real-time sensor data and precise motor control.

---

## ⚙️ System Overview

- 🧠 **Microcontroller:** ATtiny2313A
- 🦾 **Motors:** 4 DC motors (front-left, front-right, back-left, back-right)
- 🧭 **Motor Driver:** MDD10A dual channel driver
- 👁️ **Line Sensors:** 4x TCRT5000 infrared sensors (front & back edge detection)
- 🎯 **Object Sensors:** 4x JS40F analog proximity sensors (360° coverage)
- 🔋 **Power:** Battery-powered with separate logic/motor rails

---

## 🧠 Core Features

- 🔍 **Edge Detection:** Avoids ring edges using TCRT5000 sensors (front and rear)
- 🚨 **Opponent Detection:** JS40F sensors used to scan for enemy robots
- 🧠 **Autonomous Decision Logic:**
  - Advance when enemy is detected ahead
  - Turn toward opponent when detected to the side
  - Reverse when at the front edge
  - Advance when at the back edge
- 🧭 **Precise Movement:** Individual control of 4 motors using DIR and PWM pins

---

## 🗃️ File Structure

```
sumo-robot/
├── MovementManager.c/.h      # Low-level motor control (PWM & DIR)
├── SensorManager.c/.h        # Input handling for line & object sensors
├── Main.c                    # Main control logic and behavior loop
├── config.h                  # Pin definitions and thresholds
├── README.md
└── Makefile
```

---

## 🛠️ How to Build & Flash

1. Compile the code (AVR-GCC):
```bash
make
```

2. Flash to ATtiny2313A using an AVR programmer:
```bash
avrdude -p t2313 -c usbtiny -U flash:w:main.hex
```

> Make sure `Makefile` and `main.c` are configured for your setup.

---

## 🧪 Testing

- Test line sensor logic on white/black backgrounds
- Calibrate JS40F analog thresholds for accurate enemy detection
- Observe motor direction per wheel via test mode or debug flags

---

## 📷 Media

📸 *[Insert image or video link of robot in action]*

---

## 👩‍💻 Author

Anastasia Bondarenko  
Software Engineering @ Concordia University

---

## 📎 License

This project is for educational and competition use only.
