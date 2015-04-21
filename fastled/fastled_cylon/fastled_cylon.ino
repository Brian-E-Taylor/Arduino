#include "FastLED.h"

#define NUM_LEDS 200

#define DATA_PIN 3

CRGB leds[NUM_LEDS];

void setup()
{
  Serial.begin(9600);
  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
  
}

void loop()
{
  for (int i = 0; i < NUM_LEDS; i++)
  {
    if (i-2 >= 0)
      leds[i-2] = CHSV(0, 255, 60);
    if (i-1 >= 0)
      leds[i-1] = CHSV(0, 255, 150);
    leds[i] = CHSV(0, 255, 255);
    if (i+1 < NUM_LEDS)
      leds[i+1] = CHSV(0, 255, 150);
    if (i+2 < NUM_LEDS)
      leds[i+2] = CHSV(0, 255, 60);
    
    FastLED.show();
    
    if (i-2 >= 0)
      leds[i-2] = CHSV(0, 0, 0);
    if (i-1 >= 0)
      leds[i-1] = CHSV(0, 0, 0);
    leds[i] = CHSV(0, 0, 0);
    if (i+1 < NUM_LEDS)
      leds[i+1] = CHSV(0, 0, 0);
    if (i+2 < NUM_LEDS)
      leds[i+2] = CHSV(0, 0, 0);

    /*
    if (i < NUM_LEDS / 2)
    {
      Serial.print(lerp8by8(i, 100, 2));
      Serial.print("\n");
      delay(lerp8by8(i, 100, 2));
    }
    else
    {
      Serial.print(lerp8by8(i, 0, 2));
      Serial.print("\n");
      delay(lerp8by8(i, 0, 2));
    }
    */
    delay(10);
  }
  
  delay(300);
  
  for (int i = NUM_LEDS - 1; i >= 0; i--)
  {
    if (i-2 >= 0)
      leds[i-2] = CHSV(0, 255, 60);
    if (i-1 >= 0)
      leds[i-1] = CHSV(0, 255, 150);
    leds[i] = CHSV(0, 255, 255);
    if (i+1 < NUM_LEDS)
      leds[i+1] = CHSV(0, 255, 150);
    if (i+2 < NUM_LEDS)
      leds[i+2] = CHSV(0, 255, 60);
    
    FastLED.show();
    
    if (i-2 >= 0)
      leds[i-2] = CHSV(0, 0, 0);
    if (i-1 >= 0)
      leds[i-1] = CHSV(0, 0, 0);
    leds[i] = CHSV(0, 0, 0);
    if (i+1 < NUM_LEDS)
      leds[i+1] = CHSV(0, 0, 0);
    if (i+2 < NUM_LEDS)
      leds[i+2] = CHSV(0, 0, 0);
    
    delay(10);
  }
  
  delay(300);
}
  
