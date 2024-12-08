#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_oper {
  long long int resul;
  int *elems;
  int len;
  int correct;
  struct s_oper *next;
} t_oper;

/**
 * OPER_LIST.C
*/
void print_list(t_oper *list);
void gen_list_oper(t_oper **list, int argc, char **argv);
void get_arr_n_len(char *argv, int **arr, int *len);
void add_back(t_oper **list, t_oper *new_node);
t_oper *new_node(long long int res, int *arr, int len);
void reset_correct(t_oper *list);
void free_list(t_oper **list);

/**
 * UTILS.C
*/
long long int concat_numbers(long long int num1, long long int num2);
void print_binary_arr(int *arr, int len);
void fill_arr_zero(int *arr, int len);
void analyze_list_base3(t_oper *list);
void analyze_list_binary(t_oper *list);
int sum_one_base3(int *arr, int len);
int sum_one_binary(int *arr, int len);
int digit_len(char *str);
