#include "FastLED.h"

#define NUM_LEDS 200
#define ROWS 10
#define COLUMNS 20
#define SWEEP_SIZE 6

#define DATA_PIN 3

CRGB leds[NUM_LEDS];
int indexes[ROWS][COLUMNS];

void setup()
{
  randomSeed(analogRead(0));

  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);

  mapPixelIndexes(ROWS, COLUMNS);
}

void loop()
{
  int hue = random8();
  int hueFade;

  for (int i = 0; i < COLUMNS + SWEEP_SIZE; i++)
  {
    hueFade -= 2;
    for (int j = 0; j < ROWS; j++)
    {
      hueFade = hue;
      hueFade -= 20;
      for (int x = 0; x < SWEEP_SIZE; x++)
      {
        if (i - x >= 0 && i - x <= COLUMNS)
        {
          leds[indexes[j][i-x]] = CHSV(hueFade, 255, 200);
          hueFade -= 20;
        }
      }
    }

    FastLED.show();
    delay(40);

    for (int j = 0; j < ROWS; j++)
    {
      for (int x = 0; x < SWEEP_SIZE; x++)
      {
        if (i - x >= 0 && i - x <= COLUMNS)
        {
          leds[indexes[j][i-x]] = CHSV(0, 0, 0);
        }
      }
    }
    hue += 2;
  }
}

