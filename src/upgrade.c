#define _POSIX_C_SOURCE 200809L /* Allows strdup func in ANSI C */
#include <stdio.h>
#include <string.h>

#include "upgrade.h"
#include "parson.h"
#include "http-get.h"
#include "utils.h"
#include "version.h"

#define DEBUG /* Remove on release */

#ifdef DEBUG                                                          
#define CURRENT_VERSION_URL "https://api.github.com/repos/twert627/xbrew/releases/latest" /* Use xbrew for testing API connectivity in pre-release */
#define BARISTA_ASSET_URL "https://github.com/twert627/xbrew/releases/download/"
#else 
#define CURRENT_VERSION_URL "https://api.github.com/repos/twert627/barista/releases/latest"
#define BARISTA_ASSET_URL "https://github.com/twert627/barista/releases/download/"
#endif



const char *fetch_current_version() {
  http_get_response_t *res = http_get(CURRENT_VERSION_URL);
  
  JSON_Value *root_json = NULL;
  JSON_Object *json_object = NULL;
  char *tag_name = NULL;

  if (!res->ok) {
    printf(RED);
    printf("Couldn't find latest barista release!\n");
    printf(reset);
    goto cleanup;
  }

  if (!(root_json = json_parse_string(res->data))) {
    printf(RED);
    printf("Unable to parse JSON response!\n");
    printf(reset);
    goto cleanup;
  }

  if (!(json_object = json_value_get_object(root_json))) {
    printf(RED);
    printf("Unable to parse JSON response object!\n");
    printf(reset);
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

int fetch_current_package(void) {
  FILE *fp;
  char resp[1], release_asset[256];
  const char *release_version = fetch_current_version();

  strcpy(release_asset, BARISTA_ASSET_URL);
  strcat(release_asset, release_version);
  strcat(release_asset, "/barista");
  printf("%s\n", release_asset);

  http_get_file(release_asset, "barista");
  fp = fopen("barista", "rb");
  if (fp == NULL) {
    failure("Failed to download release! Please report this bug...\n");
  } else {
    printf(BLU);
    printf("barista version: %s downloaded.\n", release_version);
    printf("Would you like to install [Y/n]\n");
    printf(reset);

    scanf("%s", resp);
    if (0 == strncmp(resp, "Y", 1) || 0 == strncmp(resp, "y", 1)) {
      printf("Installing barista version %s\n", release_version);
      copy_file("barista", "/usr/bin/barista", 1);
    } else if (0 == strncmp(resp, "N", 1) || 0 == strncmp(resp, "n", 1)) {
      info("Not installing...\n");
      return 0;
    } else {
      failure("ERROR: Invalid input!\n");
    }
  }
  return 0;
}

int upgrade() {
  const char *current_version = fetch_current_version();
  char resp[1];

  /* TODO: Check version string to only include newer versions </3 */
  if (0 != strncmp(barista_version, current_version, strlen(current_version) + 1)) {
    info("New version found!\n");

    printf(YEL);
    printf("Would you like to download version %s? [Y/n]\n", current_version);
    printf(reset);

    scanf("%s", resp);
    if (0 == strncmp(resp, "Y", 1) || 0 == strncmp(resp, "y", 1)) {
      printf("Updgrading barista to %s from %s...\n", current_version, barista_version);
      fetch_current_package();
    } else if (0 == strncmp(resp, "N", 1) || 0 == strncmp(resp, "n", 1)) {
    printf("Ok, not upgrading");
    return 0;
  } else {
    failure("Invalid input!\n");
  }
 }
  return 0;
}