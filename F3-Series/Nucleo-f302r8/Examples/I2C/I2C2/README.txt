STM32 I2C2 Bare-Metal Driver

This example configures I2C2 on the STM32F302R8 using direct register access.

⚙️ Features
Bare-metal I2C2 initialization
GPIO alternate function setup (SCL / SDA)
Standard mode configuration (100 kHz)

▶️ Usage
I2C2_Init();

🧠 Highlights
RCC clock control
GPIO AF4 configuration
I2C registers: CR1, TIMINGR

📌 Note
This project is intended for learning low-level STM32 peripheral control.
