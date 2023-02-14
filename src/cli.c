#include <stdio.h>
#include <string.h>

#include "cli.h"
#include "utils.h"
#include "upgrade.h"
#include "version.h"

/* TODO: string is not ANSI compliant/build TUI for better terminal usage*/
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

/* ghetto hash map */
t_symstruct lookup_table[] = {
  { "h",           USAGE },
  { "-h",          USAGE },
  { "help",        USAGE },
  { "--help",      USAGE },
  { "v",         VERSION },
  { "-v",        VERSION },
  { "version",   VERSION },
  { "--version", VERSION },
  { "i",            INIT },
  { "-i",           INIT },
  { "init",         INIT },
  { "--init",       INIT },
  { "u",         UPGRADE },
  { "-u",        UPGRADE },
  { "up",        UPGRADE },
  { "--up",      UPGRADE },
  { "upgrade",   UPGRADE },
  { "--upgrade", UPGRADE }
};

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

int key_from_str(char *key) {
  long unsigned int i;
  for (i = 0; i < NKEYS; i++) {
    t_symstruct *sym = &lookup_table[i];
    if (strcmp(sym->key, key) == 0)
      return sym->value;
  }
    return BAD_ARG;
}

int parse_args(int argc, char **argv) {
#ifdef DEBUG
  printf("ARG COUNT: %d\n", argc);
#endif
  if (!argv[1]) {
    printf("Arg count is not greater than or equal to 2!\n");
    return 0;
  } else if (argv[1]) {
    if (argv[1] != NULL) {
      switch (key_from_str(argv[1])) {
      case USAGE:
        print_usage();
        return 0;
      case VERSION:
        print_version();
        return 0;
      case INIT:
        printf("Init command ran...\n");
        return 0;
      case UPGRADE:
        upgrade();
        return 0;
      default:
        printf("Invalid arguments! Showing usage.\n");
        print_usage();
        return 1;
    }
    } else {
      printf("%s is NULL! exiting with failure...\n", argv[1]);
      return 1;
    }
  } else { /* For some reason, this block is never reached even if !argv[1] */
    printf("No arguments supplied! exiting...\n");
    return 1;
  }
  printf("Test....\n");
}