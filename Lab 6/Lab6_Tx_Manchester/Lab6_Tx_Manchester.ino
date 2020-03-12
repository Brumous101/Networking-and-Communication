#define DELAY delayMicroseconds(50)
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(13, OUTPUT);    //Clock Pulse & Data
  digitalWrite(13, HIGH);
  Serial.println("Ready");
}

void loop() {
    unsigned char ch = 0; // variable to store key from serial.
    if(Serial.available())
    {
      ch = (char) Serial.read(); //get input from user
    }
    if(ch)//there is a message
    {
      send_serial(ch);
    }
}

unsigned char send_serial(unsigned char ch) 
{
  //send a preamble bit
  
  digitalWrite(13,LOW);
  DELAY;
  digitalWrite(13,HIGH);
  DELAY;

  //send 8 bits of character
  for(unsigned char bitMask = 128; bitMask > 0; bitMask >>=1)
   {
      if(bitMask & ch)//if 1
      {
        //Serial.print("1");
        digitalWrite(13,LOW);
        DELAY;
        digitalWrite(13,HIGH);
        DELAY;
      }
      else //if zero
      {
        //Serial.print("0");
        digitalWrite(13,HIGH);
        DELAY;
        digitalWrite(13,LOW);
        DELAY;
      }
   }
   //Serial.println();
   Serial.print(char(ch));
  
   //return line to idle
   digitalWrite(13,HIGH);
   DELAY;
}
