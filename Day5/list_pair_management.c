#include "day5.h"

static void add_node_pair(t_list_pair **list, t_list_pair *newNode) {
  if (!(*list)) {
    *list = newNode;
    return;
  }
  t_list_pair *iter = *list;
  while (iter->next) {
    iter = iter->next;
  }
  iter->next = newNode;
}

static t_list_pair *new_node_pair(int prev, int aft) {
  t_list_pair *node = (t_list_pair *)calloc(1, sizeof(t_list_pair));
  if (!node) {
    return (NULL);
  }
  node->prev = prev;
  node->aft = aft;
  node->next = NULL;
  return (node);
}

void free_list_pair(t_list_pair **list) {
  if (!(*list))
    return;
  t_list_pair *iter = *list;
  t_list_pair *toFree;
  while (iter) {
    toFree = iter;
    iter = iter->next;
    free(toFree);
  }
  *list = NULL;
}

void gen_list_pair(t_list_pair **list, char *argv) {
  if (!list) {
    return;
  }
  int len1, len2, cont = 0, lenS = strlen(argv);
  while (argv[cont] && cont < lenS) {
    len1 = digit_len(&argv[cont]);
    len2 = digit_len(&argv[cont + len1 + 1]);
    add_node_pair(
        list, new_node_pair(atoi(&argv[cont]), atoi(&argv[cont + len1 + 1])));
    //+2 because of '|' and ' '
    cont += (len1 + len2 + 2);
  }
}

void print_list_pair(t_list_pair *list) {
  while (list) {
    printf("Prev: %d| Aft: %d\n", list->prev, list->aft);
    list = list->next;
  }
}
