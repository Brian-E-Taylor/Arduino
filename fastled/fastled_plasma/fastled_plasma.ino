#include "FastLED.h"

#define NUM_LEDS 200
#define ROWS 10
#define COLUMNS 20

#define DATA_PIN 3

CRGB leds[NUM_LEDS];
int indexes[ROWS][COLUMNS];
uint8_t hue, hueShift, r, g, b;
int count;
void setup()
{
  // Serial.begin(9600);
  randomSeed(analogRead(0));

  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);

  mapPixelIndexes(ROWS, COLUMNS);
  
  count = hueShift = 0;
  
  for (int i = 0; i < ROWS; i++)
  {
    for (int j = 0; j < COLUMNS; j++)
    {
      leds[indexes[i][j]] = CRGB(0, 0, 0);
    }
  }
  FastLED.show();
}

void loop()
{
  int i, j;
  int cx, cy;
  for (i = 0; i < ROWS; i++)
  {
    for (j = 0; j < COLUMNS; j++)
    {
      // hue = quadwave8(0.6 * (j * quadwave8(count) + i * quadwave8(count/2)) + count);
      hue = hueShift + (quadwave8(j + count) * 1.5 + quadwave8(i + count) * 1.4 + quadwave8((j + i) + count) * 1.8 + quadwave8(j * j + i * i + count) / 2);
      
      /*
      hue = hueShift;
      hue += quadwave8(j + count);
      hue += 2 * quadwave8(i + count);
      hue += 4 * quadwave8(j + i + count);
      cx = j + 2 * quadwave8(count / 2);
      cy = i + 3 * quadwave8(PI/2 + count / 3);
      hue += quadwave8(sqrt(cx * cx + cy * cy + 1) + count);
      */
      
      // leds[indexes[i][j]] = CRGB(1, quadwave8(PI * hue), 1/quadwave8(PI * hue));
      leds[indexes[i][j]] = CHSV(hue, 255, random8(20) + 120);

      /*
      Serial.print("indexes[");
      Serial.print(i);
      Serial.print("][");
      Serial.print(j);
      Serial.print("]: ");
      Serial.print(indexes[i][j]);
      Serial.print(" quad: ");
      Serial.println(quadwave8(j * 20 + count));
      */
    }
  }
  FastLED.show();
  delay(3);
  
  if (count % 2 == 0)
    hueShift += 1;
      
  count++;
}
