#include <stdio.h>
#include <stdlib.h>
#define SIZE 3

struct board
{
  int chess[SIZE * SIZE];
};
struct board get_snapshot(FILE *fp);

int main(int argc, char *argv[])
{
  FILE *fp = NULL;
  int i;
  int j;
  struct board start;

  if (argc != 2)
  {
    fprintf(stderr, "argument error!\n");
    exit(EXIT_FAILURE);
  }
  if ((fp = fopen(argv[1], "r")) == NULL)
  {
    fprintf(stderr, "file is null!");
    exit(EXIT_FAILURE);
  }

  start = get_snapshot(fp);

  for (i = 0; i < SIZE; i++)
  {
    for (j = 0; j < SIZE; j++)
    {
      printf("%d", start.chess[i * SIZE + j]);
    }
    printf("\n");
  }

  fclose(fp);

  return 0;
}

struct board get_snapshot(FILE *fp)
{
  char ch;
  int i = 0;
  struct board start;

  /* 获取1-8的数字 */
  while ((ch = fgetc(fp)) != EOF)
  {
    if (ch == '\n' || ch == '\r')
    {
      continue;
    }

    /* 如果遇到为空则用0进行标识 */
    if (ch == ' ')
    {
      start.chess[i] = 0;
    }
    else
    {
      start.chess[i] = ch - '0';
    }

    i++;
  }
  return start;
}
