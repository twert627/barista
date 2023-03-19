#include <stdio.h>
#include <string.h>

#include "cli.h"
#include "utils.h"
#include "upgrade.h"
#include "project.h"
#include "version.h"

#define DEBUG

/* TODO: string is not ANSI compliant/build TUI for better terminal usage */
static const char *usage =
  "----------------------------------------------\n"
  "| barista     <command> [options]            |\n"
  "|                                            |\n"
  "| Options:                                   |\n"
  "|                                            |\n"
  "|   -h, --help     Output this message       |\n"
  "|   -v, --version  Output version number     |\n"
  "|                                            |\n"
  "| Commands:                                  |\n"
  "|                                            |\n"
  "|   -i, --init     Init new project template |\n"
  "|   -up, --upgrade Upgrade barista to latest-|\n"
  "|                   version.                 |\n"
  "----------------------------------------------";

void print_version() {
  if (barista_version && barista_version != NULL) {
    printf("%s\n", barista_version);
  } else {
    printf("Version string not found! Please report this bug...\n");
  }
}

void print_usage() {
  if (usage && usage != NULL) {
    printf("%s\n", usage);
  } else {
    printf("Usage string not found! Please report this bug...\n");
  }
}

/* TODO: Implement table as argument rawr xp */
/* TODO: Calculate NKEYS within the func for multiple table support */

#define MAX_KEYS 100

int key_from_str(char *key, t_symstruct *lookup_table, size_t num_tables) {
  size_t i;
  size_t nkeys = num_tables * MAX_KEYS;
  for (i = 0; i < nkeys; i++) {
      if (strcmp(lookup_table[i].key, key) == 0) {
          return lookup_table[i].value;
      }
   }
   return BAD_ARG;
}
/*
int key_from_str(char *key, t_symstruct *lookup_tables[], size_t num_tables) {
  long unsigned int i, j;

  for (i = 0; i < num_tables; i++) {
    t_symstruct *lookup_table = lookup_tables[i];
    size_t NKEYS = sizeof(lookup_table) / sizeof(t_symstruct);
    printf("DEBUG: NUM KEYS: %ld\n", NKEYS);
    for (j = 0; j < NKEYS; j++) {
      t_symstruct *sym = &lookup_table[j];
      printf("DEBUG: ARG SUPPLIED: %s\n", key);
      if (strcmp(sym->key, key) == 0) {
        printf("%d\n", sym->value);
        return sym->value;
      }
    }
  }
  return BAD_ARG;
}
*/

int parse_args(int argc, char **argv) {

#ifdef DEBUG
  printf("DEBUG: ARG COUNT: %d\n", argc);
#endif
  if (argv[1])
  {
    if (argv[1] == NULL) {
      if (RED)
      {
        printf(RED);
        printf("%s is NULL! exiting with failure...\n", argv[1]);
        printf(reset);
        return 1;
      } else {
        printf("%s is NULL! exiting with failure...\n", argv[1]);
        return 1;
      }
    } else {
      switch (key_from_str(argv[1], lookup_table_cli, num_tables)) {
      case USAGE:
        print_usage();
        break;
      case VERSION:
        print_version();
        break;
      case INIT:
        project_init();
        break;
      case UPGRADE:
        upgrade();
        break;
      default:
        print_usage();
        failure("Invalid arguments! Showing usage...\n");
        break;
      }
    }
  } else {
    failure("argv[1] doesn't exist! exiting with failure...\n");
  }
  return 0;
} 