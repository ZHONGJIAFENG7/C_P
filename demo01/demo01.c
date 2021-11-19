#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  FILE *fp = NULL;
  int ch;

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

  while (1)
  {
    ch = fgetc(fp);
    if (feof(fp))
    {
      break;
    }
    printf("%c", ch);
  }

  fclose(fp);

  return 0;
}
