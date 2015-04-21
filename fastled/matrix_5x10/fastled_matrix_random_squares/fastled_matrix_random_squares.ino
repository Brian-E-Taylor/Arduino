#include "FastLED.h"

#define NUM_LEDS 50
#define ROWS 5
#define COLUMNS 10

#define DATA_PIN 2

CRGB leds[NUM_LEDS];
int indexes[NUM_LEDS];

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
        indexes[(ROWS * COLUMNS) - (ROWS * (j + 1)) + i] = COLUMNS - (j + 1) + COLUMNS * i;
      }
      else
        indexes[j * ROWS + i] = COLUMNS - (j + 1) + COLUMNS * i;      
    }
  }
}

void loop()
{
  int i = random(50);
  int center = random8();
  int outer1 = random8();
  int outer2 = random8();
  
  leds[indexes[i]] = CHSV(center, 255, 255);
  
  FastLED.show();
  delay(50);
  
  if (i - 5 >= 0)
    leds[indexes[i-5]] = CHSV(outer1, 255, 150);
  if (i - 1 >= 0 && i % ROWS)
    leds[indexes[i-1]] = CHSV(outer1, 255, 150);
  if (i + 1 < NUM_LEDS && i % ROWS != ROWS - 1)
    leds[indexes[i+1]] = CHSV(outer1, 255, 150);
  if (i + 5 < NUM_LEDS)
    leds[indexes[i+5]] = CHSV(outer1, 255, 150);
    
  FastLED.show();
  delay(80);
      
  if (i - 6 >= 0 && i % ROWS)
    leds[indexes[i-6]] = CHSV(outer2, 255, 75);
  if (i - 4 >= 0 && i % ROWS != ROWS - 1)
    leds[indexes[i-4]] = CHSV(outer2, 255, 75);
  if (i + 4 < NUM_LEDS && i % ROWS)
    leds[indexes[i+4]] = CHSV(outer2, 255, 75);
  if (i + 6 < NUM_LEDS && i % ROWS != ROWS - 1)
    leds[indexes[i+6]] = CHSV(outer2, 255, 75);
    
    
  FastLED.show();
  delay(100);
  
  leds[indexes[i]] = CRGB(0, 0, 0);
  
  if (i - 5 >= 0)
    leds[indexes[i-5]] = CRGB(0, 0, 0);
  if (i - 1 >= 0 && i % ROWS)
    leds[indexes[i-1]] = CRGB(0, 0, 0);
  if (i + 1 < NUM_LEDS && i % ROWS != ROWS - 1)
    leds[indexes[i+1]] = CRGB(0, 0, 0);
  if (i + 5 < NUM_LEDS)
    leds[indexes[i+5]] = CRGB(0, 0, 0);

  if (i - 6 >= 0 && i % ROWS)
    leds[indexes[i-6]] = CRGB(0, 0, 0);
  if (i - 4 >= 0 && i % ROWS != ROWS - 1)
    leds[indexes[i-4]] = CRGB(0, 0, 0);
  if (i + 4 < NUM_LEDS && i % ROWS)
    leds[indexes[i+4]] = CRGB(0, 0, 0);
  if (i + 6 < NUM_LEDS && i % ROWS != ROWS - 1)
    leds[indexes[i+6]] = CRGB(0, 0, 0);
  
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
