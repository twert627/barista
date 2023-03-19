#ifndef UTILS_H
#define UTILS_H

#include "cli.h"
#include "project.h"

typedef struct {
  char *key;
  int value;
} t_symstruct;


/* ghetto hash map dictonary */
static t_symstruct lookup_table_cli[] = {
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

static t_symstruct lookup_langtable[] = {
  { "c",                    C },
  { "C",                    C },
  { "rust",              RUST },
  { "Rust",              RUST },
  { "javascript",  JAVASCRIPT },
  { "JavaScript",  JAVASCRIPT },
  { "js",          JAVASCRIPT },
  { "JS",          JAVASCRIPT }
};


static t_symstruct *lookup_tables[] = { lookup_table_cli, lookup_langtable };

static size_t num_tables = sizeof(lookup_tables) / sizeof(t_symstruct *);


/* String to int with dictionary */

int key_from_str(char *key, t_symstruct *lookup_tables, size_t num_tables);

/* File system util functions */
int create_file(const char *name, int binary);
int copy_file(const char *from, char *to, int binary);
size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream);

/* Logging utils*/
int init_log(void);

void sucess(const char *str);
void warning(const char *str);
int failure(const char *str);
void info(const char *str);

/* Colors! [https://gist.github.com/RabaDabaDoba/145049536f815903c79944599c6f952a] */
/* ASCI escape color codes, modified by twert for ANSI compliance */

/* Regular text */
#define BLK "\033[0;30m"
#define RED "\033[0;31m"
#define GRN "\033[0;32m"
#define YEL "\033[0;33m"
#define BLU "\033[0;34m"
#define MAG "\033[0;35m"
#define CYN "\033[0;36m"
#define WHT "\033[0;37m"

/* Regular bold text */
#define BBLK "\033[1;30m"
#define BRED "\033[1;31m"
#define BGRN "\033[1;32m"
#define BYEL "\033[1;33m"
#define BBLU "\033[1;34m"
#define BMAG "\033[1;35m"
#define BCYN "\033[1;36m"
#define BWHT "\033[1;37m"

/* Regular underline text */
#define UBLK "\033[4;30m"
#define URED "\033[4;31m"
#define UGRN "\033[4;32m"
#define UYEL "\033[4;33m"
#define UBLU "\033[4;34m"
#define UMAG "\033[4;35m"
#define UCYN "\033[4;36m"
#define UWHT "\033[4;37m"

/* Regular background */
#define BLKB "\033[40m"
#define REDB "\033[41m"
#define GRNB "\033[42m"
#define YELB "\033[43m"
#define BLUB "\033[44m"
#define MAGB "\033[45m"
#define CYNB "\033[46m"
#define WHTB "\033[47m"

/* High intensty background */
#define BLKHB "\033[0;100m"
#define REDHB "\033[0;101m"
#define GRNHB "\033[0;102m"
#define YELHB "\033[0;103m"
#define BLUHB "\033[0;104m"
#define MAGHB "\033[0;105m"
#define CYNHB "\033[0;106m"
#define WHTHB "\033[0;107m"

/* High intensty text */
#define HBLK "\033[0;90m"
#define HRED "\033[0;91m"
#define HGRN "\033[0;92m"
#define HYEL "\033[0;93m"
#define HBLU "\033[0;94m"
#define HMAG "\033[0;95m"
#define HCYN "\033[0;96m"
#define HWHT "\033[0;97m"

/* Bold high intensity text */
#define BHBLK "\033[1;90m"
#define BHRED "\033[1;91m"
#define BHGRN "\033[1;92m"
#define BHYEL "\033[1;93m"
#define BHBLU "\033[1;94m"
#define BHMAG "\033[1;95m"
#define BHCYN "\033[1;96m"
#define BHWHT "\033[1;97m"

/* Reset */
#define reset "\033[0m"
#define CRESET "\033[0m"
#define COLOR_RESET "\033[0m"

#endif