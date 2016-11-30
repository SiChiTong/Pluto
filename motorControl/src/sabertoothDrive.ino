//--------------------------------------------------------------
// Author: Ashish Choudhari
// Email: choudhariashish@gmail.com
//
//--------------------------------------------------------------
// Platform: Pluto
// Program that runs on Arduino uno and controls sabertooth
// 2x12 Amps motor driver.
//--------------------------------------------------------------
//
// Usage:
//
// Serial commands at 115200:
//
// w<steps> -Move forward
// s<steps> -Move reverse
// a<steps> -Move left
// d<steps> -Move right
// q<steps> -Move left forward
// z<steps> -Move left reverse
// e<steps> -Move right forward
// c<steps> -Move right reverse
// x        -Stop
// r<speed> -Reset speed
// t<speed> -Reset speed of left
// y<speed> -Reset speed of right
// f        -Get current speed, returns- "L30:R40" (for example)
// 4,7,10,11,13 are for safety switches
// Example: w20 -Moves 20 steps forward
//          r40 -Resets speed to 40 
//               (Speed range: 1-63 in both directions)
// H        -Help
//--------------------------------------------------------------

#include <SoftwareSerial.h>

#define NAME    "Name: MotorDrive"
#define VERSION "Version: 0.0.1"

const char NameVersionStr[] = "Name: MotorDrive Version: 0.0.1";

SoftwareSerial motor(5,6); // 5-orange, 6-brown

//--------------------------------------------------------------
// 0-127   :   Left motor
// 128-256 :   Right motor
// Center(64, 192) stop respectively
//--------------------------------------------------------------

//--------------------------------------------------------------
// Motor encoder pin configuration
//--------------------------------------------------------------
#define ENC_M_LEFT_A    2     // Encoder A pin for left motor
#define ENC_M_RIGHT_A   3     // Encoder A pin for right motor

#define ENC_M_LEFT_B    8     // Encoder B pin for left motor
#define ENC_M_RIGHT_B  12     // Encoder B pin for right motor

// Encoder steps in one revolution
#define STEPS_IN_ONE_REV    663 * 8

//--------------------------------------------------------------
// Standard arduino setup routine
//--------------------------------------------------------------
void setup() 
{
  //------------------------------------------------------------
  // Initialize standard serial to receive commands from host
  Serial.begin(115200);
  Serial.setTimeout(10);
  
  motor.begin(19200);  
  delay(10);

  // LEFT motor
  // Encoder pin B as input
  pinMode(ENC_M_LEFT_B, INPUT);
  // RIGHT motor
  // Encoder pin B as input
  pinMode(ENC_M_RIGHT_B, INPUT);  

  // Attach interrupt. Gets called everytime a signal is
  // detected
  attachInterrupt(1, leftMotorMovedISR, FALLING);// int.0
  // Attach interrupt. Gets called everytime a signal is
  // detected
  attachInterrupt(0, rightMotorMovedISR, FALLING);// int.1
}


//--------------------------------------------------------------
// Low level driver specific hard coded values
//--------------------------------------------------------------
void setLeftSpeed(unsigned int spd)
{
  motor.write(spd+127);  // spd: 1-63: FWD, 65-127: REV
}
void setRightSpeed(unsigned int spd)
{
  motor.write(spd);  // spd: 1-63: FWD, 64-127: REV
}
bool moveLeftFwd(unsigned int spd)
{
  // calibrate spd
  spd = 64-spd;
  // check if valid speed
  if(spd < 1 || spd > 64)
  {
    return false;    
  }
  setLeftSpeed(spd);  
  return true;
}
bool moveRightFwd(unsigned int spd)
{
  // calibrate spd
  spd = 64-spd;
  // check if valid speed
  if(spd < 1 || spd > 64)
  {
    return false;    
  }
  setRightSpeed(spd);  
  return true;
}
bool moveLeftRev(unsigned int spd)
{
  // calibrate spd
  spd = 64+spd;
  // check if valid speed
  if(spd < 65 || spd > 127)
  {
    return false;    
  }
  setLeftSpeed(spd);  
  return true;
}
bool moveRightRev(unsigned int spd)
{
  // calibrate spd
  spd = 64+spd;
  // check if valid speed
  if(spd < 65 || spd > 127)
  {
    return false;    
  }
  setRightSpeed(spd);  
  return true;
}
void stopLeft()
{
  setLeftSpeed(64);    
}
void stopRight()
{
  setRightSpeed(64);    
}


unsigned int LeftSteps=0;
unsigned int RightSteps=0;

unsigned int LeftDesiredSteps=0;
unsigned int RightDesiredSteps=0;

unsigned int LeftCurrMode=0;
unsigned int RightCurrMode=0;

unsigned int LeftSpeed=64;
unsigned int RightSpeed=64;

bool EnableStreaming=0;

