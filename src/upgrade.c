#define _POSIX_C_SOURCE 200809L /* Allows strdup func in ANSI C */
#include <stdio.h>
#include <string.h>

#include "upgrade.h"
#include "parson.h"
#include "http-get.h"
#include "utils.h"
#include "version.h"

#define CURRENT_VERSION_URL                                                    \
  "https://api.github.com/repos/twert627/barista/releases/latest"

const char *fetch_current_version() {
  http_get_response_t *res = http_get(CURRENT_VERSION_URL);
  
  JSON_Value *root_json = NULL;
  JSON_Object *json_object = NULL;
  char *tag_name = NULL;

  if (!res->ok) {
    printf("Couldn't find latest barista release!\n");
    goto cleanup;
  }

  if (!(root_json = json_parse_string(res->data))) {
    printf("Unable to parse JSON response!\n");
    goto cleanup;
  }

  if (!(json_object = json_value_get_object(root_json))) {
    printf("Unable to parse JSON response object!\n");
    goto cleanup;
  }

  tag_name = strdup(json_object_get_string(json_object, "tag_name"));

cleanup:
  if (root_json) {
    json_value_free(root_json);
  }
  http_get_free(res);

  return tag_name;
}

int upgrade() {
  const char *current_version = fetch_current_version();

  char resp[1];

  if (0 != strncmp(barista_version, current_version, strlen(current_version) + 1)) {
    printf("New version found!..\n");
    scanf("%s", resp);
  } else if (0 == strncmp(resp, "N", 1) || 0 == strncmp(resp, "n", 1)) {
    printf("Ok, not upgrading");
    return 0;
  } else {

  }
  return 0;
}