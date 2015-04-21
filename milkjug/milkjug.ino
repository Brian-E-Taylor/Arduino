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

boolean asc1 = false;
boolean asc2 = false;
boolean asc3 = false;
boolean asc6 = false;
boolean asc7 = false;

boolean done1 = true;
boolean done2 = true;
boolean done3 = true;
boolean done6 = true;
boolean done7 = true;

boolean pulse3 = false;

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
  analogWrite(circuit1pwm, ledState1);
  analogWrite(circuit2pwm, ledState2);
  analogWrite(circuit3pwm, ledState3);
  analogWrite(circuit6pwm, ledState6);
  analogWrite(circuit7pwm, ledState7);

  // DIGITAL
//  digitalWrite(circuit1pwm, ledState1);
//  digitalWrite(circuit2pwm, ledState2);
//  digitalWrite(circuit3pwm, ledState3);
//  digitalWrite(circuit6pwm, ledState6);
//  digitalWrite(circuit7pwm, ledState7);
  digitalWrite(circuit4, ledState4);
  digitalWrite(circuit5, ledState5);
  digitalWrite(circuit8, ledState8);
  digitalWrite(circuit9, ledState9);
  
  delay(10);

/*  
  processCircuit1();
  processCircuit2();
  processCircuit3();
  processCircuit4();
  processCircuit5();
  processCircuit6();
  processCircuit7();
  processCircuit8();
  processCircuit9();
*/

  if (count == 10)
  {
    asc1 = true;
    done1 = false;
  }
  if (count == 70)
  {
    asc3 = true;
    done3 = false;
  }
  if (count == 250)
  {
    asc1 = false;
    done1 = false;
  }
  if (count == 400)
  {
    asc2 = true;
    done2 = false;
  }
  if (count == 800)
  {
    asc1 = true;
    done1 = false;
  }
  if (count > 1000 && count % 100 == 0)
  {
    asc2 = !asc2;
    done2 = false;
  }
  if (count > 1000 && count < 1400 && count % 120 == 0)
  {
    asc1 = !asc1;
    done1 = false;
  }
  if (count == 1400)
  {
    asc1 = false;
    done1 = false;
    asc6 = true;
    done6 = false;
  }
  if (count == 1420)
  {
    asc7 = true;
    done7 = false;
  }
  if (count > 1500 && count % 200 == 0)
  {
    diagonal1();
  }
  if (count > 1500 && count % 205 == 0)
  {
    diagonal2();
  }
  if (count > 1700 && count % 300 == 0)
  {
    asc7 = !asc7;
    done7 = false;
  }
  if (count > 1700 && count % 280 == 0)
  {
    asc6 = !asc6;
    done6 = false;
  }
  
  outerSquare1();
  innerSquare1();
  middleLight();
  inner1();
  inner2();

/*  
  if (count == 1000)
  {
    innerSquare1();
  }
  
  if (count == 1200)
  {
    outerSquare1();
  }
  
  if (count > 200)
  {
    processCircuit3();
  }
*/
  count++;
  if (count == 3000)
  {
    ledState4 = LOW;
    ledState5 = LOW;
    ledState8 = LOW;
    ledState9 = LOW;
    count = 10;
  }
}

void outerSquare1()
{
  if (asc1 && !done1)
  {
    if (ledState1 < 255)
      ledState1 += 4;
    if (ledState1 >= 255)
    {
      done1 = true;
      ledState1 = 255;
    }
  }
  if (!asc1 && !done1)
  {
    if (ledState1 > 0)
      ledState1 -= 2;
    if (ledState1 <= 0)
    {
      done1 = true;
      ledState1 = 0;
    }
  }
}

void outerSquare2()
{
  ledState4 = !ledState4;
  ledState5 = !ledState5;
  ledState8 = !ledState8;
  ledState9 = !ledState9;
}

void innerSquare1()
{
  if (asc2 && !done2)
  {
    if (ledState2 < 255)
      ledState2+=3;
    if (ledState2 >= 255)
    {
      done2 = true;
      ledState2 = 255;
    }
  }
  if (!asc2 && !done2)
  {
    if (ledState2 > 0)
      ledState2 -= 2;
    if (ledState2 <= 0)
    {
      done2 = true;
      ledState2 = 0;
    }
  }
}

