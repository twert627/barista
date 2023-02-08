#ifndef CLI_H
#define CLI_H

/* arg definitions */
#define USAGE    1
#define VERSION  2
#define INIT     3
#define BAD_ARG -1

int parse_args(int argc, char **argv);
void print_usage(void);
void print_version(void);

#endif