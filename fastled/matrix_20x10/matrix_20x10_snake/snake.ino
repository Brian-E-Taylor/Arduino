void chooseNewDirection()
{
  do
    dir = random(4);
  while (oldDir == dir);
  oldDir = dir;
}

void drawSnake(int h, int s, int v, boolean on)
{
  if (on)
  {
    if (random(100) <= 75)
    {
      hue++;
      backHue++;
    }
    
    for (int i = 0; i < SNAKE_SIZE; i++)
    {
      leds[snake[i]] = CHSV(h, s, v - (i * (200 / SNAKE_SIZE)));
    }
  }
/*
  else
  {
    for (int i = 0; i < SNAKE_SIZE; i++)
    {
      leds[snake[i]] = CHSV(h, s, 20);
    }
  }
*/
}

void moveSnake()
{
  switch (dir)
  {
    case 0:
      if (head_y - 1 < 0 || isWall(head_x, head_y - 1) /* || isSnakePresent(x, y-1) */)
      {
        chooseNewDirection();
      }
      else
      {
        drawSnake(backHue, sat, val, 0);

        head_y--;
        for (int i = SNAKE_SIZE-1; i > 0; i--)
        {
          snake[i] = snake[i-1];
        }
        snake[0] = indexes[head_y][head_x];        

        drawSnake(hue, sat, val, 1);
      }
      break;

    case 1:
      if (head_x + 1 >= COLUMNS || isWall(head_x + 1, head_y) /* || isSnakePresent(x+1, y) */)
      {
        chooseNewDirection();
      }
      else
      {
        drawSnake(backHue, sat, val, 0);

        head_x++;
        for (int i = SNAKE_SIZE-1; i > 0; i--)
        {
          snake[i] = snake[i-1];
        }
        snake[0] = indexes[head_y][head_x];        

        drawSnake(hue, sat, val, 1);
      }
      break;

    case 2:
      if (head_y + 1 >= ROWS || isWall(head_x, head_y + 1) /* || isSnakePresent(x, y+1) */)
      {
        chooseNewDirection();
      }
      else
      {
        drawSnake(backHue, sat, val, 0);

        head_y++;
        for (int i = SNAKE_SIZE-1; i > 0; i--)
        {
          snake[i] = snake[i-1];
        }
        snake[0] = indexes[head_y][head_x];        

        drawSnake(hue, sat, val, 1);
      }
      break;

    case 3:
      if (head_x - 1 < 0 || isWall(head_x - 1, head_y) /* || isSnakePresent(x-1, y) */)
      {
        chooseNewDirection();
      }
      else
      {
        drawSnake(backHue, sat, val, 0);

        head_x--;
        for (int i = SNAKE_SIZE-1; i > 0; i--)
        {
          snake[i] = snake[i-1];
        }
        snake[0] = indexes[head_y][head_x];        

        drawSnake(hue, sat, val, 1);
      }
      break;
  }
}

boolean isSnakePresent(int x, int y)
{
  for (int i = 0; i < SNAKE_SIZE; i++)
  {
    if (snake[i] == indexes[y][x])
      return true;
  }
  return false;
}

