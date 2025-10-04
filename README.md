# ESP32 Ultrasonic Distance Indicator with LED Strip

## Project Overview
This project uses an **ESP32** devkit along with an **ultrasonic sensor** and an **RGB LED strip** to visually indicate distance. The LED strip acts as a **real-time distance warning system**:

- If an object is **closer than 10 cm**, all LEDs **flash red** as a warning.  
- Between **10 cm and 100 cm**, the number of LEDs lit corresponds to the distance of the object, providing a **visual gradient** of proximity.  
- Distance readings are also displayed in the **serial monitor** for debugging and verification.  

---

## Components Used
- ESP32 Devkit  
- Ultrasonic sensor (HC-SR04 or equivalent)  
- RGB LED strip (e.g., WS2812, NeoPixel, 8 LEDs)  
- Jumper wires and breadboard  
- Power source for ESP32  

---

## Circuit Connections

| Component          | ESP32 Pin |
|-------------------|-----------|
| Ultrasonic TRIG    | GPIO 6    |
| Ultrasonic ECHO    | GPIO 5    |
| LED Strip Data     | GPIO 4    |
| GND                | Common Ground |
| VCC                | 3.3V/5V (depending on LED strip) |

> Ensure the LED strip voltage matches the ESP32 output, and use a resistor or level shifter if needed for stability.

---

## Code Functionality

### 1. Ultrasonic Distance Measurement
- Sends a pulse from TRIG pin and measures echo time to calculate distance.  
- Distance is clamped between **10 cm** (`MIN_DIST`) and **100 cm** (`MAX_DIST`) for visualization.  

### 2. LED Strip Behavior
- **Distance ≥ 10 cm:**  
  - Number of LEDs lit is proportional to distance (mapped to 1–8 LEDs).  
- **Distance < 10 cm:**  
  - All LEDs blink red as an alert.  

### 3. Serial Monitor Output
Distance readings and number of LEDs turned on are printed for monitoring.  

Example:
```text
Distance: 35.00cm | LEDs ON: 3
Distance: 8.50cm | LEDs ON: 0 → ALERT: Flashing LEDs
