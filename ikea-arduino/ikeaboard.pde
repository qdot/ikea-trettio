int state = 0;
int index = 0;
int val = 0;

void setup()
{
  Serial.begin(9600);
  analogWrite(9, 255);
  analogWrite(10, 0);
  analogWrite(11, 0);
  analogWrite(12, 0);
}

void loop()
{
  
  if(Serial.available()) {
    val = Serial.read();
    if(val == 0)
    {
      state = 0;
      return;
    }
    if(state == 0)
    {
      index = val;
      state = 1;
      return;
    }
    else
    {
      analogWrite(8 + index, val);
      state = 0;
      return;
    }
  }
  
}
