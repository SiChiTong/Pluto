//--------------------------------------------------------------
// Author: Ashish Choudhari
// Email: choudhariashish@gmail.com
//
//--------------------------------------------------------------
// Platform: Pluto
// Program that runs on DfRobot romeo 1.3 board to control
// left and right motors.
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
//
// Example: w20 -Moves 20 steps forward
//          r40 -Resets speed to 40 
//               (Speed range: 1-63 in both directions)
//--------------------------------------------------------------

#include <SoftwareSerial.h>

SoftwareSerial motor(5,6); // 5-orange, 6-brown

//--------------------------------------------------------------
// 0-127   :   Left motor
// 128-256 :   Right motor
// Center(64, 192) stop respectively
//--------------------------------------------------------------
#define SPDZERO_LEFT     64
#define SPDZERO_RIGHT   192

#define FWD               1
#define REV               0

//--------------------------------------------------------------
// Motor encoder pin configuration
//--------------------------------------------------------------
#define ENC_M_LEFT_A    2     // Encoder A pin for left motor
#define ENC_M_RIGHT_A   3     // Encoder A pin for right motor

#define ENC_M_LEFT_B    8     // Encoder B pin for left motor
#define ENC_M_RIGHT_B  12     // Encoder B pin for right motor

// Encoder steps in one revolution
#define STEPS_IN_ONE_REV    663

//--------------------------------------------------------------
// Standard arduino setup routine
//--------------------------------------------------------------
void setup() 
{
  //------------------------------------------------------------
  // Initialize standard serial to receive commands from host
  Serial.begin(115200);
  Serial.setTimeout(10);
  
  //------------------------------------------------------------  
  // Initialize software serial to send commands to sabertooth
  // controller  
  motor.begin(19200);  
  delay(100);

  //------------------------------------------------------------
  //Initialize encoder requirements
  Serial.println("[INFO]:Initializing encoder interrupts..");
    
  // LEFT motor
  // Encoder pin B as input
  pinMode(ENC_M_LEFT_B, INPUT);

  // Attach interrupt. Gets called everytime a signal is
  // detected
  attachInterrupt(1, leftMotorMovedISR, FALLING);// int.0

  // RIGHT motor
  // Encoder pin B as input
  pinMode(ENC_M_RIGHT_B, INPUT);  

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

unsigned int currLeftSpd  = 30;
unsigned int currRightSpd = 30;
bool trackLeft  = false;
bool trackRight = false;
unsigned int StepsLeft         = 0;
unsigned int StepsRight        = 0;
unsigned int DesiredLeftSteps  = 0;
unsigned int DesiredRightSteps = 0;

//--------------------------------------------------------------
// ISR implementations
//--------------------------------------------------------------
void leftMotorMovedISR()
{
  StepsLeft++;
  if(StepsLeft < DesiredLeftSteps)
  {          
      Serial.print("LS:");
      Serial.print(StepsLeft);
      Serial.println(":");    
  }
  else
  {
    stopLeft();    
  }
}
void rightMotorMovedISR()
{
  StepsRight++;
  if(StepsRight < DesiredRightSteps)
  {          
      Serial.print("RS:");
      Serial.print(StepsRight);
      Serial.println(":");
  }
  else
  {
    stopRight();    
  }
}

//--------------------------------------------------------------
// Arduino standard while loop
//--------------------------------------------------------------
void loop() 
{

  delay(100);
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
    moveLeftFwd(currLeftSpd);
    moveRightFwd(currRightSpd);    
    trackLeft = true;
    trackRight = true;
    DesiredLeftSteps = steps;
    DesiredRightSteps = steps;    
    StepsLeft = 0;
    StepsRight = 0;    
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
    moveLeftRev(currLeftSpd);
    moveRightRev(currRightSpd);    
    trackLeft = true;
    trackRight = true;
    DesiredLeftSteps = steps;
    DesiredRightSteps = steps;    
    StepsLeft = 0;
    StepsRight = 0;    
    Serial.println(":");
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
    trackLeft = true;
    trackRight = true;
    DesiredLeftSteps = steps;
    DesiredRightSteps = steps;    
    StepsLeft = 0;
    StepsRight = 0;    
    moveLeftRev(currLeftSpd);
    moveRightFwd(currRightSpd);    
    Serial.println(":");
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
    moveLeftFwd(currLeftSpd);
    moveRightRev(currRightSpd);    
    trackLeft = true;
    trackRight = true;
    DesiredLeftSteps = steps;
    DesiredRightSteps = steps;    
    StepsLeft = 0;
    StepsRight = 0;    
    Serial.println(":");
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
    moveLeftFwd(currLeftSpd);
    trackLeft = true;
    DesiredLeftSteps = steps;
    StepsLeft = 0;
    Serial.println(":");
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
    moveRightFwd(currRightSpd);
    trackRight = true;
    DesiredRightSteps = steps;
    StepsRight = 0;
    Serial.println(":");
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
    moveLeftRev(currLeftSpd);
    trackLeft = true;
    DesiredLeftSteps = steps;
    StepsLeft = 0;
    Serial.println(":");
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
    moveRightRev(currRightSpd);
    trackRight = true;
    DesiredRightSteps = steps;
    StepsRight = 0;
    Serial.println(":");
    return;    
  }
      
  if(command=='x')  // stop
  {
    stopLeft();
    stopRight();
    Serial.println(":");
    return;    
  }  

  //--------------------------------------------------------------
  // Speed commands
  //--------------------------------------------------------------
  if(command=='r')  // reset speed
  {
    unsigned int spd = Serial.parseInt();
    // check for valid speed value
    if(spd < 1 || spd > 63)
    {
      Serial.println("?");      
      return;
    }
    currLeftSpd = spd;
    currRightSpd = spd;    
    Serial.println(":");
    return;
  }
  if(command=='t')  // reset left speed
  {
    unsigned int spd = Serial.parseInt();
    // check for valid speed value
    if(spd < 1 || spd > 63)
    {
      Serial.println("?");      
      return;
    }
    currLeftSpd = spd;
    Serial.println(":");
    return;
  }  
  if(command=='y')  // reset right speed
  {
    unsigned int spd = Serial.parseInt();
    // check for valid speed value
    if(spd < 1 || spd > 63)
    {
      Serial.println("?");      
      return;
    }
    currLeftSpd = spd;
    Serial.println(":");
    return;
  }  

  // Should never return here
  // ? is command unknown
  Serial.println("?");  
}

