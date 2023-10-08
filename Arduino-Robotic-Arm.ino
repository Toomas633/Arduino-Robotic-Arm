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

// Initial positions for servos when powering up and where to home. Change to where you like. Number after "position" means wich servo it corresponds to.
int initial_position1 = 75;
int initial_position2 = 175;
int initial_position3 = 175;
int initial_position4 = 90;
int initial_position5 = 0;
int Grapple_position = 180;
int GrappleState = 0;
int ResetButtonState = 0;

void setup()
{
  Serial.begin(9600);

  if (Usb.Init() == -1) {
    Serial.println("USB initialization failed.");
    while(1);
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
  servo06.write(Grapple_position);

  delay(20);

  Serial.println("<Arm is ready>");
}

// All definitions are made here for easy keeping and editing.
void definitions()
{
  servo1 = servo01.read();
  servo2 = servo02.read();
  servo3 = servo03.read();
  servo4 = servo04.read();
  servo5 = servo05.read();
  servo6 = servo06.read();
}

// All voids here, differnet actoins/inputs have different voids
void loop()
{
  // reset();
  // definitions();
  // left_joystick();
  // right_joystick();
  // wrist_servo();
  // grapple_servo();
}

//============================== Right Joystick ===========================================
void right_joystick()
{
  if (RightJoystickXVal < 300)
  {
    if (initial_position4 < 10)
    {
    }
    else
    {
      initial_position4 = constrain(initial_position4 - 5, 5, 175);
      servo04.write(initial_position4);
    }
  }
  if (RightJoystickXVal > 700)
  {
    if (initial_position4 > 180)
    {
    }
    else
    {
      initial_position4 = constrain(initial_position4 + 5, 5, 175);
      servo04.write(initial_position4);
    }
  }
  if (RightJoystickYVal < 300)
  {
    if (initial_position3 < 10)
    {
    }
    else
    {
      initial_position3 = constrain(initial_position3 + 8, 5, 175);
      servo03.write(initial_position3);
      delay(20);
    }
  }
  if (RightJoystickYVal > 700)
  {
    if (initial_position3 > 180)
    {
    }
    else
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
  if (LeftJoystickXVal < 300)
  {
    if (initial_position1 < 10)
    {
    }
    else
    {
      initial_position1 = constrain(initial_position1 + 8, 10, 160);
      servo01.write(initial_position1);
      delay(20);
    }
  }
  if (LeftJoystickXVal > 700)
  {
    if (initial_position1 > 180)
    {
    }
    else
    {
      initial_position1 = constrain(initial_position1 - 8, 10, 160);
      servo01.write(initial_position1);
      delay(20);
    }
  }
  if (LeftJoystickYVal < 300)
  {
    if (initial_position2 < 10)
    {
    }
    else
    {
      initial_position2 = constrain(initial_position2 - 8, 5, 175);
      servo02.write(initial_position2);
      delay(20);
    }
  }
  if (LeftJoystickYVal > 700)
  {
    if (initial_position2 > 180)
    {
    }
    else
    {
      initial_position2 = constrain(initial_position2 + 8, 5, 175);
      servo02.write(initial_position2);
      delay(20);
    }
  }
}

//================================= Reset button ========================================
void reset()
{
  if (ResetButtonState = HIGH)
  {
    Serial.println("<Auto homing>");
    delay(20);
    initial_position1 = 75;
    initial_position2 = 175;
    initial_position3 = 175;
    initial_position4 = 90;
    Grapple_position = 180;
    delay(20);
    servo01.write(initial_position1);
    servo02.write(initial_position2);
    servo03.write(initial_position3);
    servo04.write(initial_position4);
    servo06.write(Grapple_position);
  }
}

//================================= Wrist servo =========================================
void wrist_servo()
{
  servo05.write(180 - (Wrist + 520) / 10);
  delay(20);
}
//============================== Grapple servo ===========================================
void grapple_servo()
{
  if (GrappleState = HIGH)
  {
    servo06.write(0);
    delay(20);
  }
  else
  {
    servo06.write(180);
    delay(20);
  }
}

//============================= Read controller ========================================
void read_controller() {
  Usb.Task();
  if (Xb1.XboxOneConnected) {
    int leftX = Xb1.getAnalogHat(LeftHatX);
    int leftY = Xb1.getAnalogHat(LeftHatY);
    int rightX = Xb1.getAnalogHat(RightHatX);
    int rightY = Xb1.getAnalogHat(RightHatY);

    if (Xb1.getButtonClick(A)) {
      Serial.println("A button pressed.");
    }
    if (Xb1.getButtonPress(B)) {
      Serial.println("B button pressed.");
    }
  }
}
