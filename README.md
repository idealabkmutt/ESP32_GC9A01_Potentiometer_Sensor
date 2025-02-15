# TFT Display with BMP280 Sensor and Rotary Potentiometer

## Overview
This project utilizes an ESP32 microcontroller to display sensor data on a 240x240 TFT screen. The system reads data from a BMP280 sensor and a rotary potentiometer, allowing users to switch between different display modes using buttons.

## Features
- Displays sensor data from a **BMP280** (Temperature, Pressure, Altitude)
- Reads values from a **Rotary Potentiometer**
- Uses two buttons to cycle through display modes
- Updates the display every **0.5 seconds**

## Components Used
- **ESP32** (or compatible microcontroller)
- **TFT 240x240 Display** (Using `TFT_eSPI` library)
- **BMP280 Sensor** (Using `Adafruit_BMP280` library)
- **Rotary Potentiometer**
- **Two push buttons**

## Wiring Diagram
| Component     | ESP32 Pin                    |
|---------------|------------------------------|
| TFT Display   | Configured in `User_Setup.h` |
| BMP280 (SDA)  | GPIO 21                      |
| BMP280 (SCL)  | GPIO 22                      |
| Potentiometer | GPIO 34                      |
| Button 1      | GPIO 5                       |
| Button 2      | GPIO 16                      |

## Installation
1. Install **Arduino IDE** (or **PlatformIO** if using VS Code)
2. Install the required libraries:
   ```bash
   Arduino IDE: Library Manager
   - TFT_eSPI
   - Adafruit BMP280
   - Adafruit Sensor
   ```
3. Modify `User_Setup.h` in `TFT_eSPI` to match your TFT display settings.
4. Upload the code to your ESP32.

## How It Works
- **Button 1 & Button 2**: Pressing them cycles through four display modes:
  1. **Rotary Value**
  2. **Altitude (m)**
  3. **Pressure (hPa)**
  4. **Temperature (°C)**
- **Display updates every 0.5s** via a timer interrupt.
- The **serial monitor** logs sensor values in real time.

## Code Breakdown
- Uses **`Ticker`** to periodically update the display.
- Implements **debounce logic** for button presses.
- Reads **analog values** from the potentiometer.
- Displays values on the **TFT screen** using `TFT_eSPI`.

## Example Output (Serial Monitor)
```
Mode: 2 | Temp: 25.6°C | Pressure: 1012.5 hPa | Altitude: 35.2m | Rotary: 62.3%
```

## License
This project is open-source under the **MIT License**. Feel free to modify and improve it!

---
**Author:** Pha.Chon (Thiraphop Chantra)

