/*
  Required Connections
  --------------------
    pin 2:  LED Strip #1    OctoWS2811 drives 8 LED Strips.
    pin 14: LED strip #2    All 8 are the same length.
    pin 7:  LED strip #3
    pin 8:  LED strip #4    A 100 ohm resistor should used
    pin 6:  LED strip #5    between each Teensy pin and the
    pin 20: LED strip #6    wire to the LED strip, to minimize
    pin 21: LED strip #7    high frequency ringining & noise.
    pin 5:  LED strip #8
    pin 15 & 16 - Connect together, but do not use
    pin 4 - Do not use
    pin 3 - Do not use as PWM.  Normal use is ok.

  This test is useful for checking if your LED strips work, and which
  color config (WS2811_RGB, WS2811_GRB, etc) they require.
*/

#include <OctoWS2811.h>

#define ROWS 12
#define COLUMNS 24

const int ledsPerStrip = 100;

DMAMEM int displayMemory[ledsPerStrip*6];
int drawingMemory[ledsPerStrip*6];

int pixels[ROWS][COLUMNS];

const int config = WS2811_RGB | WS2811_800kHz;

OctoWS2811 leds(ledsPerStrip, displayMemory, drawingMemory, config);

int snake[5];

int hue, sat, val, backHue;
int dir, oldDir;
int count;
int x, y;

void setup()
{
  // Serial.begin(9600);
  
  // delay(5000);
  Serial.println("Beginning....");
  
  // pinMode(1, OUTPUT);
  // digitalWrite(1, HIGH);
  
  hue = random(360);
  sat = 255;
  val = 255;
  sat = 255;
  val = 255;  
  
  backHue = hue;
  x = random(ROWS);
  y = random(ROWS);
  
  dir = oldDir = 0;

  generatePixelIndexes(ROWS, COLUMNS);
  for (int i = 0; i < 5; i++)
  {
    snake[i] = pixels[y][x];
  }
  
  //digitalWrite(1, LOW);
  leds.begin();
}


void loop()
{
  if (random(100) <= 60)
  {
    hue++;
    backHue++;
    do
      dir = random(4);
    while (oldDir == dir);
    oldDir = dir;
  }

  moveSnake(0, 0, ROWS, ROWS);
  
  leds.show();
  delayMicroseconds(50000);  
}

void drawSnake(int h, int s, int v, boolean on)
{
  if (on)
  {
    for (int i = 0; i < 5; i++)
    {
      leds.setPixel(snake[i], HSVtoRGB(h, s, v - (i * 50)));
      leds.setPixel(snake[i]+1, HSVtoRGB(h, s, v - (i * 50)));
      // set2Pixels(x, y, HSVtoRGB(h, s, v - (i * 50)));
    }
  }
  else
  {
    for (int i = 0; i < 5; i++)
    {
      // set2Pixels(x, y, HSVtoRGB(h, s, 20));
    }
  }
}

void moveSnake(int x1, int y1, int x2, int y2)
{
  switch (dir)
  {
    case 0:
      if (y - 1 < y1)
      {
        hue++;
        backHue++;
        do
          dir = random(4);
        while (oldDir == dir);
        oldDir = dir;
      }
      else
      {
        drawSnake(backHue, sat, val, 0);

        y--;
        for (int i = 4; i > 0; i--)
        {
          snake[i] = snake[i-1];
        }
        snake[0] = pixels[y][x];        

        drawSnake(hue, sat, val, 1);
      }
      break;

    case 1:
      if (x + 1 >= x2)
      {
        hue++;
        backHue++;
        do
          dir = random(4);
        while (oldDir == dir);
        oldDir = dir;
      }
      else
      {
        drawSnake(backHue, sat, val, 0);

        x++;
        for (int i = 4; i > 0; i--)
        {
          snake[i] = snake[i-1];
        }
        snake[0] = pixels[y][x];        

        drawSnake(hue, sat, val, 1);
      }
      break;

    case 2:
      if (y + 1 >= y2)
      {
        hue++;
        backHue++;
        do
          dir = random(4);
        while (oldDir == dir);
        oldDir = dir;
      }
      else
      {
        drawSnake(backHue, sat, val, 0);

        y++;
        for (int i = 4; i > 0; i--)
        {
          snake[i] = snake[i-1];
        }
        snake[0] = pixels[y][x];        

        drawSnake(hue, sat, val, 1);
      }
      break;

    case 3:
      if (x - 1 < x1)
      {
        hue++;
        backHue++;
        do
          dir = random(4);
        while (oldDir == dir);
        oldDir = dir;
      }
      else
      {
        drawSnake(backHue, sat, val, 0);

        x--;
        for (int i = 4; i > 0; i--)
        {
          snake[i] = snake[i-1];
        }
        snake[0] = pixels[y][x];        

        drawSnake(hue, sat, val, 1);
      }
      break;
  }
}

