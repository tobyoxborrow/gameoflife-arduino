# Game of Life for Arduino

## Introduction

Small project to teach myself Arduino and programmable LEDs.

Some code copied from my earlier Java applet version of the game.

Game of life rules:
1. Any live cell with fewer than two neighbours dies, as if by loneliness.
2. Any live cell with more than three neighbours dies, as if by overcrowding.
3. Any live cell with two or three neighbours lives, unchanged, to the next
   generation.
4. Any dead cell with exactly three neighbours comes to life.

## Hardware

* Arduino Uno R3
* Unidentified LED matrix board consisting of:
  * MAX7219 Serially Interfaced, 8-Digit LED Display Driver
  * 1088AS 8x8 3mm LED matrix
* 5 male-to-female 1 wire patch cables
* USB cable for sketch upload and power

## Hardware Setup

Using the patch cables, connect the Arduino to the matrix board as follows:

* Arduino 5V to "VCC"
* Arduino GND to "GND"
* Arduino Digital Pin 10 to "CLK"
* Arduino Digital Pin 11 to "CS"
* Arduino Digital Pin 12 to "DIN"

Note: The matrix board uses slightly different labels to what may be found in
the MAX7219 datasheet.

## Arduino IDE Setup

You need to add the LedControl library to the Arduino IDE. From the Sketch
menu, select Libraries. Select Manage Libraries. From the Library Manager type
"ledcontrol" into the filter. Click on the LedControl library item and click
the Install button that appears.

Ensure the Arduino IDE is configured for your board model. From the Tools menu,
select the Board submenu and select your Arduino board.

Select the port for uploading the sketch to the board. From the Tools menu,
select the Port submenu and select the appropriate port on your computer. If
the port is not displayed, connect the USB cable to your computer and Arduino
board and check again.

## Installation

To install the sketch to the Arduino board, open the IDE and click the
upload button.

## Usage

When powered on the game will play by itself. It has conditions to reset itself
if the board has not change for a short while or the game has run for a certain
duration. That should avoid it being stuck in a single state for too long.

You can click the reset button on the Arduino board to trigger a game reset
too.
