#include "day7.h"

long long int check_all_list(t_oper *list, int mode) {
  long long int ret = 0;
  while (list) {
    if (!mode)
      analyze_list_binary(list);
    else
      analyze_list_base3(list);
    if (list->correct) {
      ret += list->resul;
    }
    list = list->next;
  }
  return (ret);
}

int main(int argc, char **argv) {
  t_oper *list = NULL;
  gen_list_oper(&list, argc, argv);
  // print_list(list);

  // printf("%d\n", concat_numbers(0, 1));

  printf("Calibration result: %ld\n", check_all_list(list, 0));
  reset_correct(list);
  printf("Calibration V2 result: %ld\n", check_all_list(list, 1));

  /*
    int arr[4];
    fill_arr_zero(arr, 4);
    while (!sum_one_base3(arr, 3))
      print_binary_arr(arr, 3);
    */

  free_list(&list);
}
