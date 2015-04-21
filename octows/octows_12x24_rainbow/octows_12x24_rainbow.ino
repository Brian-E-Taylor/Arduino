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

const int config = WS2811_RGB | WS2811_800kHz;

OctoWS2811 leds(ledsPerStrip, displayMemory, drawingMemory, config);

int rainbowColors[180];


void setup() {
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  for (int i=0; i<180; i++) {
    int hue = i * 2;
    int saturation = 255;
    int lightness = 255;
    // pre-compute the 180 rainbow colors
    rainbowColors[i] = HSVtoRGB(hue, saturation, lightness);
  }
  
  generatePixelIndexes(ROWS, COLUMNS);
  digitalWrite(13, LOW);
  leds.begin();
}


void loop() {
  rainbow(15, 2000);
}


// phaseShift is the shift between each row.  phaseShift=0
// causes all rows to show the same colors moving together.
// phaseShift=180 causes each row to be the opposite colors
// as the previous.
//
// cycleTime is the number of milliseconds to shift through
// the entire 360 degrees of the color wheel:
// Red -> Orange -> Yellow -> Green -> Blue -> Violet -> Red
//
void rainbow(int phaseShift, int cycleTime)
{
  int color, x, y, offset, wait;

  wait = cycleTime * 1000 / ledsPerStrip;
  for (color=0; color < 180; color++) {
    digitalWrite(13, HIGH);
    for (x=0; x < COLUMNS; x++) {
      for (y=0; y < ROWS; y++) {
        int index = (color + x + y*phaseShift/2) % 180;
        set2Pixels(x, y, rainbowColors[index]);
      }
    }
    leds.show();
    digitalWrite(13, LOW);
    delayMicroseconds(wait);
  }
}

