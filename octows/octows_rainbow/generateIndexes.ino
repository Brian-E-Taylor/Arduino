void generatePixelIndexes(int rows, int columns)
{
  int i, j;
  
  for (i = 0; i < rows; i++)
  {
    for (j = 0; j < columns; j++)
    {
      // Left 12x12 box
      if (j < columns / 2)
      {
        // Even rows
        if (i % 2 == 0)
          pixels[i][j] = i * columns + columns - (j * 2) - 1 + i;
        // Odd rows
        else
          pixels[i][j] = i * columns + j * 2 + 1 + i;
      }
      
      // Right 12x12 box
      else
      {
        // Odd rows
        if (i % 2)
          pixels[i][j] = 400 + i * columns + (2 * columns) - (j * 2) - 1 + i;
        // Even rows
        else
          pixels[i][j] = 400 + i * columns - columns + j * 2 + 1 + i;
      }
    }
  }
  
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < columns; j++)
    {
      Serial.print("pixels[");
      Serial.print(i);
      Serial.print("][");
      Serial.print(j);
      Serial.print("] = ");
      Serial.println(pixels[i][j]);
    }
  }
}

void set2Pixels(int x, int y, int r, int g, int b)
{
  set2Pixels(x, y, (r << 16) | (g << 8) | b);
}

void set2Pixels(int x, int y, int color)
{
  leds.setPixel(pixels[y][x], color);
  leds.setPixel(pixels[y][x]+1, color);
}