void middleLight()
{
  if (asc3 && !done3)
  {
    if (ledState3 < 255)
      ledState3++;
    if (ledState3 == 255)
    {
      done3 = true;
      pulse3 = true;
      return;
    }
  }
  if (!asc3 && !done3)
  {
    if (ledState3 != 0)
      ledState3--;
    if (ledState3 == 0)
      done3 = true;
  }
  if (pulse3 && done3)
  {
    if (asc3)
    {
      if (ledState3 < 255)
        ledState3 += 3;
      if (ledState3 >= 255)
      {
        asc3 = false;
        ledState3 = 255;
      }
    }
    else
    {
      if (ledState3 > 0)
        ledState3 -= 2;
      if (ledState3 <= 0)
      {
        asc3 = true;
        ledState3 = 150;
      }
    }
  }
}

void diagonal1()
{
  ledState4 = !ledState4;
  ledState5 = !ledState5;
}

void diagonal2()
{
  ledState8 = !ledState8;
  ledState9 = !ledState9;
}

void inner1()
{
  if (asc6 && !done6)
  {
    if (ledState6 < 255)
      ledState6+=3;
    if (ledState6 >= 255)
    {
      done6 = true;
      ledState6 = 255;
    }
  }
  if (!asc6 && !done6)
  {
    if (ledState6 > 0)
      ledState6 -= 2;
    if (ledState6 <= 0)
    {
      done6 = true;
      ledState6 = 0;
    }
  }
}

void inner2()
{
  if (asc7 && !done7)
  {
    if (ledState7 < 255)
      ledState7+=3;
    if (ledState7 >= 255)
    {
      done7 = true;
      ledState7 = 255;
    }
  }
  if (!asc7 && !done7)
  {
    if (ledState7 > 0)
      ledState7 -= 2;
    if (ledState7 <= 0)
    {
      done7 = true;
      ledState7 = 0;
    }
  }
}

// ANALOG OUT
void processCircuit1()
{
  if (asc1)
  {
    ledState1++;
    if (ledState1 == 255)
      asc1 = false;
  }
  else
  {
    ledState1--;
    if (ledState1 == 0)
      asc1 = true;
  }
}

// ANALOG OUT
void processCircuit2()
{
  if (asc2)
  {
    ledState2 += 2;
    if (ledState2 == 254)
      asc2 = false;
  }
  else
  {
    ledState2 -= 2;
    if (ledState2 == 0)
      asc2 = true;
  }
}

// ANALOG OUT
void processCircuit3()
{
  if (asc3)
  {
    ledState3 += 2;
    if (ledState3 == 252)
      asc3 = false;
  }
  else
  {
    ledState3 -= 4;
    if (ledState3 == 0)
      asc3 = true;
  }
}

// DIGITAL OUT
void processCircuit4()
{
  if (count % 100 == 0)
    ledState4 = !ledState4;
}

// DIGITAL OUT
void processCircuit5()
{
  if (count % 200 == 0)
    ledState5 = !ledState5; 
}

// ANALOG OUT
void processCircuit6()
{
  if (asc6)
  {
    ledState6 += 2;
    if (ledState6 == 254)
      asc6 = false;
  }
  else
  {
    ledState6 -= 2;
    if (ledState6 == 0)
      asc6 = true;
  }
  if (count % 50 == 0 && ledState6 != 254 && ledState6 != 0)
    asc6 = !asc6;
}

// ANALOG OUT
void processCircuit7()
{
  if (asc7)
  {
    ledState7 += 4;
    if (ledState7 == 252)
      asc7 = false;
  }
  else
  {
    ledState7 -= 4;
    if (ledState7 == 0)
      asc7 = true;
  }
  if (count % 100 == 0 && ledState7 != 252 && ledState7 != 0)
    asc7 = !asc7;
}

// DIGITAL OUT
void processCircuit8()
{
  if (count % 50 == 0)
    ledState8 = !ledState8;
}

// DIGITAL OUT
void processCircuit9()
{
  if (count % 50 == 0)
    ledState9 = !ledState9;
}

