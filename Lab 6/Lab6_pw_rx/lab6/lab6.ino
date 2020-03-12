

void setup() {
  Serial.begin(9600);
  pinMode(13, INPUT);
  Serial.println("Ready");
}


void loop() {
  int logic;
  unsigned long pulse, pulse2;
  unsigned long t, t1, t2, pTotal;
  unsigned long p1, p2, p3, p4;
  int x = 0;
  unsigned char mess = 0;
//  Serial.println("NOT INSIDE YET");

  if(digitalRead(13) == LOW){
    t1 = micros();
    while(digitalRead(13) == LOW){
      ;
    }
    t2 = micros();
    t = t2 - t1;
    
    //////////
    
    while(x < 8){
      if(digitalRead(13) == HIGH){
          //Serial.println("INPUT BIT HIGH");
          p1 = micros();
          while(digitalRead(13) == HIGH){
            //Serial.println("STILL HIGH");
            ;
          }
          p2 = micros();
          pulse = p2 - p1;

          
          if(pulse > (2*t)){
            logic = 1;    
            //Serial.print("1 - ");
          }else{
            logic = 0;
            //Serial.print("0 - ");
          }
            
          
          x++;
          mess <<= 1; 
          mess = (mess | logic); 
          //Serial.println(mess, BIN);

          
            
      }
      if(digitalRead(13) == LOW){
          //Serial.println("INPUT BIT LOW");
          p3 = micros();
          while(digitalRead(13) == LOW){
           // Serial.println("STILL LOW");
            ;
          }
          p4 = micros();
          pulse2 = p4 - p3;
      }
      if(pulse2 > (2 * t)){
        x = 0;
        break;
      }
    }
    //Serial.print(" - MESSAGE: ");
    Serial.print((char)mess);
    mess = 0; 
    x = 0;
  }  
}
