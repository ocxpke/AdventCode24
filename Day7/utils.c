#include "day7.h"

long long int concat_numbers(long long int num1, long long int num2) {
  long long int copy = num2;
  int len = 0;
  while (copy) {
    copy /= 10;
    len++;
  }
  for (int i = 0; i < len; i++)
    num1 *= 10;
  return (num1 + num2);
}

int digit_len(char *str) {
  int ret = 0;
  while (str[ret] && isdigit(str[ret]))
    ret++;
  return (ret);
}

int sum_one_binary(int *arr, int len) {
  int ok = 1;
  for (int i = 0; i <= len && ok; i++) {
    if (!arr[i])
      ok = 0;
  }
  if (ok)
    return (1);
  int cont = len;
  while (cont >= 0 && arr[cont])
    cont--;
  arr[cont] = 1;
  cont++;
  while (cont <= len) {
    arr[cont] = 0;
    cont++;
  }
  return (0);
}

int sum_one_base3(int *arr, int len) {
  int ok = 1;
  for (int i = 0; i <= len && ok; i++) {
    if (arr[i] != 2)
      ok = 0;
  }
  if (ok)
    return (1);
  int cont = len;
  while (cont >= 0 && arr[cont] == 2)
    cont--;
  arr[cont]++;
  cont++;
  while (cont <= len) {
    arr[cont] = 0;
    cont++;
  }
  return (0);
}

void analyze_list_binary(t_oper *list) {
  int arr[list->len - 1];
  fill_arr_zero(arr, list->len - 1);
  int bin = 0;
  long long int operRes;
  while (!(list->correct) && !bin) {
    operRes = list->elems[0];
    for (int i = 0; i < list->len - 1; i++) {
      if (!arr[i]) {
        operRes += list->elems[i + 1];
      } else {
        operRes *= list->elems[i + 1];
      }
    }
    list->correct = (operRes == list->resul);
    bin = sum_one_binary(arr, list->len - 2);
  }
}

void analyze_list_base3(t_oper *list) {
  int arr[list->len - 1];
  fill_arr_zero(arr, list->len - 1);
  int bin = 0;
  long long int operRes;
  while (!(list->correct) && !bin) {
    operRes = list->elems[0];
    for (int i = 0; i < list->len - 1; i++) {
      if (!arr[i]) {
        operRes += list->elems[i + 1];
      } else if (arr[i] == 1) {
        operRes *= list->elems[i + 1];
      } else {
        operRes = concat_numbers(operRes, list->elems[i + 1]);
      }
    }
    list->correct = (operRes == list->resul);
    bin = sum_one_base3(arr, list->len - 2);
  }
}

void fill_arr_zero(int *arr, int len) {
  for (int i = 0; i < len; i++) {
    arr[i] = 0;
  }
}

void print_binary_arr(int *arr, int len) {
  for (int i = 0; i <= len; i++) {
    printf("%d", arr[i]);
    if (i != len)
      printf(", ");
    else
      printf("\n");
  }
}
