#ifndef DAY6_H
#define DAY6_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_point {
  int x;
  int y;
  int dir;
} t_point;

typedef struct s_path {
  int x;
  int y;
  int times_visited;
  struct s_path *next;
} t_path;

void free_list(t_path **list);
void add_node(t_path **list, int x, int y);
void print_list(t_path *list);
int check_five(t_path *list);
int reset_times(t_path *list);

#endif
