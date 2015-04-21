/*
  Required Connections
  --------------------
    pin 2:  LED Strip #1    OctoWS2811 drives 8 LED Strips.
    pin 14: LED strip #2    All 8 are the same length.
    pin 7:  LED strip #3
    pin 8:  LED strip #4    A 100 ohm resistor should used
    pin 6:  LED strip #5    between each Teensy pin and the
    pin 20: LED strip #6    wire to the LED strip, to minimize
    pin 21: LED strip #7    high frequency ringining & noise.
    pin 5:  LED strip #8
    pin 15 & 16 - Connect together, but do not use
    pin 4 - Do not use
    pin 3 - Do not use as PWM.  Normal use is ok.
    pin 1 - Output indicating CPU usage, monitor with an oscilloscope,
            logic analyzer or even an LED (brighter = CPU busier)
*/

#include <OctoWS2811.h>

#define COLUMNS 24
#define ROWS 12

const int ledsPerStrip = 100;

DMAMEM int displayMemory[ledsPerStrip*6];
int drawingMemory[ledsPerStrip*6];

int pixels[ROWS][COLUMNS];
boolean livePixels[ROWS][COLUMNS];

const int config = WS2811_RGB | WS2811_800kHz;

OctoWS2811 leds(ledsPerStrip, displayMemory, drawingMemory, config);

void setup() {
  pinMode(13, OUTPUT);

  generatePixelIndexes(ROWS, COLUMNS);

  // Generate random points
  for (int y = 0; y < ROWS; y++)
  {
    for (int x = 0; x < ROWS; x++)
    {
      if (random(100) < 5)
      {
        set2Pixels(x, y, HSVtoRGB(20, 255, 255));
        livePixels[y][x] = true;
      }
      else
        livePixels[y][x] = false;
    }
  }
  
  digitalWrite(13, LOW);
  leds.begin();
}


void loop()
{
  gameOfLife();
  leds.show();
  delayMicroseconds(100000);
}

void gameOfLife()
{
  // Generate random points
  for (int y = 0; y < ROWS; y++)
  {
    for (int x = 0; x < ROWS; x++)
    {
      if (liveNeighbors(x, y, ROWS, ROWS) < 2 || liveNeighbors(x, y, ROWS, ROWS) > 3)
      {
        // die
        set2Pixels(x, y, 0);
        livePixels[y][x] = false;
      }
      else
      {
        // live
        set2Pixels(x, y, HSVtoRGB(20, 255, 255));
        livePixels[y][x] = true;
      }
    }
  }
}

int liveNeighbors(int x, int y, int rows, int columns)
{
  int count = 0;
  // Top
  if (y + 1 < rows)
    if (livePixels[y+1][x])
      count++;
  // Top-Right
  if (y + 1 < rows && x + 1 < columns)
    if (livePixels[y+1][x+1])
      count++;
  // Right
  if (x + 1 < columns)
    if (livePixels[y][x+1])
      count++;
  // Bottom-Right
  if (y - 1 >= 0 && x + 1 < columns)
    if (livePixels[y-1][x+1])
      count++;
  // Bottom
  if (y - 1 >= 0)
    if (livePixels[y][x+1])
      count++;
  // Bottom-Left
  if (y - 1 >= 0 && x - 1 >= 0)
    if (livePixels[y-1][x-1])
      count++;
  // Left
  if (x - 1 >= 0)
    if (livePixels[y][x-1])
      count++;
  // Top-Left
  if (y + 1 < rows && x - 1 >= 0)
    if (livePixels[y+1][x-1])
      count++;
      
  return count;
}
