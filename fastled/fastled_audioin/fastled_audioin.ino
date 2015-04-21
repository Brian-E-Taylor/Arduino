#include "FastLED.h"

#define NUM_LEDS 50

#define DATA_PIN 3

CRGB leds[NUM_LEDS];
int hue1;
int sat1;
int val1;
int count;
int max1, max2;

void setup()
{
  Serial.begin(9600);
  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
  hue1 = 0;
  sat1 = 255;
  val1 = 255;
  count = 0;
  max1 = 100;
  max2 = 200;
}

void loop()
{
  if (Serial.available())
  {
    if (Serial.read() == 0xff)
    {
      val1 = 0;
      for (int i = 0; i < 16; i++)
      {
        val1 = max(val1, Serial.read());
      }

      int i, j;
      for (i = 0; i < NUM_LEDS; i++)
      {
        leds[i] = CHSV(0, 0, 0);
      }
      FastLED.show();
    
      j = (NUM_LEDS / 2) - 1;
      for (i = (NUM_LEDS / 2); i < 25 + val1 * 3; i++)
      {
        if (i < NUM_LEDS)
          leds[i] = CHSV(hue1, sat1, val1 * 15);
        if (j >= 0)
          leds[j] = CHSV(hue1, sat1, val1 * 15);
        j--;
      }
    
    FastLED.show();
    }
  }
  
  delay(10);
}
  
