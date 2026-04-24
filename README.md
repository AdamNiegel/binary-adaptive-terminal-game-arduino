# binary-adaptive-terminal-game-arduino (4/24/26)
Adaptive Binary Coding Game System using Arduino + I2C LCD

This project is an Arduino-based interactive learning system that gamifies binary-to-hexadecimal conversion. It simulates a mini “computer terminal” where users input binary data using physical buttons, and the system evaluates the input against randomly generated challenges. It includes an adaptive difficulty engine that adjusts based on user performance, making the experience dynamic and progressively challenging.



## How it works
The system generates a random hexadecimal value and converts it into its binary equivalent internally. The user must reconstruct the correct 8-bit binary sequence using two input buttons (0 and 1). Once the ENTER button is pressed, the system checks the answer, updates the score, and adjusts the difficulty level based on performance.

An additional button allows the user to skip to a new challenge. The system also includes a special exit mode triggered when all four buttons are pressed simultaneously.



## Features
- Interactive binary input system using physical buttons
- Real-time binary-to-hexadecimal conversion validation
- Adaptive difficulty system (easy → expert scaling)
- Score and streak tracking system
- Randomized challenge generator (0–255 range)
- LCD-based terminal-style user interface
- System exit mode using multi-button combination
- Embedded learning game structure



## Key Concepts Used
- Binary and hexadecimal number systems
- Bitwise operations and bit manipulation
- ASCII and numeric encoding principles
- State machine logic for game control
- Adaptive algorithm based on user performance
- Embedded UI design using I2C LCD
- Event-driven button handling with INPUT_PULLUP



## Hardware Requirements
- Arduino UNO
- 16x2 I2C LCD Display
- Push buttons (x4)
- Jumper wires
- Breadboard



## Button Mapping
- Button 1 (Pin 6) → Input bit 0  
- Button 2 (Pin 7) → Input bit 1  
- Button 3 (Pin 8) → ENTER / Submit answer  
- Button 4 (Pin 9) → Next challenge / Skip  

**Special Feature:**
- Press ALL 4 buttons simultaneously → System exits game mode (shutdown state)



## System Behavior
- Correct answers increase score and difficulty level
- Consecutive correct answers trigger harder challenges
- Consecutive wrong answers reduce difficulty for learning support
- System continuously generates new randomized binary challenges
- LCD acts as a real-time terminal display for input and results



## Future Improvements
- EEPROM-based high score saving system
- Sound feedback for correct/incorrect answers
- Timer-based challenge mode
- Multiplayer competitive mode
- Expanded instruction set (mini CPU simulation)
- Graphical OLED upgrade for improved interface

---

## Author
Developed as an embedded systems learning project focused on number systems, digital logic, and interactive microcontroller-based game design. The project demonstrates how fundamental computing concepts can be transformed into an educational and gamified hardware experience.
