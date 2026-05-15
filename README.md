# AC Motor Starter Circuit for Industrial Applications

![Proteus Simulation](images/simulation.png)  <!-- optional -->

A microcontroller-based AC motor starter with forward/reverse control, thermal overload protection, and emergency stop – designed as a **Complex Engineering Activity** for the Electromechanical Systems Lab at FAST University.

## 📌 Features
- Bidirectional motor control (forward / reverse)
- Emergency stop and thermal overload protection (thermistor-based)
- Relay-based switching (8-channel + 4-channel) to isolate Arduino 5V logic from 3‑phase AC power
- Real‑time status indicators (LEDs)
- Validated with Proteus and MATLAB simulations

## 🛠️ Technologies & Hardware
- **Microcontroller**: Arduino Uno
- **Switching**: 8‑Channel Relay Module + 4‑Channel Relay Module
- **Sensing**: Thermistor (for temperature/overload simulation)
- **Simulation**: Proteus, MATLAB
- **Others**: Push buttons, LEDs, 3‑phase AC motor (simulated coils)

## 🔧 How It Works
1. **Input**: Four push buttons (Forward, Reverse, Stop, Emergency Stop) connected to Arduino digital pins (with 10kΩ pull-down resistors). Thermistor forms a voltage divider for analog temperature monitoring.
2. **Logic**: Arduino reads inputs and decides motor state. For forward rotation, relays connect phases R, Y, B to motor coils 1,2,3 respectively. For reverse, two phases are swapped.
3. **Output**: Relays energize the appropriate phase lines. Indicator LEDs show current status (green = forward, yellow = reverse, red = emergency/overload).
4. **Protection**: If thermistor temperature exceeds threshold or emergency stop is pressed, all relays de‑energize and red LED lights up.

## 🧪 Simulation Results (Proteus)
- Forward button → correct relays energize + green LED
- Stop button → all motor relays de‑energized
- Reverse button → phase swapping occurs + yellow LED
- Overload (thermistor high) → all motor relays off + red LED
- AC voltmeters/ammeters display expected values

## 📁 Repository Structure
