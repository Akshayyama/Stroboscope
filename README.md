# Stroboscope Using Arduino Nano 33 BLE Sense

## Overview

This project is a non-contact rotational speed measurement system using a stroboscope built around the **Arduino Nano 33 BLE Sense**. The system flashes a 9W LED at a controllable frequency. When the flash frequency matches the rotational speed (RPM) of an object, the object appears stationary — allowing accurate RPM estimation.

Multiple control methods are implemented:
- Manual frequency control using a potentiometer
- Gesture-based control using the built-in IMU (accelerometer + gyroscope)
- Bluetooth communication with a smartphone for monitoring and control

---

## Working Principle

The stroboscope works on the principle of **temporal aliasing**. When the LED flash frequency matches the rotational frequency of the object, it appears still to the eye.

- The **Arduino Nano 33 BLE Sense** generates PWM pulses to switch a **MOSFET**, which in turn drives a **9W LED**.
- The **MOSFET's gate** requires ~4V, but the 3.7V LiPo battery isn't sufficient, so an **op-amp amplifier** boosts the control signal.
- Flash frequency is adjusted using:
  - A **potentiometer** for coarse manual control
  - The **IMU (accelerometer + gyroscope)** to detect tilts and apply fine adjustments
  - **Bluetooth** to stream frequency/orientation data to a smartphone

---

## Components Used

| Component                     | Quantity | Description / Notes                           |
|------------------------------|----------|-----------------------------------------------|
| Arduino Nano 33 BLE Sense    | 1        | Microcontroller with onboard IMU and BLE      |
| High-Power White LED (9W)    | 1        | Flashing light source                         |
| N-channel MOSFET IRFZ44N     | 1        | For high-speed LED switching                  |
| LiPo Battery (3.7V)          | 1        | Main power supply                             |
| Op-Amp IC (LM741)            | 1        | Signal amplifier for MOSFET gate drive        |
| Potentiometer (10kΩ)         | 1        | Manual flash frequency adjustment             |
| Resistors                    | 1k,10k   | Biasing & filtering components for op-amp     |
| Breadboard                   | 1        | For prototyping circuit connections           |
| Smartphone                   | 1        | For Bluetooth monitoring                      |

---

## Code Overview

The Arduino code performs the following functions:

- **PWM Signal Generation**: Flashes the 9W LED using a digital output pin.
- **Manual Control**: Reads analog input from the potentiometer to determine base frequency.
- **Gesture Control**: Reads and filters IMU data to allow tilt-based adjustments to flash frequency.
- **Bluetooth Communication**: Sends live frequency and orientation data to a connected smartphone via BLE for monitoring and potential logging.
- **Sensor Fusion**: Combines accelerometer and gyroscope data for smoother gesture control.

---

## Objectives

- Create a non-contact RPM measurement tool
- Implement both hardware (potentiometer) and motion-based (IMU) input
- Use analog signal amplification for power control (op-amp + MOSFET)
- Add Bluetooth monitoring for wireless interfacing

---

## Outcomes

- Real-time RPM measurement using stroboscopic illusion
- Tilt-controlled frequency adjustment for ease of use
- Successfully integrated BLE for smartphone monitoring
- Built a fully self-contained and portable stroboscope system

---

## Usage Instructions

1. Power the system with a **3.7V LiPo battery**.
2. Upload the Arduino sketch using the **Arduino IDE**.
3. Adjust the **potentiometer** for initial flash frequency.
4. Use **tilt gestures** (forward/backward/sideways) to fine-tune frequency.
5. Connect your smartphone via **Bluetooth** to receive live frequency and angle data.
6. Point the LED at a rotating object.
7. Tune the flash frequency until the object appears stationary — the frequency now equals the RPM.

---

## Project Images / Demo

https://drive.google.com/drive/folders/1HfXdL7126vNmSyxEhwISp3AX0GDpDEKN?usp=sharing

---

## Contributors

- Prashant Narang
- Arihant Bhandari
- Vigneshwar
- Poorna Sai Reddy
- Atharvakant Chandorikar
- Bhaskar
- Venepally Sathvika
- Prem Pratik 

---

## Files

- `stroboscope_final.ino` — Main Arduino sketch  
- `kalman.h` — Kalman filter library for IMU smoothing

---

## Tools Used

- Arduino IDE  
- Serial Monitor / Bluetooth terminal  
- Basic electronics tools (multimeter, breadboard, soldering kit)

---

This was a fun and collaborative team project — we thoroughly enjoyed building, experimenting, and learning throughout the process!


