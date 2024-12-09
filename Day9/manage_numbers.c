#include "day9.h"

static t_nums *new_node(long long iden, int len) {
  t_nums *node = (t_nums *)calloc(1, sizeof(t_nums));
  if (!node) {
    printf("ERROR AL RESEVAR MEMORIA\n");
    return (NULL);
  }
  node->back_passed = 0;
  node->iden = iden;
  node->len = len;
  node->next = NULL;
  return (node);
}

static void add_back(t_nums **list, t_nums *node) {
  if (!(*list)) {
    *list = node;
    return;
  }
  t_nums *iter = *list;
  while (iter->next)
    iter = iter->next;
  iter->next = node;
}

void gen_list(t_nums **list, long long *full_arr, long long full_size) {
  t_nums *ret;
  ret = NULL;
  int cont = full_size - 1;
  long long act_num, num_len;
  while (cont >= 0) {
    if (full_arr[cont] != -1) {
      act_num = full_arr[cont];
      num_len = 0;
      while (((cont - num_len) >= 0) && full_arr[cont - num_len] == act_num)
        num_len++;
      add_back(&ret, new_node(act_num, num_len));
      cont -= num_len;
    } else {
      cont--;
    }
  }
  *list = ret;
}

void print_list(t_nums *list) {
  while (list) {
    printf("Iden: %lld, len: %d, status: %d\n", list->iden, list->len,
           list->back_passed);
    list = list->next;
  }
}

void free_list(t_nums **list) {
  t_nums *iter = *list;
  t_nums *toFree;
  while (iter) {
    toFree = iter;
    iter = iter->next;
    free(toFree);
  }
  *list = NULL;
}
