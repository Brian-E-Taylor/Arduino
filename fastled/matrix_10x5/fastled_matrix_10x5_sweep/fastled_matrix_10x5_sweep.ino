#include "FastLED.h"

#define NUM_LEDS 50
#define ROWS 5
#define COLUMNS 10

#define DATA_PIN 3

CRGB leds[NUM_LEDS];
int indexes[ROWS][COLUMNS];

int hue, sat, val;

void setup()
{
  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
  sat = 255;
  val = 100;  
  
  for (int i = 0; i < ROWS; i++)
  {
    for (int j = 0; j < COLUMNS; j++)
    {
      if (i % 2)
      {
        indexes[i][j] = i * COLUMNS + COLUMNS - 1 - j;
      }
      else
      {
        indexes[i][j] = i * COLUMNS + j;
      }
      /*
      if (i % 2)
      {
        indexes[(ROWS * COLUMNS) - (ROWS * (j + 1)) + i] = COLUMNS - (j + 1) + COLUMNS * i;
      }
      else
        indexes[j * ROWS + i] = COLUMNS - (j + 1) + COLUMNS * i;      
      */
    }
  }
}

void loop()
{
  int hue = random8();
  int hueFade;
  
  for (int i = 0; i < COLUMNS; i++)
  {
    hueFade -= 2;
    for (int j = 0; j < ROWS; j++)
    {
      leds[indexes[j][i]] = CHSV(hue, 255, 255);
      hueFade = hue;
      hueFade -= 20;
      if (i - 1 > 0)
      {
        leds[indexes[j][i-1]] = CHSV(hueFade, 255, 200);
        hueFade -= 20;
      }
      if (i - 2 > 0)
      {
        leds[indexes[j][i-2]] = CHSV(hueFade, 255, 100);
        hueFade -= 20;
      }
    }
    
    FastLED.show();
    delay(80);
    
    for (int j = 0; j < ROWS; j++)
    {
      leds[indexes[j][i]] = CHSV(0, 0, 0);
      if (i - 1 > 0)
        leds[indexes[j][i-1]] = CHSV(0, 0, 0);
      if (i - 2 > 0)
        leds[indexes[j][i-2]] = CHSV(0, 0, 0);
    }
    
    hue += 2;
  }
}
