#include "day5.h"

int digit_len(char *str) {
  int ret = 0;
  while (*str && isdigit(*str)) {
    ret++;
    str++;
  }
  return (ret);
}
