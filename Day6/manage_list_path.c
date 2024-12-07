#include "day6.h"

void free_list(t_path **list) {
  t_path *iter = *list;
  t_path *toFree;
  while (iter) {
    toFree = iter;
    iter = iter->next;
    free(toFree);
  }
  *list = NULL;
}

static void add_back(t_path **list, t_path *node) {
  t_path *iter = *list;
  while (!((iter->x == node->x) && (iter->y == node->y)) && iter->next) {
    iter = iter->next;
  }
  if ((iter->x == node->x) && (iter->y == node->y)) {
    iter->times_visited++;
    free(node);
  } else {
    iter->next = node;
  }
}

static t_path *new_node(int x, int y) {
  t_path *node = (t_path *)calloc(1, sizeof(t_path));
  if (!node) {
    return (NULL);
  }
  node->x = x;
  node->y = y;
  node->times_visited = 0;
  node->next = NULL;
  return (node);
}

void add_node(t_path **list, int x, int y) {
  if (!(*list)) {
    *list = new_node(x, y);
  } else {
    add_back(list, new_node(x, y));
  }
}

void print_list(t_path *list) {
  int cont = 0;
  while (list) {
    printf("[%d, %d] is repeated: %d\n", list->x, list->y, list->times_visited);
    cont++;
    list = list->next;
  }
  printf("Total: %d\n", cont);
}

int check_five(t_path *list) {
  int ret = 1;
  while (list && ret) {
    if (list->times_visited == 5) {
      // printf("5\n");
      ret = 0;
    }
    list = list->next;
  }
  return (ret);
}

int reset_times(t_path *list) {
  while (list) {
    list->times_visited = 0;
    list = list->next;
  }
}
