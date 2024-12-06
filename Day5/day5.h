#ifndef DAY5_H_
#define DAY5_H_

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_list_pair {
  int prev;
  int aft;
  struct s_list_pair *next;
} t_list_pair;

typedef struct s_list_elem {
  int *list;
  int len;
  int ok;
  struct s_list_elem *next;
} t_list_elem;

/**
 * LIST_PAIR_MANAGEMENT.C
 */
void free_list_pair(t_list_pair **list);
void gen_list_pair(t_list_pair **list, char *argv);
void print_list_pair(t_list_pair *list);

/**
 * LIST_ELEM_MANAGEMENT.C
 */
void free_list_elem(t_list_elem **list);
void gen_list_elem(t_list_elem **list, int argc, char **argv);
void print_list_elem(t_list_elem *list);

/**
 * UTILS.C
 */
int digit_len(char *str);

#endif
