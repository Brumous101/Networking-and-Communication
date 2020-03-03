//Kyle Johnson
//Christopher McCormick
//Derek Rafferty
//Lab 5 Receiver
char ch;
#define CE 7
#define CSN 9
#define SCK 13
#define MOSI 11
#define MISO 12
#define DELAY delay(1)

void config_rx(void)
{
  write_register(0x00, 3);
  write_register(0x05, 3);
  write_register(0x01, 0);
  write_register(0x11, 32);
  write_tx_register("AHHHH");
  write_rx_address("AHHHH");
}

unsigned char read_register(unsigned char reg)
{
 unsigned char retval;
 digitalWrite(CSN, LOW);
 soft_spi(reg);
 retval = soft_spi(0);
 digitalWrite(CSN, HIGH);
 return retval;
}

void write_tx_register(const char * ch_add_array)
{
  digitalWrite(CSN, LOW);
  soft_spi(0x20 | 0x10);
  soft_spi(ch_add_array[0]);
  soft_spi(ch_add_array[1]);
  soft_spi(ch_add_array[2]);
  soft_spi(ch_add_array[3]);
  soft_spi(ch_add_array[4]);
  digitalWrite(CSN, HIGH);
}

void write_rx_address(const char * ch_add_array)
{
  digitalWrite(CSN, LOW);
  soft_spi(0x20 | 0x0A);
  soft_spi(ch_add_array[0]);
  soft_spi(ch_add_array[1]);
  soft_spi(ch_add_array[2]);
  soft_spi(ch_add_array[3]);
  soft_spi(ch_add_array[4]);
  digitalWrite(CSN, HIGH);
}

void read_payload(unsigned char * payload)
{
  digitalWrite(CSN, LOW);
  soft_spi(0x61);
  for(int i = 0; i <= 32; i++)
  {
    payload[i] = soft_spi(0);
  }
  digitalWrite(CSN, HIGH);

 // Loop here to:
 // Read each of the 32 payload bytes from SPI.
}

void write_register(unsigned char reg,unsigned char value)
{
  digitalWrite(CSN, LOW);
  soft_spi(0x20 | reg);
  soft_spi(value);
  digitalWrite(CSN, HIGH);
}


unsigned char soft_spi(unsigned char send_byte) {
   unsigned char recv_byte = 0;
   for(unsigned char bitMask = 128; bitMask > 0; bitMask >>=1)
    {
      if(bitMask & send_byte)//if 1
      {
        digitalWrite(MOSI,HIGH);
      }
      else //if zero
      {
        digitalWrite(MOSI,LOW);
      }


      DELAY;
      digitalWrite(SCK, HIGH);//set SCK HIGH
      

      if(digitalRead(MISO)) //if high
      {
        recv_byte |= bitMask;
      }


      DELAY;
      digitalWrite(SCK, LOW);//set SCK LOW   
    }
    
    return recv_byte;
}



void setup() {
  //local serial port setup
  Serial.begin(9600);
  pinMode(SCK, OUTPUT);  //13
  pinMode(MOSI, OUTPUT);  //11
  pinMode(CSN, OUTPUT);  //9
  pinMode(CE, OUTPUT);  //7
  pinMode(MISO, INPUT);  //12 
  digitalWrite(SCK, LOW);   //Setting clock low initially???
  digitalWrite(MOSI, HIGH);
  digitalWrite(CSN, HIGH);
  digitalWrite(CE, HIGH);
  config_rx();

}

void loop() {
 unsigned char payload[32]; // array for payload data
 unsigned char status_reg=0; // array to store status reg value.
 static int count=0; // variable to store packet number.
 static int listening=false; // variable to store listen state.
 unsigned char ch=0; // variable to store key from serial.
 
 if(Serial.available()) ch=Serial.read();
 if(ch=='g')
 {
    listening=true;
    Serial.println("Listener Go!");
    count=0;
 }
 else if(ch=='s')
 {
    listening=false;
    Serial.println("Listener Stop!");
 }
 if(listening==true)
 {
  char reg = read_register(0x17);
  if((reg & 1) == 0){
      read_payload(payload);
      //print the message to console
      
      for(int i = 0; i <= 7; i++)
      {
        Serial.print((char)payload[i]);
      }
      status_reg = 0x40;
      Serial.println();
    }  
  } 
}
