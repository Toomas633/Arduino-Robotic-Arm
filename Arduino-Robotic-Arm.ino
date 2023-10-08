// Made by Toomas633
// Still in progress project, code updates can be found in github: https://github.com/Toomas633/Arduino-Robotic-Arm

#include <Servo.h>
#include <usbhid.h>
#include <usbhub.h>
#include <XBOXONE.h>

USB Usb;
USBHub Hub(&Usb);
XBOXONE Xb1(&Usb);

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

int leftY;
int leftX;
int rightY;
int rightX;
bool gripper = false;
bool home = false;

// Initial positions for servos when powering up and where to home. Change to where you like. Number after "position" means wich servo it corresponds to.
int initial_position1 = 75;
int initial_position2 = 175;
int initial_position3 = 175;
int initial_position4 = 90;
int initial_position5 = 0;
int initial_position6 = 180;

// Sensitivity: how many times to multiply the joystick input values
float sense = 1.0;

void setup()
{
  Serial.begin(9600);

  if (Usb.Init() == -1)
  {
    Serial.println("USB initialization failed.");
    while (1)
      ;
  }

  Serial.println("<Auto homing>");

  // Pins to where you connect servos, change here if needed, no need further on.
  servo01.attach(5);
  servo02.attach(6);
  servo03.attach(7);
  servo04.attach(8);
  servo05.attach(9);
  servo06.attach(10);

  delay(20);

  servo01.write(initial_position1);
  servo02.write(initial_position2);
  servo03.write(initial_position3);
  servo04.write(initial_position4);
  servo05.write(initial_position5);
  servo06.write(initial_position6);

  delay(20);

  Serial.println("<Arm is ready>");
}

// All voids here, differnet actoins/inputs have different voids
void loop()
{
  positions();
  read_controller();
  // auto_home();

  left_joystick();
  right_joystick();
  // wrist_servo();
  // grapple_servo();
}

//============================== Right Joystick ===========================================
void right_joystick()
{
  if (rightX < 300)
  {
    if (!initial_position4 < 10)
    {
      initial_position4 = constrain(initial_position4 - 5, 5, 175);
      servo04.write(initial_position4);
    }
  }
  if (rightX > 700)
  {
    if (!initial_position4 > 180)
    {
      initial_position4 = constrain(initial_position4 + 5, 5, 175);
      servo04.write(initial_position4);
    }
  }
  if (rightY < 300)
  {
    if (!initial_position3 < 10)
    {
      initial_position3 = constrain(initial_position3 + 8, 5, 175);
      servo03.write(initial_position3);
      delay(20);
    }
  }
  if (rightY > 700)
  {
    if (!initial_position3 > 180)
    {
      initial_position3 = constrain(initial_position3 - 8, 5, 175);
      servo03.write(initial_position3);
      delay(20);
    }
  }
}

//================================== Left Joystick =============================================
void left_joystick()
{
  if (leftX < 300)
  {
    if (!initial_position1 < 10)
    {
      initial_position1 = constrain(initial_position1 + 8, 10, 160);
      servo01.write(initial_position1);
      delay(20);
    }
  }
  if (leftX > 700)
  {
    if (!initial_position1 > 180)
    {
      initial_position1 = constrain(initial_position1 - 8, 10, 160);
      servo01.write(initial_position1);
      delay(20);
    }
  }
  if (leftY < 300)
  {
    if (!initial_position2 < 10)
    {
      initial_position2 = constrain(initial_position2 - 8, 5, 175);
      servo02.write(initial_position2);
      delay(20);
    }
  }
  if (leftY > 700)
  {
    if (!initial_position2 > 180)
    {
      initial_position2 = constrain(initial_position2 + 8, 5, 175);
      servo02.write(initial_position2);
      delay(20);
    }
  }
}

//================================= Auto home ========================================
void auto_home()
{
  if (home)
  {
    Serial.println("<Auto homing>");
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
    home != home;
  }
}

//================================= Wrist servo =========================================
void wrist_servo()
{
  int dir;

  servo05.write(180 - (dir + 520) / 10);
  delay(20);
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

//============================== Servo positions =======================================
void positions()
{
  servo1 = servo01.read();
  servo2 = servo02.read();
  servo3 = servo03.read();
  servo4 = servo04.read();
  servo5 = servo05.read();
  servo6 = servo06.read();
}

//============================= Read controller ========================================
void read_controller()
{
  Usb.Task();
  if (Xb1.XboxOneConnected)
  {
    leftX = Xb1.getAnalogHat(LeftHatX);
    leftY = Xb1.getAnalogHat(LeftHatY);
    rightX = Xb1.getAnalogHat(RightHatX);
    rightY = Xb1.getAnalogHat(RightHatY);

    if (Xb1.getButtonClick(A))
    {
      gripper != gripper;
    }
    if (Xb1.getButtonClick(START))
    {
      home != home;
    }
  }
}
