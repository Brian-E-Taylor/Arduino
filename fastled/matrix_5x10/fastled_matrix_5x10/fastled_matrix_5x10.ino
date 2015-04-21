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
}
