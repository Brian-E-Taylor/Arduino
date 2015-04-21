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
  
  for (int i = 0; i < NUM_LEDS; i+=4)
  {
    leds[i] = CHSV(hue, sat, val);
    if (i+1 < NUM_LEDS)
      leds[i+1] = CHSV(hue, sat, val);
    if (i+2 < NUM_LEDS)
      leds[i+2] = CHSV(hue, sat, val);
    if (i+3 < NUM_LEDS)
      leds[i+3] = CHSV(hue, sat, val);
    
    FastLED.show();
    
    delay(50);
    
    leds[i] = CHSV(0, 0, 0);
    if (i+1 < NUM_LEDS)
      leds[i+1] = CHSV(0, 0, 0);
    if (i+2 < NUM_LEDS)
      leds[i+2] = CHSV(0, 0, 0);
    if (i+3 < NUM_LEDS)
      leds[i+3] = CHSV(0, 0, 0);
        
    FastLED.show();

     delay(10);
  }
}
  
