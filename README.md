# ❤️ DaisyHeart

A 16-LED heart-shaped display driven by an ATtiny85 microcontroller and two 74HC595 shift registers. It features multiple animations controlled by two physical push buttons.

## 🎥 Demo

<img width="896" height="1196" alt="image" src="https://github.com/user-attachments/assets/bc455dea-c2b0-4b8f-8151-072f9f0aed07" />

Link to ensamples  https://youtu.be/dNeGOBqm8pQ

## 🛠️ Hardware Used
*   1x ATtiny85 (on headers for easy reprogramming)
*   2x 74HC595 Shift Registers
*   16x 5mm LEDs (Color: Orange)
*   16x 220Ω Resistors
*   2x Tactile Push Buttons
*   Prototype PCB Board

## 🔌 Wiring & Connections
  **ATtiny85 PB0** -> 74HC595 DS (Pin 14)
  **ATtiny85 PB1** -> 74HC595 SHCP (Pin 11)
  **ATtiny85 PB2** -> 74HC595 STCP (Pin 12)
  **Daisy Chaining:** 74HC595 #1 Q7S (Pin 9) -> 74HC595 #2 DS (Pin 14)
  
## 🕹️ How to Use
*   **Button 1 (P3):** Short press cycles through 6 animations. Long press (0.8s) turns all LEDs ON.
*   **Button 2 (P4):** Changes the speed of the animations (Slow, Normal, Fast).

## ⚠️ Lessons Learned
*   Always use a multimeter in continuity mode to check for cold solder joints on the shift register outputs.
*   Ensure the ATtiny85 is removed from the board when uploading code via the Arduino Uno ISP.
*   
