#include "FastLED.h"

#define NUM_LEDS 200

#define DATA_PIN 3

CHSV hsvStart[NUM_LEDS];
CHSV hsvGoal[NUM_LEDS];
CRGB leds[NUM_LEDS];

int hueStart, hueGoal, sat, val;
int count;
int fadeSpeed;
int brightnessFadeDir, hueFadeDir;

void setup()
{
  randomSeed(analogRead(0));
  // Serial.begin(9600);
  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
  hueStart = 0;
  hueGoal = 0;
  sat = 255;
  val = 255;  
  count = 0;
  fadeSpeed = 300;
  hueStart = random8();
  hueGoal = random8();
  brightnessFadeDir = 1;
  hueFadeDir = 1;
  // Generate random hue
  for (int i = 0; i < NUM_LEDS; i++)
  {
    hueStart-=2;
    hsvStart[i] = CHSV(hueStart, sat, random8());
    leds[i] = hsvStart[i];
    hsvGoal[i] = CHSV(hueStart, sat, random8());
  }
}

void loop()
{
  if (count % 20 == 0)
  {
    for (int i = 0; i < NUM_LEDS; i++)
    {
      brightnessFadeDir = hsvGoal[i].val - hsvStart[i].val;
      if (brightnessFadeDir > 0)
      {
        hsvStart[i].val++;
      }
      if (brightnessFadeDir < 0)
      {
        hsvStart[i].val--;
        if (hsvStart[i].val < 0)
          hsvStart[i].val = 0;
      }
      
      hueFadeDir = hsvGoal[i].hue - hsvStart[i].hue;
      if (hueFadeDir > 0)
      {
        hsvStart[i].hue++;
      }
      if (hueFadeDir < 0)
      {
        hsvStart[i].hue--;
        if (hsvStart[i].hue < 0)
          hsvStart[i].hue = 0;
      }
      
      leds[i] = hsvStart[i];
    }
  }
  
  if (count % 40 == 0)
  {
    for (int i = 0; i < NUM_LEDS; i++)
    {
      hsvStart[i].hue++;
      hsvGoal[i].hue++;
      leds[i] = hsvStart[i];
    }
  }
  
  if (count % fadeSpeed == 0)
  {
    // Generate random hue
    int j = random(NUM_LEDS);
    hsvGoal[j].hue = hueGoal;

    for (int i = 0; i < NUM_LEDS; i++)
    {
      // hsvStart[i].val = hsvGoal[i].val;
      hsvGoal[i].val = random8();
      // hsvStart[i] = hsvGoal[i];
      // hsvGoal[i] = CHSV(hueStart, sat, 20 + random8(200));
    }

    count = 0;
  }

  FastLED.show();
  delay(1);
  
  count++;
}
  
