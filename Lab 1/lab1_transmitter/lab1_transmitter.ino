//Lab 1 Transmitter
//Tayler Wilson, Christopher McCormick, Kyle Johnson, Derek Rafferty

void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
    pinMode(13,OUTPUT);
    pinMode(12,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available())
  {
    char c = (char) Serial.read();
    Serial.println(c);
    if(c == '1')
    {
      digitalWrite(13, HIGH);
      digitalWrite(12, HIGH);
    }
    else if(c=='0')
    {
      digitalWrite(13,LOW);
      digitalWrite(12,LOW);
    }
  }
}
