#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include "accent.h"
#include "wordfun.h"

static int
cmp_char(const void *a, const void *b)
{
  const char *aa = (char *)a;
  const char *bb = (char *)b;

  return *aa - *bb;
}


int
canon_sort(char *dst, char *str, int expectlen)
{
  int len = canon(dst, str, 0);
  if (expectlen >= 0 && len != expectlen)
    return 1;

  qsort(dst, len, 1, cmp_char);
  return 0;
}

static char *filename = DICT;

int
an_main(char *pattern, char *dictfile, void(*callback)(const char *word)) {
  FILE *fp;
  char an[100];
  char buf[100];
  char buf2[100];
  int anlen;
  int c;

  init_accent();
  canon_sort(an, pattern, -1);
  anlen = strlen(an);

  fp = fopen(dictfile, "r");
  if (fp == 0) {
    perror(dictfile);
    return 1;
  }
  while (fgets(buf, sizeof(buf), fp) != NULL) {
    if (canon_sort(buf2, buf, anlen))
      continue;
    if (strcmp(an, buf2) == 0) {
      /* fputs(buf, stdout); */
      buf[strlen(buf) - 1] = 0;
      callback(buf);
    }
  }
  fclose(fp);

  return 0;
}
