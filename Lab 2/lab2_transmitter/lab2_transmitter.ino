//Lab 2 this is Trasmitter code
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(13,OUTPUT);
  pinMode(12,OUTPUT); 
  digitalWrite(12, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available())
  {
    char ch =(char) Serial.read();
   // Serial.println(ch);


    digitalWrite(12, LOW); //start bit
    digitalWrite(13, LOW);
    delayMicroseconds(208);
    
    for(int i = 0; i < 8; i++)
    {
      if(((ch<<i)& 128) != 0) //if the masked input bit is 1
      {
        // Serial.print("1");
        digitalWrite(12, HIGH);
        digitalWrite(13, HIGH);
      }
      else //if the masked input bit is 0
      {
        // Serial.print("0");
        digitalWrite(12, LOW);
        digitalWrite(13, LOW);
      }
     
      delayMicroseconds(208);
      
    }

      
    digitalWrite(12, HIGH); //end bit
    digitalWrite(13, HIGH);
    delayMicroseconds(208);
  }
}

//delayMicroseconds(500);
