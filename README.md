# Multithreaded GUI for Arduino LCD

This repository contains several Arduino sketches focused on building GUIs and interfacing with an LCD touchscreen using the ESP32. While a few test and demo files are included (such as basic GUI layouts, button tests, and screen redraw experiments), the **main focus** of this project is the `MultithreadedGUI.ino` sketch.

This primary sketch demonstrates a multithreaded graphical user interface (GUI) that simulates multitasking in a single-threaded Arduino environment. It provides a responsive touchscreen experience for interacting with timers, settings, and sensor displays.

## 📁 Sketches Overview

- `MultithreadedGUI.ino` – 🟢 **Main sketch**. Implements the full multithreaded GUI with touch input and efficient screen updates.
- `ButtonTest.ino` – Simple test for detecting touch input and button press behavior.
- `ScreenTest.ino` – Used for validating screen drawing functions and layouts.
- `TimeEdit.ino`, `TempEdit.ino` – Prototypes for adjusting time and temperature values.
- `GUI_States.ino` – Early experiment for managing screen transitions and state control.

---

## 📌 Project Overview (Main Sketch)

`MultithreadedGUI.ino` represents the fully developed interface for an LCD-based system. It includes:

- Button-driven navigation
- Touch input handling
- Screen updates without full refreshes
- Simulated "multithreading" using non-blocking code and loop management

The system is designed to manage multiple GUI states (e.g., temperature display, battery status, settings screen) and update specific screen portions only when needed, improving performance and user experience.

## 🖥️ Features

- 📱 Touch interaction with FT6336U controller
- 📊 Dynamic content switching (e.g., temp vs. battery %)
- ⚙️ Editable settings for temperature range and timer values
- 🔄 Partial screen updates for efficient redraws
- ⏱️ Real-time clock-based timing interface
- 🧠 Modular GUI state control logic

## 🧰 Hardware Used

- **ESP32-WROOM-32 Dev Module**
- **3.5" TFT SPI Touchscreen LCD**
  - Driver: ILI9488 (for display)
  - Touch Controller: FT6336U (I2C)
- MicroSD card slot (optional, not used in this sketch)
- Power: 3.3V

## 📦 Libraries Required

Make sure the following libraries are installed in your Arduino IDE:

- [`TFT_eSPI`](https://github.com/Bodmer/TFT_eSPI)
- Wire (built-in for I2C)
- Custom FT6336U touch driver (or I2C-based implementation)
