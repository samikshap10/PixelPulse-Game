[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/eqbV8gqw)

# PixelPulse Game

## Overview
PixelPulse is a simple game implemented on the MKL25Z4 microcontroller. It utilizes an LCD display and a button for user interaction. The game involves controlling a character to navigate through obstacles.

## Testing 
- Happy Cases : Prinitng on two lines
- Corner and error cases : Prinitng teh stored Custom character from    CGRAM to the corners and middel of the LCD display.

## File Structure
- **PixelPulse.c**: Main entry point of the application. Initializes hardware peripherals and controls the game loop.
- **button.c/button.h**: Files for handling the button input.
- **delay.c/delay.h**: Files containing functions for generating delays using software loops.
- **game.c/game.h**: Files containing functions for controlling the gameplay.
- **systime.c/systime.h**: Files containing functions for initializing and handling system time using the SysTick timer.
- **LCD.c/LCD.h**: Files containing functions for interfacing with the LCD display using the I2C protocol.
- **I2C.c/I2C.h**: Files containing functions for initializing and communicating over the I2C bus.

## Usage
1. Connect the MKL25Z4 microcontroller to the LCD display and a button.
2. Power on the system.
3. Play the game by pressing the button to control the character and navigate through obstacles.

