#include "FastLED.h"

#define NUM_LEDS 200

#define DATA_PIN 3

CHSV hsvStart[NUM_LEDS];
CRGB leds[NUM_LEDS];
int brightnessFadeDir[NUM_LEDS];

int hueStart, sat, val;
int count;

void setup()
{
  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
  hueStart = 0;
  sat = 255;
  val = 255;  
  count = 0;
  hueStart = random8();
  // Generate random hue
  int j = 50;
  int k = 15;
  for (int i = 0; i < NUM_LEDS; i++)
  {
    if (i != 0)
      brightnessFadeDir[i] = brightnessFadeDir[i-1];
    hueStart -= 1;
    hsvStart[i] = CHSV(hueStart, sat, j);
    j += k;
    if (j > 253)
    {
      brightnessFadeDir[i] = -1;
      j = 255;
      k = -k;
    }
    if (j <= 50)
    {
      brightnessFadeDir[i] = 1;
      j = 50;
      k = -k;
    }
    leds[i] = hsvStart[i];
  }
}

void loop()
{
  if (count % 5 == 0)
  {
    for (int i = 0; i < NUM_LEDS; i++)
    {
      if (hsvStart[i].val > 253)
        brightnessFadeDir[i] = -1;
      if (hsvStart[i].val <= 50)
        brightnessFadeDir[i] = 1;
        
      if (brightnessFadeDir[i] > 0)
      {
        hsvStart[i].val += 1;
      }
      if (brightnessFadeDir[i] < 0)
      {
        hsvStart[i].val -= 1;
      }
      if (hsvStart[i].val < 50)
        hsvStart[i].val = 50;
        
      leds[i] = hsvStart[i];
    }
  }
  
  if (count % 40 == 0)
  {
    for (int i = 0; i < NUM_LEDS; i++)
    {
      hsvStart[i].hue++;
      leds[i] = hsvStart[i];
    }
  }

  if (count % 1000 == 0)
    count = 0;

  FastLED.show();
  
  count++;
}
  
