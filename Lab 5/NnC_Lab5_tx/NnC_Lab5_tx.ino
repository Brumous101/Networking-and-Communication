//Kyle Johnson
//Christopher McCormick
//Derek Rafferty
//Taylor Wilson
//Lab 5 Transmitter
#define DELAY delay(1)

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

  config_tx();  
}
    //Globals
    unsigned char payload[32]; // array for payload data
    //unsigned char status_reg=0; // array to store status reg value.
    static int count =0; // variable to store packet number.
    static int sending=false; // variable to store send state.
    unsigned char ch=0; // variable to store key from serial.

void loop() {
  // put your main code here, to run repeatedly:


    if(Serial.available())
    {
      ch = (char) Serial.read(); //get input from user
    }
  
  

    if(ch=='g')
    {
      sending = true;
      Serial.println("Go!");
      count=0;
      ch=0;
    }
    
    else if(ch=='s')
    {
      sending = false;
      Serial.println("Stop!");
      ch=0;
    }
    
    if(sending==true)
    {
       // increment the count
       // create the message payload by filling in the payload array.
       //   hint: use the sprintf function.
       
      
       sprintf(payload, "CJM: %d", count);
       
       // print the message on the serial console.
       for(int i = 0; i < 32; i++)
       {
        Serial.print( (char) payload[i] );
       }
       Serial.println();
       
       // call the write_payload function to send the payload data.
       write_payload(payload);

       count++;
       
       // delay for 2 seconds.
       delay(2000);

      
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

void write_register(unsigned char reg,unsigned char value)
{
    // set CSN low.
 digitalWrite(8, LOW);
    // send command 0x20 | reg over SPI.
 soft_spi(0x20 | reg);
    // send the value over SPI.
 soft_spi(value);
    // set CSN high.
 digitalWrite(8, HIGH);
    // return
 return;
}

void config_tx(void)
{
 //write a 2 to register 0x00 to put module in tx mode.
 write_register(0x00, 2);
 //write a 3 to register 0x05 to set Rf channel.
 write_register(0x05, 3);
 //write a 0 to register 0x01 to turn off all shockburst stuff
 write_register(0x01, 0);
 //write a 32 to register 0x11 to set the bytes for pipe p0 to 32
 write_register(0x11, 32);
 
 write_tx_register("AHHHH"); //write 5 byte transmit address
 write_rx_address("AHHHH"); //write 5 byte receive address
}

void write_tx_register(const char * ch_add_array)
{
 //set CSN low.
 digitalWrite(8, LOW);
 //send 0x20 | 0x10 over SPI. This is a write starting at 0x10. 
 soft_spi(0x20 | 0x10);
 
 //send ch_add_array[0]over SPI.
 //send ch_add_array[1]over SPI.
 //send ch_add_array[2]over SPI.
 //send ch_add_array[3]over SPI.
 //send ch_add_array[4]over SPI.
 for(int i = 0; i < 5; i++)
 {
  soft_spi(ch_add_array[i]);
 }
 
 digitalWrite(8, HIGH);
 //set CSN high.
}

void write_rx_address(const char * ch_add_array)
{
 //set CSN low.
 digitalWrite(8, LOW);
 //send 0x20 | 0x0A over SPI. This is a write starting at 0x0A.
  soft_spi(0x20 | 0x0A);

 for(int i = 0; i < 5; i++)
 {
  soft_spi(ch_add_array[i]);
 }
 //send ch_add_array[0]over SPI.
 //send ch_add_array[1]over SPI.
 //send ch_add_array[2]over SPI.
 //send ch_add_array[3]over SPI.
 //send ch_add_array[4]over SPI.

 digitalWrite(8, HIGH);
 //set CSN high.
}

void write_payload(unsigned char * payload)
{
 // set CSN low.
 digitalWrite(8, LOW);

 // send command 0xA0 over SPI.
 soft_spi(0xA0);
 
 // Loop here to:
 // Write each of the 32 payload bytes over SPI.
 for(int i = 0; i < 32; i++)
 {
  soft_spi(payload[i]);
 }
 
 // set CSN high.
 digitalWrite(8, HIGH);
}
