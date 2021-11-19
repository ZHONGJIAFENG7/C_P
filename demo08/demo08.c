#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 3
#define N 1000000
int COUNT = 0;

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
  int first;
  int end;
  int min_step;
  int best_pos;
};

struct board get_snapshot(FILE *fp);
void add(struct eighttile *e, struct board b);
void search_path(struct eighttile *e);
void pop(struct eighttile *e, struct board *b);
int is_solved(struct board b);
void find_neighbor(struct board b, struct eighttile *e);
void swap(int *a, int *b);
int can_insert(struct eighttile *e, struct board b);
void exchange(struct board b, struct eighttile *e, int i, int j);
void copy(struct board *dest, struct board *source);
int get_step(struct eighttile *e, int b);

int main(int argc, char *argv[])
{
  FILE *fp = NULL;
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
  e.first = 0;
  e.end = 0;

  start = get_snapshot(fp);
  start.prev = -1;
  add(&e, start);
  search_path(&e);

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
    e->q[e->end].chess[i] = b.chess[i];
  }
  e->q[e->end].prev = b.prev;
  e->q[e->end].pos = b.pos;
  e->end++;
}

void pop(struct eighttile *e, struct board *b)
{
  int i;
  for (i = 0; i < SIZE * SIZE; i++)
  {
    b->chess[i] = e->q[e->first].chess[i];
  }
  b->pos = e->q[e->first].pos;
  b->prev = e->q[e->first].prev;
  e->first++;
}

void search_path(struct eighttile *e)
{
  struct board b;
  int step;
  while (e->end != e->first)
  {
    pop(e, &b);
    if (is_solved(b))
    {
      step = get_step(e, e->first - 1);
      if (COUNT < 1)
      {
        COUNT++;
        printf("%d", step);
      }
      if (e->min_step > step)
      {
        e->min_step = step;
        e->best_pos = e->first - 1;
      }
      return;
    }
    find_neighbor(b, e);
  }
}

int is_solved(struct board b)
{
  int i;
  if (b.chess[SIZE * SIZE - 1] != 0)
  {
    return 0;
  }

  for (i = 0; i < SIZE * SIZE - 1; i++)
  {
    if (b.chess[i] != i + 1)
    {
      return 0;
    }
  }

  return 1;
}

void find_neighbor(struct board b, struct eighttile *e)
{
  /* 获取空格所在行 */
  int i = b.pos / SIZE;
  /* 获取空格所在列 */
  int j = b.pos % SIZE;

  if (i - 1 >= 0)
  {
    exchange(b, e, i - 1, j);
  }

  if (i + 1 < SIZE)
  {
    exchange(b, e, i + 1, j);
  }

  if (j - 1 >= 0)
  {
    exchange(b, e, i, j - 1);
  }

  if (j + 1 < SIZE)
  {
    exchange(b, e, i, j + 1);
  }
}

void swap(int *a, int *b)
{
  int tmp;
  tmp = *a;
  *a = *b;
  *b = tmp;
}

int can_insert(struct eighttile *e, struct board b)
{
  int i, j;

  for (i = e->first; i != e->end;)
  {
    for (j = 0; j < SIZE * SIZE; j++)
    {
      if (b.chess[j] != e->q[i].chess[j])
      {
        break;
      }
    }
    if (j == SIZE * SIZE)
    {
      break;
    }
    i++;
  }

  if (i == e->end)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

void exchange(struct board b, struct eighttile *e, int i, int j)
{
  /* 1. 保存原先镜像 */
  struct board nb;
  copy(&nb, &b);

  /* swap */
  swap(&nb.chess[nb.pos], &nb.chess[i * SIZE + j]);

  /* 更新pos */
  nb.pos = i * SIZE + j;

  /* 更新prev */
  nb.prev = e->first - 1;

  /* 判断当前镜像是否有存在于队列中 */
  if (can_insert(e, nb))
  {
    add(e, nb);
  }
}

void copy(struct board *dest, struct board *source)
{
  int i;
  for (i = 0; i < SIZE * SIZE; i++)
  {
    dest->chess[i] = source->chess[i];
  }
  dest->pos = source->pos;
  dest->prev = source->prev;
}

int get_step(struct eighttile *e, int b)
{
  if (b > 0)
  {
    return get_step(e, e->q[b].prev) + 1;
  }
  else
  {
    return 0;
  }
}
