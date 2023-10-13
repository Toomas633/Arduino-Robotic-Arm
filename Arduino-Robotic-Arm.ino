// Made by Toomas633
// Still in progress project, code updates can be found in github: https://github.com/Toomas633/Arduino-Robotic-Arm

#include <Servo.h>
#include <usbhid.h>
#include <usbhub.h>
#include <XBOXONE.h>
#include <XBOXOLD.h>

USB Usb;
USBHub Hub(&Usb);
XBOXONE Xb1(&Usb);
XBOXOLD Xb(&Usb);

Servo servo01;
Servo servo02;
Servo servo03;
Servo servo04;
Servo servo05;
Servo servo06;

int servo1;
int servo2;
int servo3;
int servo4;
int servo5;
int servo6;

boolean gripper = false;
boolean xboxControllerConnected = false;
boolean psControllerConnected = false;

// Initial positions for servos when powering up and where to home. Change to where you like. Number after "position" means wich servo it corresponds to.
int initial_position1 = 75;
int initial_position2 = 175;
int initial_position3 = 175;
int initial_position4 = 90;
int initial_position5 = 0;
int initial_position6 = 180;

void setup()
{
  Serial.begin(115200);
  if (Usb.Init() == -1)
  {
    while (1)
      ;
  }

  // Pins to where you connect servos, change here if needed, no need further on.
  servo01.attach(2);
  servo02.attach(3);
  servo03.attach(4);
  servo04.attach(5);
  servo05.attach(6);
  servo06.attach(7);

  servo01.write(initial_position1);
  servo02.write(initial_position2);
  servo03.write(initial_position3);
  servo04.write(initial_position4);
  servo05.write(initial_position5);
  servo06.write(initial_position6);
}

// All voids here, differnet actoins/inputs have different voids
void loop()
{
  Usb.Task();

  servo1 = servo01.read();
  servo2 = servo02.read();
  servo3 = servo03.read();
  servo4 = servo04.read();
  servo5 = servo05.read();
  servo6 = servo06.read();

  int rightX = 100;
  int rightY = 100;
  int leftX = 100;
  int leftY = 100;
  int upDown = 100;

  boolean xboxConnected = Xb1.XboxOneConnected || Xb.XboxConnected;

  handleControllerConnection(xboxControllerConnected, xboxConnected, "Xbox");

  if (xboxConnected)
  {
    if (Xb1.getButtonClick(A) || Xb.getButtonClick(A))
    {
      gripper = !gripper;
      gripper_servo();
    }
    if (Xb1.getButtonClick(Y) || Xb.getButtonClick(Y))
    {
      auto_home();
    }

    if (Xb1.XboxOneConnected)
    {
      rightX = map(Xb1.getAnalogHat(RightHatX), -32800, 32800, 0, 200);
      rightY = map(Xb1.getAnalogHat(RightHatY), -32800, 32800, 0, 200);
      leftX = map(Xb1.getAnalogHat(LeftHatX), -32800, 32800, 0, 200);
      if (Xb1.getButtonPress(B))
      {
        upDown = map(Xb1.getAnalogHat(LeftHatY), -32800, 32800, 0, 200);
      }
      else
      {
        leftY = map(Xb1.getAnalogHat(LeftHatY), -32800, 32800, 0, 200);
      }
    }
    else
    {
      rightX = map(Xb.getAnalogHat(RightHatX), -32800, 32800, 0, 200);
      rightY = map(Xb.getAnalogHat(RightHatY), -32800, 32800, 0, 200);
      leftX = map(Xb.getAnalogHat(LeftHatX), -32800, 32800, 0, 200);
      if (Xb.getButtonPress(B))
      {
        upDown = map(Xb.getAnalogHat(LeftHatY), -32800, 32800, 0, 200);
      }
      else
      {
        leftY = map(Xb.getAnalogHat(LeftHatY), -32800, 32800, 0, 200);
      }
    }
  }

  right_joystick(rightX, rightY);
  left_joystick(leftX, leftY);
  wrist_servo(upDown);

  delay(20);
}

//=========================== Controller connection logic =================================
void handleControllerConnection(boolean &isConnected, boolean isCurrentlyConnected, const char *controllerName)
{
  if (isCurrentlyConnected != isConnected)
  {
    isConnected = isCurrentlyConnected;
  }
}

//============================== Right Joystick ===========================================
void right_joystick(int x, int y)
{
  if (x < 70)
  {
    initial_position4 = constrain(initial_position4 - map(x, 70, 0, 0, 8), 5, 175);
    servo04.write(initial_position4);
  }
  if (x > 130)
  {
    initial_position4 = constrain(initial_position4 + map(x, 130, 200, 0, 8), 5, 175);
    servo04.write(initial_position4);
  }
  if (y < 70)
  {
    initial_position3 = constrain(initial_position3 - map(x, 70, 0, 0, 8), 5, 175);
    servo03.write(initial_position3);
  }
  if (y > 130)
  {
    initial_position3 = constrain(initial_position3 + map(x, 130, 200, 0, 8), 5, 175);
    servo03.write(initial_position3);
  }
}

//================================== Left Joystick =============================================
void left_joystick(int x, int y)
{
  if (x < 70)
  {
    initial_position1 = constrain(initial_position1 + map(x, 70, 0, 0, 5), 10, 160);
    servo01.write(initial_position1);
  }
  if (x > 120)
  {
    initial_position1 = constrain(initial_position1 - map(x, 130, 200, 0, 5), 10, 160);
    servo01.write(initial_position1);
  }
  if (y < 70)
  {
    initial_position2 = constrain(initial_position2 - map(x, 70, 0, 0, 8), 5, 175);
    servo02.write(initial_position2);
  }
  if (y > 130)
  {
    initial_position2 = constrain(initial_position2 + map(x, 130, 200, 0, 8), 5, 175);
    servo02.write(initial_position2);
  }
}

//================================= Wrist servo =========================================
void wrist_servo(int value)
{
  if (value > 130)
  {
    initial_position5 = constrain(initial_position5 + map(value, 130, 200, 0, 8), 5, 175);
    servo05.write(initial_position5);
  }
  if (value < 70)
  {
    initial_position5 = constrain(initial_position5 - map(value, 70, 0, 0, 8), 5, 175);
    servo05.write(initial_position5);
  }
}

//================================= Auto home ========================================
void auto_home()
{
  initial_position1 = 75;
  initial_position2 = 175;
  initial_position3 = 175;
  initial_position4 = 90;
  initial_position6 = 180;
  servo01.write(initial_position1);
  servo02.write(initial_position2);
  servo03.write(initial_position3);
  servo04.write(initial_position4);
  servo06.write(initial_position6);
}

//============================== Grapple servo ===========================================
void gripper_servo()
{
  if (gripper)
  {
    servo06.write(0);
  }
  else
  {
    servo06.write(180);
  }
}
