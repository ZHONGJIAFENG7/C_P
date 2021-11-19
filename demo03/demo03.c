#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 3
#define N 1000000

struct board
{
  int chess[SIZE * SIZE];
  int prev;
  int pos;
};

struct eighttile
{
  struct board *q;
  struct board start;
};

struct board get_snapshot(FILE *fp);
void add(struct eighttile *e, struct board b);

int main(int argc, char *argv[])
{
  FILE *fp = NULL;
  int i;
  int j;
  struct eighttile e;
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
  /* 分配无限大的空间 */
  e.q = (struct board *)malloc(sizeof(struct board) * N);
  memset(e.q, 0, sizeof(struct board) * N);

  start = get_snapshot(fp);
  start.prev = -1;
  add(&e, start);

  for (i = 0; i < SIZE; i++)
  {
    for (j = 0; j < SIZE; j++)
    {
      printf("%d", e.q->chess[i * SIZE + j]);
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
  struct eighttile e;

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
      start.pos = i;
    }
    else
    {
      start.chess[i] = ch - '0';
    }

    i++;
  }
  return start;
}

void add(struct eighttile *e, struct board b)
{
  int i;
  for (i = 0; i < SIZE * SIZE; i++)
  {
    e->q->chess[i] = b.chess[i];
  }
  e->q->prev = b.prev;
  e->q->pos = b.pos;
}
