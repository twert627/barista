#include <stdio.h>
#include <string.h>

#include "project.h"
#include "cli.h"
#include "utils.h"

/* TODO: Implement boolean flags for project settings */

int project_init() {
  char project_name[100];
  char *project_lang = NULL;
  int len = 0;

  printf("Barista project manager\n");

  printf("Please input project name...\n");
  /* TODO: Check for spaces, if so, concat (meow) the string */
  scanf("%s", project_name);
  len = strlen(project_name);
  if (len > 100) {
    failure("ERROR: Project name has 100 char limit!\n");
  } 
  len = 0;
  /* TODO: Create symstruct that holds available options && list them */
  printf("Please input project language...\n");

  scanf("%s", project_lang);
  len = strlen(project_lang);
  if (len > 100) {
    failure("ERROR: Project language has 100 char limit!\n");
  }
  switch (key_from_str(project_lang, lookup_langtable, num_tables)) {
  case C:
    printf("%d selected\n", key_from_str(project_lang, lookup_langtable, num_tables));
    break;
  case RUST:
    printf("%d selected\n", key_from_str(project_lang, lookup_langtable, num_tables));
    break;
  case JAVASCRIPT:
    printf("%d selected\n", key_from_str(project_lang, lookup_langtable, num_tables));
    break;
  default:
    printf("%d selected\n", key_from_str(project_lang, lookup_langtable, num_tables));
    break;
  }  
  return 0;
}