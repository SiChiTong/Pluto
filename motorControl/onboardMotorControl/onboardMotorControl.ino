//--------------------------------------------------------------
// Author: Ashish Choudhari
// Email: choudhariashish@gmail.com
//
//--------------------------------------------------------------
// Platform: Pluto
// Program that runs on DfRobot romeo 1.3 board to control
// left and right motors.
//--------------------------------------------------------------

//--------------------------------------------------------------
//Standard PWM DC control
//--------------------------------------------------------------
#define LEFT_MOTOR    0
#define RIGHT_MOTOR   0

#define CURR_ADVANCE  0
#define CURR_BACKOFF  1

#define SPD_M_LEFT    6     // M left Speed Control
#define SPD_M_RIGHT   5     // M right Speed Control
#define DIR_M_LEFT    7     // M left Direction Control
#define DIR_M_RIGHT   4     // M right Direction Control

//--------------------------------------------------------------
// Motor encoder pin configuration
//--------------------------------------------------------------
#define ENC_M_LEFT_A    2     // Encoder A pin for left motor
#define ENC_M_RIGHT_A   3     // Encoder A pin for right motor

#define ENC_M_LEFT_B    8     // Encoder B pin for left motor
#define ENC_M_RIGHT_B  12     // Encoder B pin for right motor

//--------------------------------------------------------------
// Standard arduino setup routine
//--------------------------------------------------------------
void setup(void) 
{ 
  //------------------------------------------------------------
  // Configure all required pwm control pins to be output
  for(int i=4;i<=7;i++)
  {
      pinMode(i, OUTPUT);  
  }
  //Initialize serial port  
  Serial.begin(115200);
  Serial.setTimeout(10);
  Serial.println("[INFO]:Initialized serial console");
  
  //------------------------------------------------------------
  //Initialize encoder requirements
  Serial.println("[INFO]:Initializing encoder interrupts..");

  // LEFT motor
  // Encoder pin B as input
  pinMode(ENC_M_LEFT_B, INPUT);

  // Attach interrupt. Gets called everytime a signal is
  // detected
  attachInterrupt(0, leftMotorMovedISR, FALLING);// int.0

  // RIGHT motor
  // Encoder pin B as input
  pinMode(ENC_M_RIGHT_B, INPUT);  

  // Attach interrupt. Gets called everytime a signal is
  // detected
  attachInterrupt(1, rightMotorMovedISR, FALLING);// int.1
  Serial.println("[INFO]:done"); 
}

volatile unsigned int LeftMPos       = 0;
volatile unsigned int RightMPos      = 0;
volatile unsigned int TargetPosLeft  = 0;
volatile unsigned int TargetPosRight = 0;
volatile bool trackLeft  = false;
volatile bool trackRight = false;
volatile unsigned int temp = 1;  // 663:steps/rev
volatile unsigned spd = 100;
volatile bool LeftCurrDir  = CURR_ADVANCE;
volatile bool RightCurrDir = CURR_ADVANCE;

//--------------------------------------------------------------
// Standard arduino loop routine
//--------------------------------------------------------------
void loop()
{
  if(trackLeft)
  {
    if(LeftMPos > TargetPosLeft)
    {
      stopMotors(LEFT_MOTOR);
      LeftMPos = 0;
      TargetPosLeft = 0;
      trackLeft = false;
      Serial.println("LIDLE");
    }
    else
    {
      analogWrite (SPD_M_LEFT,spd);
      Serial.print(LeftMPos);
      if(LeftCurrDir == CURR_BACKOFF)
      {
        Serial.print(":B:");              
      }
      else
      {
        Serial.print(":A:");        
      }
      Serial.println("LDONE");
    }
  }
  if(trackRight)
  {
    if(RightMPos > TargetPosRight)
    {
      stopMotors(RIGHT_MOTOR);
      RightMPos = 0;
      TargetPosRight = 0;
      trackRight = false;
      Serial.println("RIDLE");      
    }
    else
    {
      analogWrite (SPD_M_RIGHT,spd);      
      Serial.print(RightMPos);
      if(RightCurrDir == CURR_BACKOFF)
      {
        Serial.print(":B:");              
      }
      else
      {
        Serial.print(":A:");        
      }
      Serial.println("RDONE");
    }    
  }
}

//--------------------------------------------------------------
// stopMotors()
// Stops motor
//--------------------------------------------------------------
void stopMotors(bool motor)
{
  if(motor == LEFT_MOTOR)
  {
    digitalWrite(SPD_M_LEFT,LOW);   
  }
  if(motor == RIGHT_MOTOR)
  {    
    digitalWrite(SPD_M_RIGHT,LOW);      
  }
}

//--------------------------------------------------------------
// turn_L()
// Turns left
//--------------------------------------------------------------
void turn_L (char a,char b)
{
  analogWrite (SPD_M_LEFT,a);
  digitalWrite(DIR_M_LEFT,HIGH);    
  analogWrite (SPD_M_RIGHT,b);    
  digitalWrite(DIR_M_RIGHT,LOW);
}

