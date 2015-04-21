#include "FastLED.h"

#define NUM_LEDS 200

#define DATA_PIN 3

CRGB leds[NUM_LEDS];

int hue;
int sat;
int val;

void setup()
{
  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
  hue = 0;
  sat = 255;
  val = 255;
}

void loop()
{  
  for (int i = NUM_LEDS - 1; i >= 0; i-=5)
  {
    if (i+4 < NUM_LEDS)
      leds[i+4] = leds[i+3];
    if (i+3 < NUM_LEDS)
      leds[i+3] = leds[i+2];
    if (i+2 < NUM_LEDS)
      leds[i+2] = leds[i+1];
    if (i+1 < NUM_LEDS)
      leds[i+1] = leds[i];      
    
    if (i-4 >= 0)
      leds[i-4] = CHSV(hue, sat, val - 190);
    if (i-3 >= 0)
      leds[i-3] = CHSV(hue, sat, val - 140);
    if (i-2 >= 0)
      leds[i-2] = CHSV(hue, sat, val - 90);
    if (i-1 >= 0)
      leds[i-1] = CHSV(hue, sat, val - 40);
    leds[i] = CHSV(hue++, sat, val);
    
    if (hue > 255)
      hue = 0;
  }
  
  FastLED.show();
  
  delay(50);
}
  
