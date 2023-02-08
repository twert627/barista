#include <stdio.h>

#include "utils.h"

int copy_file(const char *from, char *to) {
  FILE *file_from, *file_to;
  char buffer[8 * 1024]; /* 8kb buffer */
  size_t read;

  file_from = fopen(from, "r");
  if (!file_from) {
    printf("Can't open source file!\n");
    return 0;
  }

  file_to = fopen(to, "w");
  if (!file_to) {
    printf("Can't open destination file!\n");
    return 0;
  }

  read = 0;

  while((read = fread(buffer, 1, sizeof(buffer), file_from))) {
    fwrite(buffer, 1, read, file_to);
  }

  fclose(file_from);
  fclose(file_to);
  return 1;
}