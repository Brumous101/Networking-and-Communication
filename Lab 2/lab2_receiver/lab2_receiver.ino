//THIS IS THE RECEIVER CODE
//Christopher McCorkmick
//Kyle Johnson
//Tayler Wilson
//Derek Rafferty



void setup() 
{
  Serial.begin(9600);     //Boud Rate
  pinMode(12, INPUT);     //SERIAL INPUT
  pinMode(13, OUTPUT);    //LED
  Serial.println("Ready");
}

void loop() 
{
  char receiving = 0, bit_in_question =0, ch = 0;
  if(digitalRead(12) == LOW)
  {
      receiving = 1;
      delayMicroseconds(312);
  }
  if(receiving)
  {
      for(int i =0; i <8; i++)
      {
        bit_in_question=digitalRead(12);
        ch<<=1;
        ch=ch|bit_in_question;
        delayMicroseconds(208);
        //Serial.println((int)bit_in_question);
      }
      if(ch == 0 && digitalRead(12) ==LOW)
      {
        Serial.println("Disconnected");
      }
      Serial.println(ch);
      receiving =0;
  }
}
