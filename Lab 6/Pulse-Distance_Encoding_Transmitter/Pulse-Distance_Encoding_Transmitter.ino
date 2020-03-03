//THIS IS THE TRANSMITTER CODE FOR THE SELF-CLOCKING SYNCHRONOUS SERIAL COMMUNICATION
//Christopher McCorkmick
//Kyle Johnson
//Derek Rafferty
#define DELAY delay(100)
/*
Transmitter
Setup:
1. Configure the serial connection to the PC to run at 9600bps.
2. Configure a GPIO port pin to act as a data/clock output.
3. Set the output data/clock pin to be initially in an idle state of HIGH.

Loop:
1. Read a key from the serial interface from the PC.
2. Send all 8 bits of the character, one bit at a time, using pulse-distance encoding as
described in the lecture. Note: a 1 should be 1t time-period low followed by 3t high, 0
should be 1t time-period low followed by 1t time-period high.
3. Once the message is complete, send a low-pulse of 3t.
4. Be sure to return the lines to the idle state after the character has been sent.
Note: Set the time-period of 100ms for initial testing. 
 */
void setup() 
{
  Serial.begin(9600);
  pinMode(13, OUTPUT);    //Clock Pulse & Data
  digitalWrite(13, HIGH);
  Serial.println("Ready");
}
  
void loop() 
{
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
   for(unsigned char bitMask = 128; bitMask > 0; bitMask >>=1)
   {
      if(bitMask & ch)//if 1
      {
        digitalWrite(13,LOW);
        DELAY;
        digitalWrite(13,HIGH);
        DELAY;
        DELAY;
        DELAY;
      }
      else //if zero
      {
        digitalWrite(13,LOW);
        DELAY;
        digitalWrite(13,HIGH);
        DELAY;
      }
   }
   digitalWrite(13,LOW);
   DELAY;
   DELAY;
   DELAY;
   digitalWrite(13,HIGH);//idle high
}
