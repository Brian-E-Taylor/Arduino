#include "FastLED.h"

#define NUM_LEDS 50
#define ROWS 5
#define COLUMNS 10
#define SNAKE_SIZE 7

#define DATA_PIN 3

CRGB leds[NUM_LEDS];
int indexes[ROWS][COLUMNS];
int snake[SNAKE_SIZE];

int hue, sat, val, backHue;
int dir, oldDir;
int count;
int x, y;

void setup()
{
  randomSeed(analogRead(0));
  count = 0;
  
  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
  sat = 255;
  val = 255;  
  
  hue = random8();
  backHue = hue;
  x = random(COLUMNS);
  y = random(ROWS);
  
  dir = oldDir = 0;
  
  mapPixelIndexes(ROWS, COLUMNS);
  
  for (int i = 0; i < SNAKE_SIZE; i++)
  {
    snake[i] = indexes[y][x];
  }
}

void loop()
{
  if (random(100) <= 55)
  {
    do
      dir = random(4);
    while (oldDir == dir);
    oldDir = dir;
  }

  moveSnake();
  FastLED.show();
  
  delay(20);
  count++;
}

void drawSnake(int h, int s, int v, boolean on)
{
  if (on)
  {
    if (random(100) <= 75)
    {
      hue++;
      backHue++;
    }
    
    for (int i = 0; i < SNAKE_SIZE; i++)
    {
      leds[snake[i]] = CHSV(h, s, v - (i * 15));
    }
  }
/*
  else
  {
    for (int i = 0; i < SNAKE_SIZE; i++)
    {
      leds[snake[i]] = CHSV(h, s, 20);
    }
  }
*/
}

void moveSnake()
{
  switch (dir)
  {
    case 0:
      if (y - 1 < 0)
      {
        do
          dir = random(4);
        while (oldDir == dir);
        oldDir = dir;
      }
      else
      {
        drawSnake(backHue, sat, val, 0);

        y--;
        for (int i = SNAKE_SIZE-1; i > 0; i--)
        {
          snake[i] = snake[i-1];
        }
        snake[0] = indexes[y][x];        

        drawSnake(hue, sat, val, 1);
      }
      break;

    case 1:
      if (x + 1 >= COLUMNS)
      {
        do
          dir = random(4);
        while (oldDir == dir);
        oldDir = dir;
      }
      else
      {
        drawSnake(backHue, sat, val, 0);

        x++;
        for (int i = SNAKE_SIZE-1; i > 0; i--)
        {
          snake[i] = snake[i-1];
        }
        snake[0] = indexes[y][x];        

        drawSnake(hue, sat, val, 1);
      }
      break;

    case 2:
      if (y + 1 >= ROWS)
      {
        do
          dir = random(4);
        while (oldDir == dir);
        oldDir = dir;
      }
      else
      {
        drawSnake(backHue, sat, val, 0);

        y++;
        for (int i = SNAKE_SIZE-1; i > 0; i--)
        {
          snake[i] = snake[i-1];
        }
        snake[0] = indexes[y][x];        

        drawSnake(hue, sat, val, 1);
      }
      break;

    case 3:
      if (x - 1 < 0)
      {
        do
          dir = random(4);
        while (oldDir == dir);
        oldDir = dir;
      }
      else
      {
        drawSnake(backHue, sat, val, 0);

        x--;
        for (int i = SNAKE_SIZE-1; i > 0; i--)
        {
          snake[i] = snake[i-1];
        }
        snake[0] = indexes[y][x];        

        drawSnake(hue, sat, val, 1);
      }
      break;
  }
}

boolean isSnakePresent(int x, int y)
{
  for (int i = 0; i < SNAKE_SIZE; i++)
  {
    if (snake[i] == indexes[y][x])
      return true;
  }
  return false;
}
