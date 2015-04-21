int HSVtoRGB(int hue, int sat, int val)
{
  int r, g, b, base;
  
  // hue: 0-359, sat: 0-255, val (lightness): 0-255

  // Loop hue circularly
  hue = hue % 360;
  
  // Clamp max saturation
  if (sat > 255)
    sat = 255;

  // Clamp min and max value
  if (val < 0)
    val = 0;
  if (val > 255)
    val = 255;

  if (sat <= 0)
  {
    r = val;
    g = val;
    b = val;
  }
  else
  {
    base = ((255 - sat) * val) >> 8;
    
    switch (hue / 60)
    {
      case 0:
        r = val;
        g = (((val - base) * hue) / 60) + base;
        b = base;
        break;
      case 1:
        r = (((val - base) * (60 - (hue % 60))) / 60) + base;
        g = val;
        b = base;
        break;
      case 2:
        r = base;
        g = val;
        b = (((val - base) * (hue % 60)) / 60) + base;
        break;
      case 3:
        r = base;
        g = (((val - base) * (60 - (hue % 60))) / 60) + base;
        b = val;
        break;
      case 4:
        r = (((val - base) * (hue % 60)) / 60) + base;
        g = base;
        b = val;
        break;
      case 5:
        r = val;
        g = base;
        b = (((val - base) * (60 - (hue % 60))) / 60) + base;
        break;
    }
  }
  
  return (r << 16) | (g << 8) | b;
}
