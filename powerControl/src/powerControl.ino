//--------------------------------------------------------------
// Author: Ashish Choudhari
// Email: choudhariashish@gmail.com
//
//--------------------------------------------------------------
// Platform: Pluto
// Controls relays to switch subsystem power.
//--------------------------------------------------------------
//
// Usage:
//
// Serial commands at 115200:
//
// s -Get power status (0000 -> 1,2,3,4)
// u -1 power off
// i -2 power off
// o -3 power off
// p -4 power off
// h -1 power on
// j -2 power on
// k -3 power on
// l -4 power on
//--------------------------------------------------------------


#define NAME    "Power Control System"
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
  Serial.println("[INFO]:Initializing power relay inputs..");
  Serial.println("[INFO]:Power at relay 4 is normally enabled");
    
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
//--------------------------------------------------------------
}


//--------------------------------------------------------------
// runDemo()
//--------------------------------------------------------------
void runDemo() 
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
// loop()
//--------------------------------------------------------------
void loop()
{
}

//--------------------------------------------------------------
// Serial interrupt
//--------------------------------------------------------------
void serialEvent()
{
  char command = Serial.read();

  if(command=='d')  // run demo
  {
    for(int i=0; i<1; i++)
    {
      runDemo();
    }
    Serial.println(":");
    return;
  }
  // Get status
  if(command=='s')
  {
    for(int i=2; i<=5; i++)
    {
      Serial.print(digitalRead(i));
    }
    Serial.println(":");
    return;
  }
  if(command=='u') // power 1 off
  {
    digitalWrite(2,HIGH);
    Serial.println(":");
    return;
  }
  if(command=='h') // power 1 on
  {
    digitalWrite(2,LOW);
    Serial.println(":");
    return;
  }
  if(command=='i') // power 2 off
  {
    digitalWrite(3,HIGH);
    Serial.println(":");
    return;
  }
  if(command=='j') // power 2 on
  {
    digitalWrite(3,LOW);
    Serial.println(":");
    return;
  }
  if(command=='o') // power 3 off
  {
    digitalWrite(4,HIGH);
    Serial.println(":");
    return;
  }
  if(command=='k') // power 3 on
  {
    digitalWrite(4,LOW);
    Serial.println(":");
    return;
  }
  if(command=='p') // power 4 off
  {
    digitalWrite(5,HIGH);
    Serial.println(":");
    return;
  }
  if(command=='l') // power 4 on
  {
    digitalWrite(5,LOW);
    Serial.println(":");
    return;
  }
  if(command=='h') // get help
  {
    Serial.println("u,i,o,p -1,2,3,4 power off");
    Serial.println("h,j,k,l -1,2,3,4 power on");
    Serial.println("s       -Get power status");
    Serial.println("d       -Demo power switching");
    Serial.println(":");
    return;
  }
  Serial.println("?");
}  
