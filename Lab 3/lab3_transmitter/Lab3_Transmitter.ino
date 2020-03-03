void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  pinMode(13, OUTPUT); //LED
  pinMode(12, OUTPUT); //Data
  pinMode(10, OUTPUT); //Clock

  // set idle high
  digitalWrite(12, HIGH); 
  digitalWrite(10, HIGH); 
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available())
  {
    char ch = (char) Serial.read();
    //Serial.print(ch);

    for(int i = 0; i < 8; i++)
    {
      digitalWrite(10, LOW); //clock pulse low
      
      if(((ch<<i) & 128) != 0) //if masked bit is 1
      {
        //Serial.print("1");
        digitalWrite(12, HIGH);
        //digitalWrite(13, HIGH);
      }
      if(((ch<<i) & 128) == 0) //if masked bit is 0
      {
        //Serial.print("0");
        digitalWrite(12, LOW);
        //digitalWrite(13, LOW);
      }

      delayMicroseconds(5); //delay half period

      digitalWrite(10, HIGH); //clock pulse high

      delayMicroseconds(5); //delay half period
      
    }
  }
}
