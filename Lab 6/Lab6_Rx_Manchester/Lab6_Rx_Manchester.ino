#include <time.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(13, INPUT);
  Serial.println("Ready");
}

void loop() {
   int state = 0;// = digitalRead(13);
  unsigned char ch = 0;
  
   

   while(digitalRead(13) != LOW)
   {;}

  
  
  //line goes LOW
     unsigned long tStart = micros();
     while(digitalRead(13) == LOW) {;}
     unsigned long tEnd = micros();
     unsigned long timeHigh, timeLow;
  
  //store delay time in t
     unsigned long t = tEnd - tStart; //t was found with the total time preamble was low
     double checkTime = (double)t * 1.5;
  
  for(int i = 0; i < 8;)
  {
    switch(state)
    {
      //Flips the bit
      case 0://You just had a one 
        tStart = micros();
        while(digitalRead(13) == HIGH);
          tEnd = micros();
        timeHigh = tEnd - tStart;
        
        if(timeHigh >= checkTime) //time High is high for 2 unit ts
        {
          state = 2;
          //Serial.print("0");
          ch<<=1;
          //ch=ch|0;
          i++;
        }
        else//1 t
        {
          state = 1;
        }
        
        break;
        
      case 1:
        //Serial.print("1");
        ch<<=1;
        ch=ch|1;
        state = 0;
        i++;
        while(digitalRead(13) == LOW)
          {;}
        break;
        
      //Flips the bit
      case 2:
        tStart = micros();
        while(digitalRead(13) == LOW);
          tEnd = micros();
        timeLow = tEnd - tStart;
        if(timeLow >= checkTime) //time Low is low for 2 unit ts
        {
          state = 0;
          //Serial.print("1");
          ch<<=1;
          ch=ch|1;
          i++;
        }
        else//1 t
        {
          state = 3;
        }
        
        break;
        
      case 3:
        //Serial.print("0");
        ch<<=1;
        i++;
        state = 2;
        while(digitalRead(13) == HIGH)
          {;}
        break;
    }
  }//end of for loop
while(digitalRead(13) == LOW) {;}
  
  //Serial.print(" - ");
  Serial.print((char)ch);
  //Serial.print(" - ");
  //Serial.print(ch, BIN);
  //Serial.println((char)ch);
  
}
