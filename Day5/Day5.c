#include "day5.h"

/**
 * Here we check for every list if any pair is in an incorrect way,
 * if that's the case we dont set the flag as 1
 */
void list_ok(t_list_elem *list_elem, t_list_pair *list_pair) {
  int a, b;
  int ok;
  t_list_pair *iter;
  while (list_elem) {
    ok = 1;
    for (int i = 0; (i < list_elem->len) && ok; i++) {
      iter = list_pair;
      a = list_elem->list[i];
      for (int j = i + 1; (j < list_elem->len) && ok; j++) {
        b = list_elem->list[j];
        while (iter && ok) {
          if (iter->prev == b && iter->aft == a) {
            ok = 0;
          }
          iter = iter->next;
        }
      }
    }
    if (ok == 1) {
      list_elem->ok = 1;
    }
    list_elem = list_elem->next;
  }
}

/**
 * We use here Bubble sort, I know that it is inefficent but has an easier
 * implementation
 */
void order_list(t_list_elem *list_e, t_list_pair *list_p) {
  int a, b, tmp, rule, rep;
  t_list_pair *iter;
  while (list_e) {
    rep = 0;
    while (rep < list_e->len) {
      for (int i = 0; i < list_e->len && !list_e->ok; i++) {
        a = list_e->list[i];
        for (int j = i + 1; j < list_e->len; j++) {
          b = list_e->list[j];
          iter = list_p;
          rule = 0;
          while (iter && !rule) {
            if (iter->prev == b && iter->aft == a) {
              printf("SWAP %d %d i:%d\n", a, b, i);
              tmp = list_e->list[i];
              list_e->list[i] = list_e->list[j];
              list_e->list[j] = tmp;
              rule = 1;
            }
            iter = iter->next;
          }
        }
      }
      rep++;
    }
    list_e = list_e->next;
  }
}

int final_ret(t_list_elem *list, int mode) {
  int ret = 0;
  int mid;
  while (list) {
    if (list->ok == mode) {
      mid = (list->len / 2);
      ret += list->list[mid];
    }
    list = list->next;
  }
  return (ret);
}

int main(int argc, char **argv) {
  t_list_pair *list_p = NULL;
  t_list_elem *list_e = NULL;
  gen_list_pair(&list_p, argv[1]);
  // print_list_pair(list_p);
  gen_list_elem(&list_e, argc, argv);
  // print_list_elem(list_e);

  list_ok(list_e, list_p);
  // printf("Post mod\n");
  // print_list_elem(list_e);

  printf("And the final sum is: %d\n", final_ret(list_e, 1));
  order_list(list_e, list_p);
  // print_list_elem(list_e);
  printf("And the final sum for part 2 is: %d\n", final_ret(list_e, 0));

  free_list_pair(&list_p);
  free_list_elem(&list_e);
}
