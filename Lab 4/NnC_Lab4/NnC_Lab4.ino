//Kyle Johnson
//Christopher McCormick

#define DELAY delay(10)


void setup() {
  Serial.begin(9600);

  pinMode(7, OUTPUT); //CE
  pinMode(8, OUTPUT); //CSN
  pinMode(13, OUTPUT); //SCK
  pinMode(11, OUTPUT); //MOSI
  pinMode(12, INPUT); //MISO

  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(13, LOW);
  digitalWrite(11, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:

  if(Serial.available())
  {
    char ch = (char) Serial.read(); //get input from user
    
    if(ch == 'r' || ch == 'R')
    {
      
      //call function
      for(unsigned char i = 0; i < 23 /*17h*/; i++)// i is register
      {

        Serial.print("Register ");
        Serial.print(i, HEX);
        Serial.print("\t");
        
        if(i == 10/*0Ah*/ || i == 11/*0Bh*/ || i == 16/*10h*/)
        {
          digitalWrite(8, LOW); //slave select low
          soft_spi(i);
          soft_spi_x5(i);
          digitalWrite(8, HIGH); //slave select low
        }
        else
        {
          digitalWrite(8, LOW); //slave select low
          soft_spi(i);
          printAll(soft_spi(i));
          digitalWrite(8, HIGH); //slave select low

        }
        
      }
    }
    else
    {
      Serial.print("Bad input\n");
    }
  }
}

unsigned char soft_spi(unsigned char send_byte) {
   unsigned char recv_byte = 0;
  
   for(unsigned char bitMask = 128; bitMask > 0; bitMask >>=1)
    {
      if(bitMask & send_byte)//if 1
      {
        digitalWrite(11,HIGH);
      }
      else //if zero
      {
        digitalWrite(11,LOW);
      }


      DELAY;
      digitalWrite(13, HIGH);//set SCK HIGH
      

      if(digitalRead(12)) //if high
      {
        recv_byte |= bitMask;
      }


      DELAY;
      digitalWrite(13, LOW);//set SCK LOW   
    }
    
    return recv_byte;
}


void soft_spi_x5(unsigned char ch)
{
  bool first = true;
  for(int j = 0; j < 5; j++)
  {
    if(!first)
    {
      Serial.print("\t\t");
    }
    else
    {
      first = false;
    }
    printAll(soft_spi(00));
  }
}

void printAll(unsigned char ch)
{
  Serial.print(ch, HEX);
  Serial.print("\t");
  Serial.println(ch, BIN);
}