struct Update
{
  unsigned int leftSteps;
  unsigned int leftSpeed;
  unsigned int leftCurrMode;

  unsigned int rightSteps;
  unsigned int rightSpeed;
  unsigned int rightCurrMode;
} __attribute__ ((packed));

struct Update u;

//--------------------------------------------------------------
// ISR implementations
// Developer note:- Never print in ISRs
//--------------------------------------------------------------
void leftMotorMovedISR(){ LeftSteps++; }
void rightMotorMovedISR(){ RightSteps++; }

//--------------------------------------------------------------
// Arduino standard while loop
//--------------------------------------------------------------
void loop() 
{
  if(LeftSteps<LeftDesiredSteps)
  {
    // Increase speed
    (LeftSpeed<63) ? LeftSpeed++ : LeftSpeed=63;

    // Move left, 0:Fwd, 1:Rev
    (0==LeftCurrMode) ? moveLeftFwd(LeftSpeed) : moveLeftRev(LeftSpeed);
  }
  else
  {
    // Stop
    stopLeft();
  }

  if(RightSteps<RightDesiredSteps)
  {
    // Increase speed
    (RightSpeed<63) ? RightSpeed++ : RightSpeed=63;

    // Move right, 0:Fwd, 1:Rev
    (0==RightCurrMode) ? moveRightFwd(RightSpeed) : moveRightRev(RightSpeed);
  }
  else
  {
    // stop
    stopRight();
  }

  if(1==EnableStreaming)
  {
    u.leftSteps = LeftSteps;
    u.leftSpeed = LeftSpeed;
    u.leftCurrMode = LeftCurrMode;

    u.rightSteps = RightSteps;
    u.rightSpeed = RightSpeed;
    u.rightCurrMode = RightCurrMode;

    // Send status updates
    Serial.write( (unsigned char*)&u, sizeof(struct Update) );
  }
}

//--------------------------------------------------------------
// Serial interrupt
//--------------------------------------------------------------
void serialEvent()
{
  char command = Serial.read();

  //--------------------------------------------------------------
  // Directional commands
  //--------------------------------------------------------------
  if(command=='w')  // forward
  {
    unsigned int steps = Serial.parseInt();
    // check for valid steps
    if(steps < 1 || steps > STEPS_IN_ONE_REV)
    {
      Serial.println("?");      
      return;
    }
    LeftCurrMode=0;
    LeftDesiredSteps=steps;
    LeftSteps=0;
    LeftSpeed=0;

    RightCurrMode=0;
    RightDesiredSteps=steps;
    RightSteps=0;
    RightSpeed=0;

    Serial.println(":");
    return;
  }

  if(command=='s')  // reverse
  {
    unsigned int steps = Serial.parseInt();
    // check for valid steps
    if(steps < 1 || steps > STEPS_IN_ONE_REV)
    {
      Serial.println("?");      
      return;
    }
    return;
  }

  if(command=='a')  // left
  {
    unsigned int steps = Serial.parseInt();
    // check for valid steps
    if(steps < 1 || steps > STEPS_IN_ONE_REV)
    {
      Serial.println("?");      
      return;
    }
    return;
  }

  if(command=='d')  // right
  {
    unsigned int steps = Serial.parseInt();
    // check for valid steps
    if(steps < 1 || steps > STEPS_IN_ONE_REV)
    {
      Serial.println("?");      
      return;
    }
    return;
  }
      
  if(command=='q')  // left fwd only
  {
    unsigned int steps = Serial.parseInt();
    // check for valid steps
    if(steps < 1 || steps > STEPS_IN_ONE_REV)
    {
      Serial.println("?");      
      return;
    }
    return;
  }

  if(command=='e')  // right fwd only
  {
    unsigned int steps = Serial.parseInt();
    // check for valid steps
    if(steps < 1 || steps > STEPS_IN_ONE_REV)
    {
      Serial.println("?");      
      return;
    }
    return;
  }

  if(command=='z')  // left rev only
  {
    unsigned int steps = Serial.parseInt();
    // check for valid steps
    if(steps < 1 || steps > STEPS_IN_ONE_REV)
    {
      Serial.println("?");      
      return;
    }
    return;
  }
  
  if(command=='c')  // right rev only
  {
    unsigned int steps = Serial.parseInt();
    // check for valid steps
    if(steps < 1 || steps > STEPS_IN_ONE_REV)
    {
      Serial.println("?");      
      return;
    }
    return;    
  }
      
  if(command=='x')  // stop
  {
    stopLeft();
    stopRight();
    return;    
  }  

  if(command=='v')  // name and version of firmware
  {
    Serial.println(NameVersionStr);
    Serial.println(":");
  }

  if(command=='p')  // Enable streaming of status
  {
      EnableStreaming=1;
  }
  if(command=='o')  // Disable streaming of status
  {
      EnableStreaming=0;
  }

  // Should never return here
  // ? is command unknown
  Serial.println("?");
}

