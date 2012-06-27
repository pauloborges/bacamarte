int first_pad = A0;
int last_pad = A5;
int value;

void setup()
{
  Serial.begin(38400);
}

void loop()
{
  for (int pad = first_pad; pad <= last_pad; pad++)
  {
    value = analogRead(pad);
    Serial.print(pad-first_pad);
    Serial.print(',');
    Serial.println(value);
  }
}
