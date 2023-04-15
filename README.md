# Arduino Robotic Arm
- [Arduino Robotic Arm](#arduino-robotic-arm)
  * [About:](#about)
  * [Donate:](#donate)


## About
Arduino Uno robotic arm using joystick input
Had some spare servos and salvaged a broken controller for joysticks, decided to make a robotic arm. Had to put some spare metal to the base for extra heft so it won't tip over so easily. Going to replace the sg90 servos with metal gearbox ones soon, big ones already are. This is also the first project i have coded completly by myself. Joysticks cahnge the servo position values so they hold position and won't come back when you let go.
The reset button doesn't need a pullup resistor on it's lines (configured to use the Arduino's built in resistors). All other switches/buttons will need a 10k resistor on their gnd/input line).
Serial monitor also displays all the button and servo states in a table.

## Donate
Monero: `46b9jWCbtfDEGibADKG5uqL12r8RDohm1ZjkSK2ZW3T3gTsUYSPGpvu5fvhJZjuBGRbN8HnKWc8T6RFvzuUxTQjFF5osdeP`

Bitcoin: `3NPFV9ivECdSgyCXeNk4h5Gm3q1xiDRnPV`

More options on https://toomas633.com/donate/

## Licences
Model files: CERN Open Hardware Licence Version 2 - Strongly Reciprocal

Code files: GNU General Public License v3 (GPL-3)
