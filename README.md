<img align="right" src="https://sonarcloud.io/api/project_badges/quality_gate?project=Toomas633_Arduino-Robotic-Arm">

# Arduino Robotic Arm

- [Arduino Robotic Arm](#arduino-robotic-arm)
  * [About](#about)
    * [V1](#v1)
    * [V2](#v2)
  * [Donate](#donate)
  * [Licences](#licences)

## About

### V1

Arduino Uno robotic arm using joystick input
Had some spare servos and salvaged a broken controller for joysticks, decided to make a robotic arm. Had to put some spare metal to the base for extra heft so it won't tip over so easily. Going to replace the sg90 servos with metal gearbox ones soon, big ones already are. This is also the first project i have coded completly by myself. Joysticks cahnge the servo position values so they hold position and won't come back when you let go.
The reset button doesn't need a pullup resistor on it's lines (configured to use the Arduino's built in resistors). All other switches/buttons will need a 10k resistor on their gnd/input line).
Serial monitor also displays all the button and servo states in a table.

Download from releases [Version 1](https://github.com/Toomas633/Arduino-Robotic-Arm/releases/tag/v1) or from tag [v1](https://github.com/Toomas633/Arduino-Robotic-Arm/tree/v1).

### V2

Removed the custom joystick, moved servo connections down to pins 2-7 and added a USB HID hat for using XBOX controller input via usb wire. For a usb  hat I used [this](https://www.amazon.de/-/en/Hailege-Shield-Support-Google-Android/dp/B07YJQBGFW/ref=sr_1_1?crid=M0CZAVK8EEDM&dib=eyJ2IjoiMSJ9.uxUOWxowuN8wYjbckG61t4ETkl0BpUuPhKclKIu9ho0o56Rn-vxTOaOF1tx2MxtXGIvQPB9M4kJzaTuCvBazbLzo6LAThyz5McKRkB2MxVcqcv8Ckryv2YWeAoQTCv9OGmOkT9vNWi5bc9CLGh0TITjfdcn22-Vtc70pGIklAHo.dDYbhTCGCTeHEG1vmHcJjQNKjNQsKwl8qKGSgwjLumM&dib_tag=se&keywords=arduino+uno+usb+hat&qid=1725008057&sprefix=arduinouno+usb+hat%2Caps%2C128&sr=8-1) one but any should work aslong as they are supported by the [USB Host Shield Library 2.0](https://www.arduino.cc/reference/en/libraries/usb-host-shield-library-2.0/) and do not require custom drivers. The hat makes the arduino a bit higher and for connecting the usb you would need standoffs between the base of the arm and the top where servos connect.

Required libraries:

- [USB Host Shield Library 2.0](https://www.arduino.cc/reference/en/libraries/usb-host-shield-library-2.0/)
- [Servo](https://www.arduino.cc/reference/en/libraries/servo/)

Control scheme:

|      Button      | Action                           |
| :---------------: | -------------------------------- |
|     &#x24B6;     | Gripper open/close               |
|     &#x24C7;     | Rotate left-right and up-down   |
|     &#x24C1;     | Rotate Gripper or extend up-down |
| &#x24B7;+&#x24C1; | Gripper up/down                  |

Download it from releases [Version 2](https://github.com/Toomas633/Arduino-Robotic-Arm/releases/tag/v2) or from tag [v2](https://github.com/Toomas633/Arduino-Robotic-Arm/tree/v2).

## Donate

[toomas633.com/donate](https://toomas633.com/donate/)

## Licences

Model files: CERN Open Hardware Licence Version 2 - Strongly Reciprocal

Code files: GNU General Public License v3 (GPL-3)
