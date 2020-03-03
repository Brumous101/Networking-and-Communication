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
}

void loop() 
{
  if(digitalRead(12) == HIGH)
  {
    Serial.println("HIGH");       //if byte is 1, write high
    digitalWrite(13, HIGH);       //pin13 is the LED pin
  }

  if (digitalRead(12) == LOW)
  {
    Serial.println("LOW");    // if byte is 0, write low
    digitalWrite(13, LOW);
  }
}
