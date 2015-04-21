int leds[3][3];
int buffer[3][3][3];
int newFrame[3][3][3];
int framerate = 100;
int persistencerate = 20;

void setup()
{
  leds[0][0] = 3;    // PWM
  leds[0][1] = 7;
  leds[0][2] = 5;    // PWM
  leds[1][0] = 8;
  leds[1][1] = 6;    // PWM
  leds[1][2] = 12;
  leds[2][0] = 9;    // PWM
  leds[2][1] = 10;   // PWM
  leds[2][2] = 11;   // PWM
  
  pinMode(leds[0][0], OUTPUT);  // back-left
  pinMode(leds[0][1], OUTPUT);  // back-center
  pinMode(leds[0][2], OUTPUT);  // back-right
  pinMode(leds[1][0], OUTPUT);  // mid-left
  pinMode(leds[1][1], OUTPUT);  // mid-center
  pinMode(leds[1][2], OUTPUT);  // mid-right
  pinMode(leds[2][0], OUTPUT);  // front-left
  pinMode(leds[2][1], OUTPUT);  // front-center
  pinMode(leds[2][2], OUTPUT);  // front-right
  
  pinMode(A3, OUTPUT);          // GND, top layer
  pinMode(A4, OUTPUT);          // GND, middle layer
  pinMode(A5, OUTPUT);          // GND, bottom layer
  
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 3; k++)
      {
        buffer[i][j][k] = 0;
        newFrame[i][j][k] = 0;
      }
}
    
void displayLeds()
{
  // first layer
  displayTop(HIGH);
  delay(persistencerate);
  displayTop(LOW);
  displayMiddle(HIGH);
  delay(persistencerate);
  displayMiddle(LOW);  
  displayBottom(HIGH);
  delay(persistencerate);
  displayBottom(LOW);  
}

void displayTop(uint8_t sig)
{
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      if (sig == LOW || buffer[i][j][0] == 0)
        digitalWrite(leds[i][j], LOW);
      else
        digitalWrite(leds[i][j], HIGH);
    }
  }
  digitalWrite(A3, LOW);
  digitalWrite(A4, HIGH);
  digitalWrite(A5, HIGH);
}

void displayMiddle(uint8_t sig)
{
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      if (sig == LOW || buffer[i][j][1] == 0)
        digitalWrite(leds[i][j], LOW);
      else
        digitalWrite(leds[i][j], HIGH);
    }
  }
  digitalWrite(A3, HIGH);
  digitalWrite(A4, LOW);
  digitalWrite(A5, HIGH);
}        

void displayBottom(uint8_t sig)
{
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      if (sig == LOW || buffer[i][j][2] == 0)
        digitalWrite(leds[i][j], LOW);
      else
        digitalWrite(leds[i][j], HIGH);
    }
  }
  digitalWrite(A3, HIGH);
  digitalWrite(A4, HIGH);
  digitalWrite(A5, LOW);
}

// where the magic happens
void updateFrame()
{
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 3; k++)
        newFrame[i][j][k] = 1;
}

void updateBuffer()
{
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      for (int k = 0; k < 3; k++)
        buffer[i][j][k] = newFrame[i][j][k];
}

void loop()
{
  updateFrame();
  
  updateBuffer();
  
  displayLeds();

  delay(framerate);
}
