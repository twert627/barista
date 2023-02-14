#include <stdio.h>

#include "utils.h"

/* TODO: Add sanity/mem safety x3 */
size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
  size_t written;
  written = fwrite(ptr, size, nmemb, stream);
  return written;
}

int copy_file(const char *from, char *to, int binary) {
  int is_binary = binary;
  FILE *file_from = NULL, *file_to = NULL;
  char buffer[8 * 1024]; /* 8kb buffer (8096 bytes/64768 bits) */
  size_t read;

  if (is_binary) {
    file_from = fopen(from, "rb");
  } else if (!is_binary) {
    file_from = fopen(from, "r");
  } else {
    printf("is_binary check isn't yes/no! please report this bug...\n");
    return 0;
  }

  if (!file_from) {
    printf("Can't open source file!\n");
    return 0;
  }

  if (is_binary) {
    file_to = fopen(to, "wb");
  } else if (!is_binary) {
    file_to = fopen(to, "w");
  } else {
    printf("is_binary check isn't yes/no! please report this bug...\n");
    return 0;
  }
  
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