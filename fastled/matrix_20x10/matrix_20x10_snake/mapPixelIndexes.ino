void mapPixelIndexes(int rows, int columns)
{
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < columns; j++)
    {
      if (i % 2)
      {
        indexes[i][j] = i * columns + columns - 1 - j;
      }
      else
      {
        indexes[i][j] = i * columns + j;
      }
    }
  }
}
