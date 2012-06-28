int first_pad = A0;
int last_pad = A7;
int value;

int PIN_LED = 2;
int PIN_BUTTON = 3;
int state, last_state, last_change_time, current_time;
int debounce_time = 10;
int do_not_refresh_this_time;

int threshold = 400;
int window = 30;
int last_value[8] = {0, 0, 0, 0, 0, 0, 0, 0};
unsigned int current_pos[8] = {0, 0, 0, 0, 0, 0, 0, 0};
unsigned int last_trigger_pos[8] = {0, 0, 0, 0, 0, 0, 0, 0};

void setup()
{
  Serial.begin(38400);
  
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_BUTTON, INPUT);
  
  state = last_state = LOW;
  digitalWrite(PIN_LED, LOW);
  
  last_change_time = millis();
  
  do_not_refresh_this_time = 0;
}

void loop()
{
  do_not_refresh_this_time = 0;
  state = digitalRead(PIN_BUTTON);
  current_time = millis();
  if (state != last_state && current_time - last_change_time >= debounce_time)
  {
    digitalWrite(PIN_LED, state);
    last_state = state;
    last_change_time = current_time;
    
    do_not_refresh_this_time = 1;
    
    if (state == LOW)
    {
      Serial.end();
      Serial.begin(38400);
    }
    
    else
    {
      Serial.end();
      Serial.begin(57600); 
    }
  }
  
  
  if (!do_not_refresh_this_time)
  {
    if (state == LOW)
    {
      for (int pad = first_pad; pad <= last_pad; pad++)
      {
        value = analogRead(pad);
        Serial.print(pad-first_pad);
        Serial.print(',');
        Serial.println(value);
      }
    }
    
    else
    {
      for (int pad = first_pad; pad <= last_pad; pad++)
      {
        value = analogRead(pad);
        int p = pad - first_pad;
        current_pos[p]++;
        
        if (value >= threshold && last_value[p] < threshold && current_pos[p] - last_trigger_pos[p] > window)
        {
           last_trigger_pos[p] = current_pos[p];
           Serial.print(p);
           Serial.print(',');
           Serial.print(value);
           Serial.println();
        }
        
        last_value[p] = value;
      }
    }
  }
}
