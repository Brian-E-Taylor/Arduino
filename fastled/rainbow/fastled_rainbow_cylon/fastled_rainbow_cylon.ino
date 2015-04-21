#include "FastLED.h"

#define NUM_LEDS 50

#define DATA_PIN 3

CRGB leds[NUM_LEDS];

int hue, sat, val;

void setup()
{
  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
  hue = 0;
  sat = 255;
  val = 255;  
}

void loop()
{
  // Generate random hue
  hue = random(255);
  
  for (int i = 0; i < NUM_LEDS + 10; i++)
  {
    
    for (int j = 0; j < 10; j++)
    {
      if (i-j < NUM_LEDS && i-j >= 0)
        leds[i-j] = CHSV(hue - (j+1)*10, sat, val - (j+1)*50);
    }
    
    /*
    if (i < NUM_LEDS && i >= 0)
      leds[i] = CHSV(hue, sat, val);
    if (i-1 < NUM_LEDS && i-1 >= 0)
      leds[i-1] = CHSV(hue - 10, sat, val - 50);
    if (i-2 < NUM_LEDS && i-2 >= 0)
      leds[i-2] = CHSV(hue - 40, sat, val - 100);
    if (i-3 < NUM_LEDS && i-3 >= 0)
      leds[i-3] = CHSV(hue - 70, sat, val - 150);
    if (i-4 < NUM_LEDS && i-4 >= 0)
      leds[i-4] = CHSV(hue - 100, sat, val - 200);
    */
    
    FastLED.show();
    
    delay(20);
    
    /*
    leds[i] = CHSV(0, 0, 0);
    if (i-1 >= 0)
      leds[i-1] = CHSV(0, 0, 0);
    if (i-2 >= 0)
      leds[i-2] = CHSV(0, 0, 0);
    if (i-3 >= 0)
      leds[i-3] = CHSV(0, 0, 0);
    if (i-4 >= 0)
      leds[i-4] = CHSV(0, 0, 0);
        
    FastLED.show();
    */
    // delay(10);
  }
}
  
