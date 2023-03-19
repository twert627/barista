#ifndef PROJECT_H
#define PROJECT_H

/* Project language options (always able to add more) */
#define C           1
#define RUST        2
#define CPP         3
#define JAVASCRIPT  4

#define NKEYS_LANG (sizeof(lookup_langtable) / sizeof(t_symstruct))

int project_init(void);

#endif