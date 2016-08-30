void setup() {
  Serial.begin(115200);
  Serial.println("Initializing sensors");
  Serial.println("analog   -0,1,2,3,4");
  Serial.println("digital  -4,8,12");
  Serial.println("done..");  
}

bool enable = false;

void loop() {

  if(enable)
  {
    int v0 = analogRead(0);
    delay(1);  
    int v1 = analogRead(1);
    delay(1);
  
    int v2 = analogRead(2);
    delay(1);
    int v3 = analogRead(3);
    delay(1);
    int v4 = analogRead(4);
    delay(1);
  
    Serial.print(" ");
    Serial.print(v0);
  
    Serial.print(" ");
    Serial.print(v1);
  
    Serial.print(" ");
    Serial.print(v2);
    
    Serial.print(" ");
    Serial.print(v3);
    
    Serial.print(" ");
    Serial.println(v4);
  
    delay(200);
  }
}

//--------------------------------------------------------------
// Serial interrupt
//--------------------------------------------------------------
void serialEvent()
{
  char command = Serial.read();
  if(command=='e')
  {
    enable = true;
    Serial.println(":");
    return;
  }
  if(command=='d')
  {
    enable = false;
    Serial.println(":");
    return;    
  }
  Serial.println("?");
  return;
}

