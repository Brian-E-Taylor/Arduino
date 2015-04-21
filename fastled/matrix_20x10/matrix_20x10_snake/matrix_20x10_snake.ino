#include "FastLED.h"

#define NUM_LEDS 200
#define ROWS 10
#define COLUMNS 20
#define SNAKE_SIZE 10

#define DATA_PIN 3

CRGB leds[NUM_LEDS];
int indexes[ROWS][COLUMNS];
int snake[SNAKE_SIZE];
boolean wall[ROWS][COLUMNS];

int hue, sat, val, backHue;
int dir, oldDir;
int count;
int head_x, head_y;

void setup()
{
  randomSeed(analogRead(0));
  count = 0;
  
  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
  sat = 255;
  val = 255;  
  
  hue = random8();
  backHue = hue;
  head_x = random(COLUMNS);
  head_y = random(ROWS);
  
  dir = oldDir = 0;
  
  mapPixelIndexes(ROWS, COLUMNS);
  
  for (int i = 0; i < SNAKE_SIZE; i++)
  {
    snake[i] = indexes[head_y][head_x];
  }
  
  for (int i = 0; i < ROWS; i++)
  {
    for (int j = 0; j < COLUMNS; j++)
    {
      wall[i][j] = false;
    }
  }
  
  // Set Up Wall structures
  /*
  for (int i = 0; i < 4; i++)
  {
    wall[i][5] = true;
    leds[indexes[i][5]] = CHSV(0, 0, 100);
    
    wall[7][COLUMNS-i-1] = true;
    leds[indexes[7][COLUMNS-i-1]] = CHSV(0, 0, 100);
  }
  */
}

void loop()
{
  if (random(100) <= 45)
  {
    chooseNewDirection();
  }

  moveSnake();
  
  if (count % 15 == 0)
    fadeBackground();
  
  FastLED.show();
  
  delay(12);
  count++;
}

boolean isWall(int x, int y)
{
  return wall[y][x];
}

void fadeBackground()
{
  for (int y = 0; y < ROWS; y++)
  {
    for (int x = 0; x < COLUMNS; x++)
    {
      if (!isSnakePresent(x, y) && !isWall(x, y))
      {
        // leds[indexes[y][x]].fadeToBlackBy(2);
        leds[indexes[y][x]] -= CRGB(1, 1, 1);
      }
    }
  }
}

