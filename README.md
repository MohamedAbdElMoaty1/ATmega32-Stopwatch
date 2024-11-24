# ATmega32-Stopwatch

A versatile and interactive digital stopwatch implemented using the ATmega32 microcontroller. This project combines efficient hardware interfacing with clear, user-friendly controls for setting, navigating, and displaying a countdown timer. The stopwatch provides a robust platform for embedded systems enthusiasts to learn about real-time application development.

---

## 📌 Features

- **Real-Time Display**: Time updates in `HH:MM:SS` format using a 16x2 character LCD.
- **Custom Input Controls**:
  - Set hours, minutes, and seconds using a 4x4 keypad.
  - Navigate through digits with dedicated Right and Left buttons.
  - Start the countdown with a single button press.
- **Timeout Notification**: Displays a clear "TIME OUT" message upon countdown completion.
- **Enhanced UX**:
  - Includes a custom arrow graphic for precise digit selection.
  - Debouncing ensures stable input for buttons and switches.

---

## 🛠️ Components

### Hardware
- **Microcontroller**: ATmega32
- **Display**: 16x2 Character LCD
- **Input Devices**:
  - 4x4 Keypad
  - Push Buttons (Right, Left, Start)

### Software
- **Libraries Used**:
  - `DIO` (Digital Input/Output)
  - `PORT` (Port Configuration)
  - `CLCD` (Character LCD Interface)
  - `SWITCH` (Button Interface)
  - `KPD` (Keypad Interface)

---

## ⚙️ How It Works

### 1. **Set Timer**  
   - Input time using the keypad, and navigate between digits using the Right and Left buttons. A custom arrow indicates the current selection.

### 2. **Start Countdown**  
   - Press the Start button to begin the countdown. The LCD updates the time every second.

### 3. **Timeout Notification**  
   - When the timer reaches `00:00:00`, a "TIME OUT" message is displayed, and the system resets for a new input.

---

## 🔧 Project Structure

The project is organized into modules for better maintainability:

- **Main Application**: Implements the stopwatch logic, including input handling and countdown functionality.
- **Peripheral Drivers**: Provides abstraction for LCD, keypad, and switch interfaces.
- **Custom Characters**: Defines the arrow graphic for navigation.

---

## 📋 Usage Instructions

### 1. Clone the Repository
```bash
git clone https://github.com/MohamedAbdElMoaty1/ATmega32-Stopwatch.git
