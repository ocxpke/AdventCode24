#ifndef DAY9_H
#define DAY9_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_nums {
  long long iden;
  int len;
  int back_passed;
  struct s_nums *next;
} t_nums;

void gen_list(t_nums **list, long long *full_arr, long long full_size);
void print_list(t_nums *list);
void free_list(t_nums **list);

#endif
