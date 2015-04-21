#include "FastLED.h"

#define NUM_LEDS 50

#define DATA_PIN 2

CHSV hsvStart;
CHSV hsvGoal;
CRGB leds[NUM_LEDS];

int ledHead;
int count;
int fadeSpeed;

void setup()
{
  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
  count = 0;
  fadeSpeed = 20;

  hsvStart = CHSV(random8(), 255, 255);
  hsvGoal = CHSV(random8(), 255, 255);
  ledHead = 0;

  for (int i = 0; i < NUM_LEDS - 1; i++)
  {
    leds[i] = CHSV(0, 0, 0);
  }
  FastLED.show();  
}

void loop()
{
  float hueDistance;
  
  // Check Head LED to see how far from hueGoal
  // create step size to next hue
  hueDistance = abs(hsvStart.hue - hsvGoal.hue) / fadeSpeed;
  hsvStart.hue += (int)hueDistance;

  int value = 255;
  for (int i = ledHead, j = NUM_LEDS - ledHead - 1; i >= 0; i--, j++)
  {
    Serial.print("i: ");
    Serial.print(i);
    Serial.print("j: ");
    Serial.println(j);

    leds[i] = leds[j] = CHSV(hsvStart.hue, hsvStart.sat, value);
    value -= 255 / NUM_LEDS;
  }
  ledHead++;
  if (ledHead >= NUM_LEDS)
    ledHead = 0;
   
  if (count % fadeSpeed == 0)
  {
    
  }

  FastLED.show();
  delay(5);
  
  count++;
}
  
