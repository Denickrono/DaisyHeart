❤️ DaisyHeart
A 16-LED heart-shaped display driven by an ATtiny85 microcontroller (Digispark) and two daisy-chained 74HC595 shift registers. It features six unique animations and an "Always ON" mode, all controlled by two physical push buttons.

🎥 Demo
<img width="896" height="1196" alt="image" src="https://github.com/user-attachments/assets/b52d9951-f9fe-4657-991f-32c9c8f74b2b" />
Watch the demo here https://youtu.be/dNeGOBqm8pQ

🛠️ Hardware Used
1x ATtiny85 (Mounted on header pins for easy removal and reprogramming)
2x 74HC595 Shift Registers (8-Bit Serial-In, Parallel-Out)
16x 5mm LEDs (Orange)
16x 220Ω Resistors (One per LED)
2x Tactile Push Buttons
1x Prototype PCB Board
1x Arduino Uno (Used strictly as an ISP Programmer)

🔌 Wiring & Connections
Shift Register to Microcontroller
ATtiny85 PB0 (Data) ➔ 74HC595 DS (Pin 14)
ATtiny85 PB1 (Latch) ➔ 74HC595 STCP (Pin 12)
ATtiny85 PB2 (Clock) ➔ 74HC595 SHCP (Pin 11)
Daisy Chaining (Connecting the two registers)
74HC595 #1 Q7S (Pin 9) ➔ 74HC595 #2 DS (Pin 14)

Physical Board Wiring Colors (Reference)
🟢 Green Wire: DS (Data) ➔ PB0 of the Digispark
⚪ White Wire: SHCP (Clock) ➔ PB1 of the Digispark
🟤 Brown Wire: STCP (Latch) ➔ PB2 of the Digispark
⚫ Ground: GND rail ➔ Digispark GND
🔴 Power: 5V rail ➔ Digispark 5V

LED Array
Anodes (+) ➔ 74HC595 Output Pins (Q0 - Q7 on both chips)
Cathodes (-) ➔ 220Ω Resistor ➔ Common Ground (GND) Rail

🕹️ How to Use
Button 1 (PB3):
Short Press: Cycles through the 6 animations (Rotate, Fill/Drain, Heartbeat, Sweep, Ping-Pong, Sparkle).
Long Press (0.8s): Instantly turns ALL LEDs ON (Always ON mode).

Button 2 (PB4):
Changes the speed of the animations (Slow ➔ Normal ➔ Fast).

💻 Programming the ATtiny85 (The Uno ISP Method)
A point to note: My ATtiny85's onboard USB port broke, so I could not program it directly. Instead, I used an Arduino Uno as an In-System Programmer (ISP) to bypass the broken port and flash the code directly to the chip.
How it was done:
The Uno's Role: The Arduino Uno was loaded with the standard ArduinoISP sketch, turning it into a hardware programmer.
The 10µF Capacitor: A 10µF capacitor was placed between the Uno's RESET and GND pins. This prevents the Uno from resetting itself during the upload process.
The Wiring: The Uno was wired to the ATtiny85's SPI pins (P0, P1, P2) and Reset pin (P5).
Uploading: In the Arduino IDE, selecting "Sketch > Upload Using Programmer" pushed the code through the Uno and into the ATtiny85.
(Note: Because the ATtiny is on header pins, it can easily be popped out of the heart board and placed into the Uno programming circuit whenever the code needs to be updated).

⚠️ Lessons Learned
Multimeter Magic: If the LEDs aren't working properly, always use a multimeter in continuity (beep) mode to check for cold solder joints or bridges on the shift register outputs. That is how I found the exact fault after hours of troubleshooting!
Power Limits: 16 LEDs drawing power at the same time can pull too much current for the ATtiny85's onboard voltage regulator. Ensure the shift registers and LEDs are powered by a strong 5V supply.
Removable Chips: Always use header pins for the ATtiny. It makes reprogramming 100x easier than soldering it directly to the board.
