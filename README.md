# AC Motor Starter Circuit for Industrial Applications

A microcontroller-based AC motor starter with forward/reverse control, thermal overload protection, and emergency stop – designed as a **Complex Engineering Activity** for the Electromechanical Systems Lab at FAST University.


## 📌 Features

- Bidirectional motor control (forward / reverse)
- Emergency stop and thermal overload protection (thermistor-based)
- Relay-based switching (8‑channel + 4‑channel) to isolate Arduino 5V logic from 3‑phase AC power
- Real‑time status indicators (LEDs)
- Validated with Proteus and MATLAB simulations

---

## 🛠️ Technologies & Hardware

| Category | Components |
|----------|-------------|
| **Microcontroller** | Arduino Uno |
| **Switching** | 8‑Channel Relay Module + 4‑Channel Relay Module |
| **Sensing** | Thermistor (for temperature/overload simulation) |
| **Simulation** | Proteus, MATLAB |
| **Others** | Push buttons, LEDs, 3‑phase AC motor (simulated coils), AC voltmeters/ammeters |

---

## 🔧 How It Works

1. **Input Stage**  
   - Four push buttons (Forward, Reverse, Stop, Emergency Stop) connected to Arduino digital pins with 10kΩ pull-down resistors.  
   - Thermistor forms a voltage divider with a 10kΩ resistor, feeding analog data to pin A0 to monitor motor temperature.

2. **Processing Stage**  
   - Arduino reads inputs and decides motor state.  
   - For **forward** rotation, relays connect phases R, Y, B to motor coils 1, 2, 3 respectively.  
   - For **reverse**, the logic swaps two phases, reversing the motor’s magnetic field.

3. **Output Stage**  
   - Relays energize the appropriate phase lines.  
   - Indicator LEDs show current status:  
     - Green = Forward  
     - Yellow = Reverse  
     - Red = Emergency / Overload  

4. **Protection**  
   - If the thermistor reading exceeds a temperature threshold **or** Emergency Stop is pressed, the Arduino immediately de-energizes all relays and lights the red LED.

---

## 🧪 Simulation Results (Proteus)

| Action | Expected Result |
|--------|----------------|
| Press **Forward** | Correct relays energize, green LED on |
| Press **Stop** | All motor relays de‑energized |
| Press **Reverse** | Phase swapping occurs, yellow LED on |
| Raise thermistor resistance (simulate overload) | All motor relays off, red LED on |
| AC voltmeters/ammeters | Display expected line parameters during operation |

*All logic was validated in both Proteus and MATLAB.*


---

## 👥 Team

- Muhammad Shariq (24K-6084)
- Muhammad Ali Siddiqui (24K-6121)
- **Syed Muneeb Ahmed (24K-6030)**  
- Abdullah Hussain (24K-6037)
- Syed Hassaan Ali (24K-6106)

---

## 🧠 What I Learned

- Interfacing low‑voltage logic (Arduino) with high‑power AC circuits using relays.
- Implementing software‑based interlocking for safe phase reversal without short circuits.
- Simulating electromechanical systems in Proteus and MATLAB.
- Documenting a Complex Engineering Activity for academic evaluation.

---

## 📜 License

This project is for educational purposes only.

---

## 🔗 Connect with Me

[![LinkedIn](https://img.shields.io/badge/-LinkedIn-blue?logo=linkedin)](https://www.linkedin.com/in/syed-muneeb-ahmed-027950393)  
[![GitHub](https://img.shields.io/badge/-GitHub-black?logo=github)](https://github.com/Buns-Dev)

"This is the whole code?"