//--------------------------------------------------------------
// turn_R()
// Turns right
//--------------------------------------------------------------
void turn_R (char a,char b)
{
  analogWrite (SPD_M_LEFT,a);
  digitalWrite(DIR_M_LEFT,LOW);    
  analogWrite (SPD_M_RIGHT,b);    
  digitalWrite(DIR_M_RIGHT,HIGH);
}

//--------------------------------------------------------------
// turn_L_only_advance()
// Advances left motor only
//--------------------------------------------------------------
void turn_L_only_advance(char a)
{
  analogWrite (SPD_M_LEFT,a);
  digitalWrite(DIR_M_LEFT,LOW);    
}

//--------------------------------------------------------------
// turn_L_only_backoff()
// Backsoff left motor only
//--------------------------------------------------------------
void turn_L_only_backoff(char a)
{
  analogWrite (SPD_M_LEFT,a);
  digitalWrite(DIR_M_LEFT,HIGH);    
}

//--------------------------------------------------------------
// turn_R_only_advance()
// Advances right motor only
//--------------------------------------------------------------
void turn_R_only_advance(char a)
{
  analogWrite (SPD_M_RIGHT,a);
  digitalWrite(DIR_M_RIGHT,LOW);
}

//--------------------------------------------------------------
// turn_R_only_backoff()
// Backsoff right motor only
//--------------------------------------------------------------
void turn_R_only_backoff(char a)
{
  analogWrite (SPD_M_RIGHT,a);
  digitalWrite(DIR_M_RIGHT,HIGH);
}

//--------------------------------------------------------------
// advance()
// Advances both motors in forward direction
//--------------------------------------------------------------
void advance(char a,char b)
{
  analogWrite (SPD_M_LEFT,a);
  digitalWrite(DIR_M_LEFT,LOW);    
  analogWrite (SPD_M_RIGHT,b);
  digitalWrite(DIR_M_RIGHT,LOW);
}

//--------------------------------------------------------------
// backoff()
// backsoff both motors
//--------------------------------------------------------------
void backoff(char a,char b)
{
  analogWrite (SPD_M_LEFT,a);
  digitalWrite(DIR_M_LEFT,HIGH);    
  analogWrite (SPD_M_RIGHT,b);
  digitalWrite(DIR_M_RIGHT,HIGH);
}

void serialEvent()
{  
  char command = Serial.read();
  if(command == 'r')
  {
    int spdInpt = Serial.parseInt();
    if(spdInpt >= 0 && spdInpt <= 255)
    {
      spd = spdInpt;
      Serial.print(spd);
    }
    else
    {
      return;
    }
  }
  else
  if(command == 'f')
  {
    int target = Serial.parseInt();
    if(target >= 1 && target <= 663)
    {
      temp = target;
      Serial.print(temp);
    }
    else
    {
      return;
    }
  }
  else
  if(command == 'w')
  {
    TargetPosLeft = temp;    
    TargetPosRight = temp;    
    LeftMPos = 0;
    RightMPos = 0;    
    trackLeft = true;
    trackRight = true;    
    advance(spd, spd);
  }
  else
  if(command == 's')
  {
    TargetPosLeft = temp;    
    TargetPosRight = temp; 
    LeftMPos = 0;
    RightMPos = 0;        
    trackLeft = true;
    trackRight = true;    
    backoff(spd, spd); 
  }
  else  
  if(command == 'a')
  {
    TargetPosLeft = temp;    
    TargetPosRight = temp;    
    LeftMPos = 0;
    RightMPos = 0;    
    trackLeft = true;
    trackRight = true;    
    turn_L(spd, spd);
  }
  else  
  if(command == 'd')
  {
    TargetPosLeft = temp;    
    TargetPosRight = temp; 
    LeftMPos = 0;
    RightMPos = 0;        
    trackLeft = true;
    trackRight = true;    
    turn_R(spd, spd); 
  }
  else  
  if(command == 'q')
  {
    TargetPosLeft = temp;
    LeftMPos = 0;
    trackLeft = true;
    turn_L_only_advance(spd);
  }
  else  
  if(command == 'e')
  {
    TargetPosRight = temp;
    RightMPos = 0;
    trackRight = true;    
    turn_R_only_advance(spd);
  }
  else  
  if(command == 'z')
  {
    TargetPosLeft = temp;
    LeftMPos = 0;
    trackLeft = true;
    turn_L_only_backoff(spd);
  }
  else  
  if(command == 'c')
  {
    TargetPosRight = temp;
    RightMPos = 0;
    trackRight = true;    
    turn_R_only_backoff(spd);
  }
  else  
  if(command == 'x')
  {
    TargetPosLeft  = 0;
    TargetPosRight = 0;
    LeftMPos = 0;
    RightMPos = 0;
    trackLeft = false;
    trackRight = false;        
    stopMotors(LEFT_MOTOR);
    stopMotors(RIGHT_MOTOR);    
  }
  else
  {
    return;
  }
  Serial.println(':');
  Serial.flush();
}

void leftMotorMovedISR()
{
  LeftMPos++;
  LeftCurrDir = digitalRead(ENC_M_LEFT_B);
}

void rightMotorMovedISR()
{
  RightMPos++;
  RightCurrDir = digitalRead(ENC_M_RIGHT_B);  
}
