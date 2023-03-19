#include <stdio.h>

#include "utils.h"

/*///////////////// File System Utils ///////////////////////*/

/* TODO: 
- Add sanity/mem safety x3 
- Assign is_binary check string into #define variable
*/
size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
  size_t written;
  written = fwrite(ptr, size, nmemb, stream);
  return written;
}

int create_file(const char *name, int binary) {
  FILE *file = NULL;
  int is_binary = binary;

  if (is_binary) {
    file = fopen(name, "wb");
  } else if (!is_binary) {
    file = fopen(name, "w");
  } else {
    printf("is_binary check isn't yes/no! Please report this bug...\n");
    return 0;
  }

  if (!file) {
    printf("Failed to create file! Please report this bug...\n");
    return 0;
  } else {
    printf("File %s created successfully\n", name);
  }

  fclose(file);
  file = NULL;
  
  return 1;
}

int copy_file(const char *from, char *to, int binary) {
  int is_binary = binary;
  FILE *file_from = NULL, *file_to = NULL;
  char buffer[8 * 1024]; /* 8kb buffer (8096 bytes/64768 bits) [standard size] */
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

/*///////////////// Logging Utils ///////////////////////*/

int init_log() {
  #ifdef DEBUG
    printf("Initiating logging...\n");
  #endif
  create_file("log.txt", 0);
  
  return 0;
}

/* TODO: support formatted strings */
const char *missing_color_str = "Color not defined, can't print in color!\n";

void success(const char *str) {
  if (str == NULL) {
    if (RED)
    {
      printf(RED);
      printf("String is NULL!\n");
      printf(reset);
    } else {
      printf("%s", missing_color_str);
      printf("String is NULL!\n");
    }
  } else {
    if (BLU)
    {
      printf(BLU);
      printf("%s", str);
      printf(reset);

    } else {
      printf("%s", missing_color_str);
      printf("%s", str);
    }
  }
}

void warning(const char *str) {
  if (str == NULL) {
    if (RED)
    {
      printf(RED);
      printf("String is NULL!\n");
      printf(reset);
    } else {
      printf("%s", missing_color_str);
      printf("String is NULL!\n");
    }
  } else {
    if (YEL)
    {
      printf(YEL);
      printf("%s", str);
      printf(reset);
    } else {
      printf("%s", missing_color_str);
      printf("%s", str);
    }
  }
}

/* Maybe TODO: concat <exiting with failure...> to end of string */
int failure(const char *str) {
  if (str == NULL)
  {
    if (RED)
    {
      printf(RED);
      printf("String is NULL!\n");
      printf(reset);
      return 1;
    } else {
      printf("%s\n", missing_color_str);
      printf("String is NULL!\n");
      return 1;
    }
  } else {
    if (RED)
    {
      printf(RED);
      printf("%s\n", str);
      printf(reset);
      return 1;
    } else {
      printf("%s\n", missing_color_str);
      printf("%s\n", str);
      return 1;
    }
  }
  /* Never reached */
  return 1;
}

void info(const char *str) {
  if (str == NULL) {
    if (RED)
    {
      printf(RED);
      printf("String is NULL!\n");
      printf(reset);
    } else {
      printf("%s\n", missing_color_str);
      printf("String is NULL!\n");
    }
  } else {
    if (BLU)
    {
      printf(BLU);
      printf("%s\n", str);
      printf(reset);
    } else {
      printf("%s\n", missing_color_str);
      printf("%s\n", str);
    }
  }
}