#include "day5.h"

static t_list_elem *create_node_elem(int *arr, int len) {
  t_list_elem *node = (t_list_elem *)calloc(1, sizeof(t_list_elem));
  int *array = (int *)calloc(1, sizeof(int) * len);
  if (!node || !array) {
    free(array);
    free(node);
    return (NULL);
  }
  for (int i = 0; i < len; i++) {
    array[i] = arr[i];
  }
  node->list = array;
  node->len = len;
  node->ok = 0;
  node->next = NULL;
  return (node);
}

static void add_list_elem_back(t_list_elem **list, t_list_elem *newNode) {
  if (!(*list)) {
    *list = newNode;
    return;
  }
  t_list_elem *iter = *list;
  while (iter->next) {
    iter = iter->next;
  }
  iter->next = newNode;
}

void free_list_elem(t_list_elem **list) {
  if (!(*list))
    return;
  t_list_elem *iter = *list;
  t_list_elem *toFree;
  while (iter) {
    toFree = iter;
    iter = iter->next;
    free(toFree->list);
    free(toFree);
  }
  *list = NULL;
}

void gen_list_elem(t_list_elem **list, int argc, char **argv) {
  if (!list)
    return;
  int pos, numCont, jump, totLen;
  int arr[1024];
  for (int i = 2; i < argc; i++) {
    pos = 0;
    numCont = 0;
    totLen = strlen(argv[i]);
    while (pos < totLen && argv[i][pos]) {
      jump = digit_len(&argv[i][pos]);
      arr[numCont] = atoi(&argv[i][pos]);
      numCont++;
      pos += (jump + 1);
    }
    add_list_elem_back(list, create_node_elem(arr, numCont));
  }
}

void print_list_elem(t_list_elem *list) {
  int len;
  while (list) {
    len = 0;
    printf("[");
    for (int i = 0; i < list->len; i++) {
      printf("%d", list->list[i]);
      if (i != (list->len - 1)) {
        printf(", ");
      }
    }
    printf("] + len: %d + ok: %d\n", list->len, list->ok);
    list = list->next;
  }
}
