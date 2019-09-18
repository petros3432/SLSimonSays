int i;
int check=0;
int oldcheck=0;

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  for(i=3;i<=7;++i) pinMode(i, INPUT_PULLUP);
}

void loop() {
  check=0;
  for(i=3;i<=7;++i)
    if(digitalRead(i)==LOW) check=i;
    
  if(check>0) digitalWrite(13, HIGH);
  else digitalWrite(13, LOW);
  
  if(oldcheck!=check)
  {
    switch(check)
    {
      case  3: Serial.print("R"); break;
      case  4: Serial.print("G"); break;
      case  5: Serial.print("S"); break;
      case  6: Serial.print("B"); break;      
      case  7: Serial.print("Y"); break;
    }
    oldcheck=check;
  }
  delay(10);
} 
