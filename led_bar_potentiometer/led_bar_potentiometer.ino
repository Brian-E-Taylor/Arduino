const int analogPin = A0;
const int ledCount = 9;

int red = 0;
int redDir = 0;
int green = 0;
int greenDir = 0;
int blue = 0;
int blueDir = 0;

int ledPins[] = { 2, 3, 4, 5, 6, 7, 9, 10, 11 };

void setup()
{
  for (int thisLed = 0; thisLed < ledCount - 1; thisLed++)
  {
    pinMode(ledPins[thisLed], OUTPUT);
  }
}

void loop()
{
  int sensorReading = analogRead(analogPin);
  int ledLevel = map(sensorReading, 0, 1000, 0, ledCount);
  
  for (int thisLed = 0; thisLed < ledCount; thisLed++)
  {
    if (thisLed < ledLevel)
    {
      /*
      if (ledLevel >= 6 && thisLed == 6)
      {
        digitalWrite(ledPins[thisLed], HIGH);
        delay(18000 / (ledLevel * ledLevel * ledLevel));
        digitalWrite(ledPins[thisLed], LOW);
        digitalWrite(ledPins[thisLed+1], HIGH);
        delay(18000 / (ledLevel * ledLevel * ledLevel));
        digitalWrite(ledPins[thisLed+1], LOW);
        digitalWrite(ledPins[thisLed+2], HIGH);
        delay(18000 / (ledLevel * ledLevel * ledLevel));
        digitalWrite(ledPins[thisLed+2], LOW);
      }
      */
      if (ledLevel >= 6 && thisLed >= 6)
      {
        if (thisLed == 6 && ledLevel == 7)
        {
          if (redDir == 0)
          {
            if (red + ledLevel - 5 >= 255)
            {
              redDir = !redDir;
              red = 255;
            }
            else
              red += ledLevel - 5;
          }
          else
          {
            if (red - ledLevel - 5 <= 0)
            {
              redDir = !redDir;
              red = 1;
            }
            else
              red -= ledLevel - 5;
          }

          analogWrite(ledPins[thisLed], red);
          delay(10);
        }
        else
          digitalWrite(ledPins[thisLed], LOW);
        
        if (thisLed == 7 && ledLevel == 8)
        {
          if (greenDir == 0)
          {
            if (green + ledLevel - 5 >= 255)
            {
              greenDir = !greenDir;
              green = 255;
            }
            else
              green += ledLevel - 5;
          }
          else
          {
            if (green - ledLevel - 5 <= 0)
            {
              greenDir = !greenDir;
              green = 1;
            }
            else
              green -= ledLevel - 5;
          }

          analogWrite(ledPins[thisLed], green);
          delay(10);
        }
        else
          digitalWrite(ledPins[thisLed], LOW);
         
        if (thisLed == 8 && ledLevel == 9)
        {
          if (blueDir == 0)
          {
            if (blue + ledLevel - 5 >= 255)
            {
              blueDir = !blueDir;
              blue = 255;
            }
            else
              blue += ledLevel - 5;
          }
          else
          {
            if (blue - ledLevel - 5 <= 0)
            {
              blueDir = !blueDir;
              blue = 1;
            }
            else
              blue -= ledLevel - 5;
          }

          analogWrite(ledPins[thisLed], blue);
          delay(10);
        }
        else
          digitalWrite(ledPins[thisLed], LOW);

      }
      else
      {
        digitalWrite(ledPins[thisLed], HIGH);
      }
    }
    else
    {
      digitalWrite(ledPins[thisLed], LOW);
    }
  }
}

