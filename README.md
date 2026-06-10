 CodeAlpha IoT Internship – Task 2

## IoT-Based Arrhythmia Detector Simulation

### Author

Bhavesh Sai Naidu Ganta

### Internship

CodeAlpha – Internet of Things (IoT) Internship

### Task

Task 2: Sensor-Based IoT Simulation

## Project Overview

This project simulates an IoT-based Arrhythmia Detection System using Arduino. The system monitors heart rate values (BPM – Beats Per Minute) and classifies the patient's condition into different categories such as Normal, Bradycardia, Tachycardia, and Irregular Heartbeat.

A potentiometer is used to simulate sensor readings. The Arduino processes the input data, displays BPM values on an LCD screen, activates status LEDs, and generates buzzer alerts according to the detected heart condition.

## Components Used

* Arduino Uno
* 16x2 I2C LCD Display
* Potentiometer
* Green LED
* Red LED
* Blue LED
* Yellow LED
* Buzzer
* Jumper Wires

## Working Principle

1. The potentiometer acts as a simulated heart-rate sensor.
2. Arduino continuously reads analog values from the potentiometer.
3. The analog values are converted into BPM values ranging from 20 to 180.
4. The BPM is classified into different heart conditions.
5. The LCD displays the current BPM and health status.
6. LEDs indicate the detected condition visually.
7. The buzzer produces different alert sounds for different heart conditions.

## BPM Classification

| BPM Range | Condition   |
| --------- | ----------- |
| 60 – 100  | Normal      |
| Above 100 | Tachycardia |
| 40 – 59   | Bradycardia |
| Below 40  | Irregular   |

## LED Indications

| LED Color | Status              |
| --------- | ------------------- |
| Green     | Normal              |
| Red       | Tachycardia         |
| Blue      | Bradycardia         |
| Yellow    | Irregular Heartbeat |

## Code Explanation

### LCD Initialization

The LiquidCrystal_I2C library is used to communicate with the 16x2 LCD display. During startup, the LCD displays the project title and version information.

### Sensor Input

The potentiometer connected to analog pin A0 simulates heart-rate sensor readings.

```cpp
raw = analogRead(POT_PIN);
bpm = map(raw, 0, 1023, 20, 180);
```

The analog value is converted into BPM values between 20 and 180.

### Heart Condition Classification

The classify() function determines the patient's condition based on BPM.

```cpp
if (b >= 60 && b <= 100)
    return "NORMAL";
else if (b > 100)
    return "TACHYCARDIA";
else if (b >= 40 && b < 60)
    return "BRADYCARDIA";
else
    return "IRREGULAR";
```

### LED Status Indicators

Each heart condition activates a specific LED for easy visual identification.

### Buzzer Alerts

Different sound frequencies are generated for different heart conditions to provide audible alerts.

### LCD Monitoring

The LCD continuously displays:

* Current BPM
* Heart Condition Status

### Serial Monitor Output

The Arduino sends diagnostic information to the Serial Monitor, including:

* Raw sensor value
* Calculated BPM
* Current condition

## Features

* Real-time heart rate monitoring simulation
* BPM classification system
* LCD-based status display
* LED-based visual alerts
* Buzzer-based warning system
* Serial monitoring support
* Non-blocking operation using millis()

## Learning Outcomes

Through this project, I learned:

* Arduino programming fundamentals
* Analog sensor data acquisition
* BPM calculation and monitoring
* LCD interfacing using I2C
* LED and buzzer control
* Real-time embedded system design
* Basic healthcare IoT concepts

## Files Included

* Task1.ino
* Simulation Screenshots
* README.md

## Future Improvements

* Integration with actual pulse sensors
* Wi-Fi-based cloud monitoring
* Mobile application support
* Remote patient monitoring dashboard
* AI-based arrhythmia prediction

## Submitted For

CodeAlpha Internet of Things (IoT) Internship Program

---

**Author:** Bhavesh Sai Naidu Ganta
**Project:** IoT-Based Arrhythmia Detector Simulation
**Domain:** Internet of Things (IoT)
