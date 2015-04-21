#include "FastLED.h"

#define NUM_LEDS 200
#define ROWS 10
#define COLUMNS 20
#define SNAKE_SIZE 10

#define DATA_PIN 3

CRGB leds[NUM_LEDS];
int indexes[ROWS][COLUMNS];

int readData[3];

void setup()
{
  Serial.begin(9600);
  
  randomSeed(analogRead(0));
  
  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);

  mapPixelIndexes(ROWS, COLUMNS);
}

void loop()
{
  if (Serial.available())
  {
    readData[0] = Serial.read();
    while (readData[0] == -1)
    {
      readData[0] = Serial.read();
    }
    readData[1] = Serial.read();
    readData[2] = Serial.read();
    
    for (int i = 0; i < 20; i++)
    {
      for (int j = 0; j < 10; j++)
      {
        leds[indexes[i][j]] = CRGB(readData[0], readData[1], readData[2]);
        readData[0] = Serial.read();
        readData[1] = Serial.read();
        readData[2] = Serial.read();
      }
    }
  } 
  FastLED.show();
  
}

