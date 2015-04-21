#include "FastLED.h"

#define NUM_LEDS 50
#define ROWS 5
#define COLUMNS 10

#define DATA_PIN 2

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
  int i = random(ROWS);
  int j = random(COLUMNS);
  
  int center = random8();
  int outer1 = random8();
  int outer2 = random8();
  
  leds[indexes[i][j]] = CHSV(center, 255, 255);
  
  FastLED.show();
  delay(40);
  
  if (j - 1 >= 0)
    leds[indexes[i][j-1]] = CHSV(outer1, 255, 150);
  if (i - 1 >= 0)
    leds[indexes[i-1][j]] = CHSV(outer1, 255, 150);
  if (i + 1 < ROWS)
    leds[indexes[i+1][j]] = CHSV(outer1, 255, 150);
  if (j + 1 < COLUMNS)
    leds[indexes[i][j+1]] = CHSV(outer1, 255, 150);
    
  FastLED.show();
  delay(60);
      
  if (i - 1 >= 0 && j - 1 >= 0)
    leds[indexes[i-1][j-1]] = CHSV(outer2, 255, 75);
  if (i - 1 >= 0 && j + 1 < COLUMNS)
    leds[indexes[i-1][j+1]] = CHSV(outer2, 255, 75);
  if (i + 1 < ROWS && j + 1 < COLUMNS)
    leds[indexes[i+1][j+1]] = CHSV(outer2, 255, 75);
  if (i + 1 < ROWS && j - 1 >= 0)
    leds[indexes[i+1][j-1]] = CHSV(outer2, 255, 75);
    
    
  FastLED.show();
  delay(100);
  
  leds[indexes[i][j]] = CRGB(0, 0, 0);
  
  if (j - 1 >= 0)
    leds[indexes[i][j-1]] = CRGB(0, 0, 0);
  if (i - 1 >= 0)
    leds[indexes[i-1][j]] = CRGB(0, 0, 0);
  if (i + 1 < ROWS)
    leds[indexes[i+1][j]] = CRGB(0, 0, 0);
  if (j + 1 < COLUMNS)
    leds[indexes[i][j+1]] = CRGB(0, 0, 0);

  if (i - 1 >= 0 && j - 1 >= 0)
    leds[indexes[i-1][j-1]] = CRGB(0, 0, 0);
  if (i - 1 >= 0 && j + 1 < COLUMNS)
    leds[indexes[i-1][j+1]] = CRGB(0, 0, 0);
  if (i + 1 < ROWS && j + 1 < COLUMNS)
    leds[indexes[i+1][j+1]] = CRGB(0, 0, 0);
  if (i + 1 < ROWS && j - 1 >= 0)
    leds[indexes[i+1][j-1]] = CRGB(0, 0, 0);
  
  delay(10);
  
  /*  
  for (int i = 0; i < NUM_LEDS; i+=5)
  {
    // Generate random hue
    hue += 2;
    
    for (int j = 0; j < ROWS; j++)
    {
      if (i+j < NUM_LEDS)
        leds[indexes[i+j]] = CHSV(hue + i * 20, 255, 255);
    }
    
    FastLED.show();
      
    delay(100);

    for (int j = 0; j < ROWS; j++)
    {
      if (i+j < NUM_LEDS)
        leds[indexes[i+j]] = CRGB(0, 0, 0);
    }
    
    FastLED.show();

    delay(5);    
  }    
  */
}
