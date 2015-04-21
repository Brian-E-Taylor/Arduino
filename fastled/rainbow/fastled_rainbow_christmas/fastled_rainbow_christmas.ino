#include "FastLED.h"

#define NUM_LEDS 200

#define DATA_PIN 3

CRGB leds[NUM_LEDS];

void setup()
{
  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
  randomSeed(analogRead(0));
}

void loop()
{
  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = CHSV(random8(), 255, 20 + random8(230));
  }
  FastLED.show();
  delay(40);
}
  
