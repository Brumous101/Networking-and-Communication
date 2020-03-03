//THIS IS THE RECEIVER CODE FOR THE SYNCHRONOUS SERIAL COMMUNICATION
//Christopher McCorkmick
//Kyle Johnson
//Tayler Wilson
//Derek Rafferty

//10 will be our clock so need to wait for 1 


void setup() 
{
  Serial.begin(9600);
  pinMode(10, INPUT);     //Clock Pulse
  pinMode(12, INPUT);     //SERIAL INPUT DATA
  pinMode(13, OUTPUT);    //LED
  Serial.println("Ready");
}

void loop() 
{
  char bit_in_question =0, ch = 0;
  /*Serial.print(digitalRead(10));
  Serial.print(" ");
  Serial.println(digitalRead(12));
  */
  
  for(int i =0; i <8;i++)
  {
      //Serial.println("0");
    
      while(digitalRead(10) != LOW)
      {
        ; //Serial.println("1");
      }
      while(digitalRead(10) != HIGH)
      {
        ; //Serial.println("2");
      }  
      bit_in_question=digitalRead(12);
      ch<<=1;
      ch=ch|bit_in_question;
      //Serial.println(bit_in_question);
  }
  Serial.print(ch);
}
