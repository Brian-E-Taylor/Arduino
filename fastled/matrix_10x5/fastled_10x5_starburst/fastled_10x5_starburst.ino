// TODO:
//  Animate starburst at each stage for all starbursts
//   instead of each starburst's stage fully before animating next starburst
//   (animate stages backwards? need to keep track of starting times?)
//
//  Finish starburst animation stages


#include "FastLED.h"
#include "Starburst.h"

#define NUM_LEDS 50
#define ROWS 5
#define COLUMNS 10
#define STARBURST_COUNT 10

#define DATA_PIN 3

CRGB leds[NUM_LEDS];
int indexes[ROWS][COLUMNS];
Starburst starbursts[STARBURST_COUNT];

int sat, val, backHue;
int x, y;

void setup()
{
  randomSeed(analogRead(0));

  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
  sat = 255;
  val = 255;  

  mapPixelIndexes(ROWS, COLUMNS);

  for (int i = 0; i < STARBURST_COUNT; i++)
  {
    starbursts[i].animationStage = 0;
    starbursts[i].hue = random8();
  }
  starbursts[0].animationStage = 5;
  starbursts[0].x = random(COLUMNS);
  starbursts[0].y = random(ROWS);
}

void loop()
{
  if (random(100) < 30)
  {
    int j = random(STARBURST_COUNT);
    if (starbursts[j].animationStage != 0)
    {
      starbursts[j].animationStage = 5;
      starbursts[j].x = random(COLUMNS);
      starbursts[j].y = random(ROWS);
    }
  }

  animateStarburst();
  
  FastLED.show();
  
  delay(15);
}

void animateStarburst()
{
  for (int i = 0; i < STARBURST_COUNT; i++)
  {
    Starburst* star = &starbursts[i];
    int x = star->x;
    int y = star->y;
    int hue = star->hue;
  
  if (star->animationStage == 5)
  {
    leds[indexes[y][x]] = CHSV(hue, 255, 255);
  }
  else if (star->animationStage == 4)
  {
    if (y - 1 >= 0)
      leds[indexes[y-1][x]] = CHSV(hue+20, 255, 180);
    if (y + 1 < ROWS)
      leds[indexes[y+1][x]] = CHSV(hue+20, 255, 180);
    if (x - 1 >= 0)
      leds[indexes[y][x-1]] = CHSV(hue+20, 255, 180);
    if (x + 1 < COLUMNS)
      leds[indexes[y][x+1]] = CHSV(hue+20, 255, 180);
  }
  else if (star->animationStage == 3)
  {
    if (y - 1 >= 0 && x - 1 >= 0)
      leds[indexes[y-1][x-1]] = CHSV(hue+30, 255, 140);
    if (y + 1 < ROWS && x - 1 >= 0)
      leds[indexes[y+1][x-1]] = CHSV(hue+30, 255, 140);
    if (y - 1 >= 0 && x + 1 < COLUMNS)
      leds[indexes[y-1][x+1]] = CHSV(hue+30, 255, 140);
    if (y + 1 < ROWS && x + 1 < COLUMNS)
      leds[indexes[y+1][x+1]] = CHSV(hue+30, 255, 140);
  }
  else if (star->animationStage == 2)
  {
    leds[indexes[y][x]] = CRGB(0, 0, 0);

    if (y - 1 >= 0)
      leds[indexes[y-1][x]] = CRGB(0, 0, 0);
    if (y + 1 < ROWS)
      leds[indexes[y+1][x]] = CRGB(0, 0, 0);
    if (x - 1 >= 0)
      leds[indexes[y][x-1]] = CRGB(0, 0, 0);
    if (x + 1 < COLUMNS)
      leds[indexes[y][x+1]] = CRGB(0, 0, 0);
  }
  else if (star->animationStage == 1)
  {
    
  }
  else if (star->animationStage == 0)
  {
    if (y - 1 >= 0 && x - 1 >= 0)
      leds[indexes[y-1][x-1]] = CRGB(0, 0, 0);
    if (y + 1 < ROWS && x - 1 >= 0)
      leds[indexes[y+1][x-1]] = CRGB(0, 0, 0);
    if (y - 1 >= 0 && x + 1 < COLUMNS)
      leds[indexes[y-1][x+1]] = CRGB(0, 0, 0);
    if (y + 1 < ROWS && x + 1 < COLUMNS)
      leds[indexes[y+1][x+1]] = CRGB(0, 0, 0);
  }
  
  star->animationStage--;
   if (star->animationStage < 0)
     star->animationStage = 0;
  }
}


