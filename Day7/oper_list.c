#include "day7.h"

void free_list(t_oper **list) {
  t_oper *iter = *list;
  t_oper *toFree;
  while (iter) {
    toFree = iter;
    iter = iter->next;
    free(toFree->elems);
    free(toFree);
  }
  *list = NULL;
}

void reset_correct(t_oper *list) {
  while (list) {
    list->correct = 0;
    list = list->next;
  }
}
t_oper *new_node(long long int res, int *arr, int len) {
  t_oper *newNode = (t_oper *)calloc(1, sizeof(t_oper));
  if (!newNode)
    return (NULL);
  newNode->resul = res;
  newNode->elems = arr;
  newNode->len = len;
  newNode->correct = 0;
  newNode->next = NULL;
  return (newNode);
}

void add_back(t_oper **list, t_oper *new_node) {
  if (!(*list)) {
    *list = new_node;
    return;
  }
  t_oper *iter = *list;
  while (iter->next)
    iter = iter->next;
  iter->next = new_node;
}

void get_arr_n_len(char *argv, int **arr, int *len) {
  int cont = 0;
  int pos = 0;
  int lenArr = 0;
  int lenS = strlen(argv);
  while (cont < lenS) {
    cont += (digit_len(&argv[cont]) + 1);

    lenArr++;
  }
  int *newArr = (int *)calloc(1, sizeof(int) * lenArr);
  if (!newArr)
    return;
  cont = 0;
  while (cont < lenS) {
    newArr[pos] = atoi(&argv[cont]);
    cont += (digit_len(&argv[cont]) + 1);
    pos++;
  }
  *arr = newArr;
  *len = lenArr;
}

void gen_list_oper(t_oper **list, int argc, char **argv) {
  int *arr = NULL;
  long long int res;
  int len;
  int cont;
  for (int i = 1; i < argc; i++) {
    cont = 0;
    res = strtoll(argv[i], NULL, 10);
    cont += (digit_len(argv[i]) + 2);
    get_arr_n_len(&argv[i][cont], &arr, &len);
    add_back(list, new_node(res, arr, len));
  }
}

void print_list(t_oper *list) {
  while (list) {
    printf("%d: [", list->resul);
    for (int i = 0; i < list->len; i++) {
      printf("%d", list->elems[i]);
      if (i != list->len - 1)
        printf(", ");
    }
    printf("] len is: %d\n", list->len);
    list = list->next;
  }
}
