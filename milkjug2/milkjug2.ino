// constants won't change. They're used here to 
// set pin numbers:
const int circuit1pwm = 3;      // the number of the LED pins
const int circuit2pwm = 5;
const int circuit3pwm = 6;
const int circuit4 = 2;
const int circuit5 = 8;
const int circuit6pwm = 9;
const int circuit7pwm = 10;
const int circuit8 = 11;
const int circuit9 = 12;

// ANALOG
int ledState1 = 0;
int ledState2 = 0;
int ledState3 = 0;
int ledState6 = 0;
int ledState7 = 0;

// DIGITAL
// int ledState1 = LOW;
// int ledState2 = LOW;
// int ledState3 = LOW;
int ledState4 = LOW;
int ledState5 = LOW;
// int ledState6 = LOW;
// int ledState7 = LOW;
int ledState8 = LOW;
int ledState9 = LOW;

int ledState[9] = {ledState1, ledState2, ledState3, ledState4, ledState5, ledState6, ledState7, ledState8, ledState9};
int low[9] = {0, 0, 0, LOW, LOW, 0, 0, LOW, LOW};
int high[9] = {255, 255, 255, HIGH, HIGH, 255, 255, HIGH, HIGH};
int digitalOn[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
int digitalOff[9] = {0, 0, 0, 0, 0, 0, 0,  0, 0};
int inSpeed[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
int outSpeed[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};

boolean asc[5] = {false, false, false, false, false};
boolean done[5] = {true, true, true, true, true};
boolean pulsing[5] = {false, false, false, false, false};

int count = 0;

void setup() {
  pinMode(circuit1pwm, OUTPUT);
  pinMode(circuit2pwm, OUTPUT);
  pinMode(circuit3pwm, OUTPUT);
  pinMode(circuit4, OUTPUT);
  pinMode(circuit5, OUTPUT);
  pinMode(circuit6pwm, OUTPUT);
  pinMode(circuit7pwm, OUTPUT);
  pinMode(circuit8, OUTPUT);
  pinMode(circuit9, OUTPUT);
}

void loop() {
  // ANALOG  
  analogWrite(circuit1pwm, ledState[0]);
  analogWrite(circuit2pwm, ledState[1]);
  analogWrite(circuit3pwm, ledState[2]);
  analogWrite(circuit6pwm, ledState[5]);
  analogWrite(circuit7pwm, ledState[6]);

  // DIGITAL
//  digitalWrite(circuit1pwm, ledState[0]);
//  digitalWrite(circuit2pwm, ledState[1]);
//  digitalWrite(circuit3pwm, ledState[2]);
//  digitalWrite(circuit6pwm, ledState[5]);
//  digitalWrite(circuit7pwm, ledState[6]);
  digitalWrite(circuit4, ledState[3]);
  digitalWrite(circuit5, ledState[4]);
  digitalWrite(circuit8, ledState[7]);
  digitalWrite(circuit9, ledState[8]);
  
  delay(5);

  if (count == 10)
  {
    fadeIn(1, 0, 255, 1);
    fadeIn(4, 0, 255, 1);
  }
  
  if (count == 800)
  {
    pulse(1, 0, 255, 3, 2);
    pulse(4, 0, 255, 20, 1);
  }
  
  if (count == 1900)
  {
    fadeIn(1, 0, 255, 1);
    fadeIn(4, 0, 255, 1);
  }
  if (count == 2000)
  {
    fadeOut(1, 0, 255, 1);
    fadeOut(4, 0, 255, 1);
  }

    for (int i = 1; i <= 9; i++)
    processCircuit(i);

  count++;
}

void turnOn(int circuit, int highVal)
{
  pulsing[circuit - 1] = false;
  asc[circuit - 1] = true;
  done[circuit - 1] = true;
  high[circuit - 1] = highVal;
  
  if (circuit == 4 || circuit == 5 || circuit == 8 || circuit == 9)
  {
    digitalOn[circuit - 1] = count;
  }
  else
  {
    ledState[circuit - 1] = highVal;
  }
}

void turnOff(int circuit, int lowVal)
{
  pulsing[circuit - 1] = false;
  asc[circuit - 1] = false;
  done[circuit - 1] = true;
  low[circuit - 1] = lowVal;
  
  if (circuit == 4 || circuit == 5 || circuit == 8 || circuit == 9)
  {
    digitalOff[circuit - 1] = count;
  }
  else
  {
    ledState[circuit - 1] = lowVal;
  }
}

void fadeIn(int circuit, int lowVal, int highVal, int fadeSpeed)
{
  pulsing[circuit - 1] = false;
  asc[circuit - 1] = true;
  done[circuit - 1] = false;
  low[circuit - 1] = lowVal;
  high[circuit - 1] = highVal;
  inSpeed[circuit - 1] = fadeSpeed;
  
  // Digital
  if (circuit == 4 || circuit == 5 || circuit == 8 || circuit == 9)
  {
    inSpeed[circuit - 1] = ((highVal - lowVal + 1) / fadeSpeed);
    digitalOn[circuit - 1] = count + inSpeed[circuit - 1];
  }
}

void fadeOut(int circuit, int lowVal, int highVal, int fadeSpeed)
{
  pulsing[circuit - 1] = false;
  asc[circuit - 1] = false;
  done[circuit - 1] = false;
  low[circuit - 1] = lowVal;
  high[circuit - 1] = highVal;
  inSpeed[circuit - 1] = fadeSpeed;

  // Digital
  if (circuit == 4 || circuit == 5 || circuit == 8 || circuit == 9)
  {
    outSpeed[circuit - 1] = ((highVal - lowVal + 1) / fadeSpeed);
    digitalOff[circuit - 1] = count + outSpeed[circuit - 1];
  }
}

void pulse(int circuit, int lowVal, int highVal, int fadeInSpeed, int fadeOutSpeed)
{
  pulsing[circuit - 1] = true;
  done[circuit - 1] = false;
  low[circuit - 1] = lowVal;
  high[circuit - 1] = highVal;
  inSpeed[circuit - 1] = fadeInSpeed;
  outSpeed[circuit - 1] = fadeOutSpeed;
  // Digital
  if (circuit == 4 || circuit == 5 || circuit == 8 || circuit == 9)
  {
    inSpeed[circuit - 1] = ((highVal - lowVal + 1) / fadeInSpeed);
    outSpeed[circuit - 1] = ((highVal - lowVal + 1) / fadeOutSpeed);
    digitalOn[circuit - 1] = count + inSpeed[circuit - 1];
    digitalOff[circuit - 1] = count + outSpeed[circuit - 1] + inSpeed[circuit - 1];
  }
}

void processCircuit(int circuit)
{
  // Analog circuits
  if (circuit == 1 || circuit == 2 || circuit == 3 || circuit == 6 || circuit == 7)
  {
    // This circuit should be ascending in value
    if (asc[circuit - 1] && !done[circuit - 1])
    {
      if (ledState[circuit - 1] < high[circuit - 1])
        ledState[circuit - 1] += inSpeed[circuit - 1];
      if (ledState[circuit - 1] >= high[circuit - 1])
      {
        if (pulsing[circuit - 1])
          asc[circuit - 1] = false;
        else
          done[circuit - 1] = true;
        ledState[circuit - 1] = high[circuit - 1];
      }
    }
    
    // This circuit should be descending in value
    else if (!asc[circuit - 1] && !done[circuit - 1])
    {
      if (ledState[circuit - 1] > low[circuit - 1])
        ledState[circuit - 1] -= outSpeed[circuit - 1];
      if (ledState[circuit - 1] <= low[circuit - 1])
      {
        if (pulsing[circuit - 1])
          asc[circuit - 1] = true;
        else
          done[circuit - 1] = true;
        ledState[circuit - 1] = low[circuit - 1];
      }
    }
  }
  
  
  // Digital circuits
  else
  {
    if (count == digitalOn[circuit - 1])
    {
      ledState[circuit - 1] = HIGH;
      if (pulsing[circuit - 1])
      {
        digitalOff[circuit - 1] = digitalOn[circuit - 1] + outSpeed[circuit - 1];
      }
    }
    if (count == digitalOff[circuit - 1])
    {
      ledState[circuit - 1] = LOW;
      if (pulsing[circuit - 1])
      {
        digitalOn[circuit - 1] = digitalOff[circuit - 1] + inSpeed[circuit - 1];
      }
    }
  }
}

