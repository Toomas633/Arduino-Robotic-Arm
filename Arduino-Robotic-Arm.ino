// Made by Toomas633
// Still in progress project, code updates can be found in github: https://github.com/Toomas633/Arduino-Robotic-Arm
// Reddit thread: https://www.reddit.com/r/arduino/comments/lv9i9n/my_first_ever_arduino_uno_powered_project/?utm_source=share&utm_medium=web2x&context=3
//<>
#include <SoftwareSerial.h>
#include <Servo.h>
                                // Change anu pins here, no need to change the code further on:
#define LX_JOY_PIN A0           // Left joystick x-axys line.
#define LY_JOY_PIN A1           // Left joystick y-axys line.
#define RX_JOY_PIN A2           // Right joystick x-axys.
#define RY_JOY_PIN A3           // Right joystick y-axys.
#define GRAPPLE_BUTTON_PIN 11   // Switch or button to make the grapple close and open.
#define GRAPPLE_LED_PIN 4       // Was going to use a status LED but made it to a power LED later on.
#define TRIM_PIN A4             // Potentiometer input to control servo 5 a.k.a wrist tilt.
#define R_BUTTON_PIN 3          // Button to reset servo positions, outcomment later in code to enable, don't have it wired up yet on my end, but it's ready to go.

Servo servo01;
Servo servo02;
Servo servo03;
Servo servo04;
Servo servo05;
Servo servo06;

int Wrist;
int StatusLED;
int servo1;
int servo2;
int servo3;
int servo4;
int servo5;
int servo6;
int LeftJoystickXVal;
int LeftJoystickYVal;
int RightJoystickXVal;
int RightJoystickYVal;
int initial_position1 = 75;   // Initial positions for servos when powering up and where to home. Change to where you like. Number after "position" means wich servo it corresponds to.
int initial_position2 = 175;
int initial_position3 = 175;
int initial_position4 =90;
int initial_position5 = 0;
int Grapple_position = 180;
int GrappleState = 0;
int ResetButtonState = 0;


void setup() {
  Serial.begin(9600);
  Serial.println("<Auto homing>");

  pinMode(R_BUTTON_PIN, INPUT);
  pinMode(GRAPPLE_BUTTON_PIN, INPUT);
  pinMode(GRAPPLE_LED_PIN, OUTPUT);
  
  servo01.attach(5);    // Pins to where you connect servos, change here if needed, no need further on.
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

  digitalWrite(GRAPPLE_LED_PIN, HIGH);    //Use as power LED, change code under grapple_servo() if wanted to show grapple state.

  delay(20);
  
  Serial.println("<Arm is ready>");
}

void definitions()     // All definitions are made here for easy keeping and editing.
{
  servo1 = servo01.read();
  servo2 = servo02.read();
  servo3 = servo03.read();
  servo4 = servo04.read();
  servo5 = servo05.read();
  servo6 = servo06.read();
  StatusLED = digitalRead(GRAPPLE_LED_PIN);
  Wrist = analogRead(TRIM_PIN);
  LeftJoystickXVal = analogRead(LX_JOY_PIN);
  LeftJoystickYVal = analogRead(LY_JOY_PIN);
  RightJoystickXVal = analogRead(RX_JOY_PIN);
  RightJoystickYVal = analogRead(RY_JOY_PIN);
  GrappleState = digitalRead(GRAPPLE_BUTTON_PIN);
//  ResetButtonState = digitalRead(R_BUTTON_PIN);   // Comment in if reset button is wired.
}

void loop()   //All voids here, differnet actoins/inputs have different voids
{
//  reset();
  serial();
  definitions();
  left_joystick();
  right_joystick();
  wrist_servo();
  grapple_servo();
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
  servo05.write(180-(Wrist + 520)/10);
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
//================================== Serial ========================================
void serial()   // Edit if more serial functionality is needed (currently working on my 
{
  delay(20);
//  Serial.println();
}
