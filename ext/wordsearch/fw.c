#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include "accent.h"
#include "wordfun.h"

int
direct_match(const char *pat, char *str)
{
  int i;

  for (i = 0; pat[i] && str[i]; i++) {
    if (pat[i] == '.')
      continue;
    if (pat[i] == '/' && str[i] == ' ')
      continue;
    if (pat[i] == str[i])
      continue;
    return 0;
  }

  return pat[i] == str[i];  /* both 0 */
}

int
canon_match(const char *pat, char *str)
{
  int i;

  for (i = 0; pat[i] && str[i]; i++) {
    if (pat[i] == '.')
      continue;
    if (pat[i] == str[i])
      continue;
    return 0;
  }

  return pat[i] == str[i];  /* both 0 */
}

int crypto_match(const char *pat, char *str)
{
  int i;
  char key[256];
  char rkey[256];
  memset(key, 0, 256);
  memset(rkey, 0, 256);

  for (i = 0; pat[i] && str[i]; i++) {
    int idx = pat[i];
    int idx2 = str[i];
    char ch = key[idx];
    char ch2 = rkey[idx2];
    if (ch && str[i] != ch) return 0;
    if (ch2 && pat[i] != ch2) return 0;

    key[idx] = str[i];
    rkey[idx2] = pat[i];
  }

  return pat[i] == str[i];  /* both 0 */
}


int
fw_main(const char *pattern, const char *dictfile, int cryptogram, void (*callback)(const char *word)) {
  FILE *fp;
  char buf[100];
  char buf2[100];
  int spaces;
  int c;

  init_accent();

  spaces = strchr(pattern, '/') != 0;

  fp = fopen(dictfile, "r");
  if (fp == 0) {
    perror(dictfile);
    return 1;
  }
  while (fgets(buf, sizeof(buf), fp) != NULL) {
    buf[strlen(buf) - 1] = 0;
    if (cryptogram) {
      canon(buf2, buf, 1);
      if (crypto_match(pattern, buf2)) {
        callback(buf);
      }
    }
    else if (spaces) {
      canon(buf2, buf, 1);
      if (direct_match(pattern, buf2)) {
        callback(buf);
      }
    }
    else {
      canon(buf2, buf, 0);
      if (canon_match(pattern, buf2)) {
        callback(buf);
      }
    }
  }
  fclose(fp);

  return 0;
}
