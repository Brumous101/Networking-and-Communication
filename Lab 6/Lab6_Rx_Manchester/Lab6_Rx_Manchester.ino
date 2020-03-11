#include <time.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(13, INPUT);
}

void loop() {
   bool bitState;// = digitalRead(13);
  unsigned char ch = 0;

   while(digitalRead(13) != LOW)
   {;}

  
  
  //line goes LOW
     unsigned long tStart = millis();
     while(digitalRead(13) == LOW) {;}
     unsigned long tEnd = millis();
  
  //store delay time in t
     unsigned long t = tEnd - tStart;
     double checkTime = (double)t * 1.5;
  
    bitState = true; //high

  for(int i = 0; i < 8; i++)
  {
    
    
    //line is HIGH
    unsigned long tStart2 = millis();
    while(digitalRead(13) == HIGH);
    unsigned long tEnd2 = millis();
    unsigned long timeHigh = tEnd2 - tStart2;
    
    
  
     if(bitState == true) //bitState is high
     {
        if(timeHigh > checkTime ) //2t
        {
          //todo: emit a 0
          Serial.print("0");
          ch<<=1;
          
          bitState = false; //low
        }
        else //1t
        {
          //todo: emit a 1
          Serial.print("1");
          ch<<=1;
          ch = ch|1;
          
        }
     }
     else //bitState is low
     {
        if(timeHigh > checkTime ) //2t
        {
          //todo: emit a 1
          Serial.print("1");
          ch<<=1;
          ch = ch|1;
          
          bitState = true; //high
        }
        else //1t
        {
          //todo: emit a 0
          Serial.print("0");
          ch<<=1;
        }
     }

  
  while(digitalRead(13) == LOW) {;}
  }//end of for loop

  Serial.print(" - ");
  Serial.print((char)ch);
  Serial.print(" - ");
  Serial.print(ch, BIN);
  Serial.println();
  
}
