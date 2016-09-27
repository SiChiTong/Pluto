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
//--------------------------------------------------------------


#define NAME    "Sabertooth Motor Drive"
#define VERSION "pluto-0.0.1"

//--------------------------------------------------------------
// Standard arduino setup routine
//--------------------------------------------------------------
void setup() 
{
  //------------------------------------------------------------
  // Initialize standard serial to receive commands from host
  Serial.begin(115200);
  Serial.setTimeout(10);
  
  //Initialize encoder requirements
  Serial.println("[INFO]:Initializing encoder pins..");
    
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
//--------------------------------------------------------------
}

void loop() 
{
  digitalWrite(2, HIGH);
  delay(1000);
  digitalWrite(2, LOW);
  delay(1000);
  
  digitalWrite(3, HIGH);
  delay(1000);
  digitalWrite(3, LOW);
  delay(1000);
  
  digitalWrite(4, HIGH);
  delay(1000);
  digitalWrite(4, LOW);
  delay(1000);
  
  digitalWrite(5, HIGH);
  delay(1000);
  digitalWrite(5, LOW);
  delay(1000);
}

//--------------------------------------------------------------
// Serial interrupt
//--------------------------------------------------------------
void serialEvent()
{
  char command = Serial.read();

  if(command=='y')  // reset right speed
  {
    return;
  }
}  
