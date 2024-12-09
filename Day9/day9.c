#include "day9.h"

void first_fill_arr(long long *arr, char *str) {
  int pos_arr = 0;
  int pos_str = 0;
  int write = 1;
  int cont = 0;
  while (str[pos_str]) {
    if (write) {
      for (int i = 0; i < (str[pos_str] - '0'); i++) {
        arr[pos_arr] = cont;
        pos_arr++;
      }
      cont++;
      write = 0;
    } else {
      for (int i = 0; i < (str[pos_str] - '0'); i++) {
        arr[pos_arr] = -1;
        pos_arr++;
      }
      write = 1;
    }
    pos_str++;
  }
}

long long *new_arr(char *str, long long *full_len) {
  while (*str) {
    (*full_len) += (*str) - '0';
    str++;
  }
  long long *ret = (long long *)calloc(1, (*full_len) * sizeof(long long));
  if (!ret) {
    printf("ERROR AL RESEVAR MEMORIA\n");
    return (NULL);
  }
  return (ret);
}

void print_arr(long long *full_arr, long long full_len) {
  for (long long i = 0; i < full_len; i++) {
    printf("%d ", full_arr[i]);
  }
  printf("\n");
}

void find_empty(long long *full_arr, long long int *iter, long long full_len) {
  while (((*iter) < full_len) && full_arr[(*iter)] != -1)
    (*iter)++;
}

void next_num(long long *full_arr, long long int *iter) {
  while ((*iter) >= 0 && full_arr[(*iter)] == -1)
    (*iter)--;
}

void reorder(long long *full_arr, long long full_len) {
  long long int back = full_len - 1;
  long long int front = 0;
  while (front < full_len && back >= 0 && back >= front) {
    find_empty(full_arr, &front, full_len);
    next_num(full_arr, &back);
    if (back >= front) {
      full_arr[front] = full_arr[back];
      full_arr[back] = -1;
    }
    back--;
  }
}

void reorderV2(long long *cpy_arr, long long full_len, t_nums *list) {
  long long int back = full_len - 1;
  long long int front = 0;
  int len_space;
  int cpy_back;
  t_nums *iter;
  int found;
  while (front < full_len) {
    found = 0;
    iter = list;
    len_space = 0;
    find_empty(cpy_arr, &front, full_len);
    while ((front + len_space < full_len) && cpy_arr[front + len_space] == -1) {
      len_space++;
    }
    while (iter && !found) {
      if (!iter->back_passed && (iter->len <= len_space))
        found = 1;
      else
        iter = iter->next;
    }
    if (iter) {
      while (back >= 0 && cpy_arr[back] != iter->iden) {
        back--;
      }
      for (int i = 0; i < iter->len; i++) {
        cpy_arr[front + i] = iter->iden;
      }
      front += iter->len;
      iter->back_passed = 1;
    } else {
      front++;
    }
  }
}

long long int fin_sum(long long *full_arr, long long full_len) {
  long long int ret = 0;
  int cont = 0;
  for (long long i = 0; i < full_len; i++) {
    // printf("%d * %d\n", cont, full_arr[i] - '0');
    if (full_arr[i] != -1)
      ret += (cont * (full_arr[i]));
    cont++;
  }
  return (ret);
}

/**
 * Limpiar array + ver bien funcion reorderV2
 */
void clean_arr(long long *cpy_arr, long long full_len, t_nums *list) {
  int back;
  while (list) {
    back = full_len - 1;
    if (list->back_passed) {
      while (back >= 0 && cpy_arr[back] != list->iden) {
        back--;
      }
      for (int i = 0; i < list->len; i++) {
        cpy_arr[back] = -1;
        back--;
      }
    }
    list = list->next;
  }
}

int main(int argc, char **argv) {
  t_nums *list = NULL;
  long long full_len = 0;
  long long *full_arr = new_arr(argv[1], &full_len);
  long long *cpy_arr = (long long *)calloc(1, full_len * sizeof(long long));
  if (!cpy_arr) {
    printf("ERROR AL RESEVAR MEMORIA\n");
    exit(EXIT_FAILURE);
  }

  first_fill_arr(full_arr, argv[1]);
  first_fill_arr(cpy_arr, argv[1]);

  gen_list(&list, full_arr, full_len);
  // print_list(list);

  // print_arr(full_arr, full_len);
  // print_arr(cpy_arr, full_len);

  reorder(full_arr, full_len);
  // print_arr(full_arr, full_len);
  printf("The final checksum is: %lld\n", fin_sum(full_arr, full_len));

  reorderV2(cpy_arr, full_len, list);
  clean_arr(cpy_arr, full_len, list);
  // print_arr(cpy_arr, full_len);
  // print_list(list);
  printf("The final checksum is: %lld\n", fin_sum(cpy_arr, full_len));

  free(full_arr);
  free(cpy_arr);
  free_list(&list);
}
