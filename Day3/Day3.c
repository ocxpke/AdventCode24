#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isMul(char *str) {
  int ret = 0, x, y;
  int cont = 0, sum;
  int multi = 1;
  while (str[cont]) {
    sum = 0;
    if (!strncmp(&str[cont], "don't()", 7)) {
      multi = 0;
      cont += 7;
    } else if (!strncmp(&str[cont], "do()", 4)) {
      multi = 1;
      cont += 4;
    }
    if (!strncmp(&str[cont + sum], "mul(", 4)) {
      /**
       * All the content of this if could be replaced with the use of
       * the function sscanf.
       */
      sum += 4;
      x = atoi(&str[cont + sum]);
      while (isdigit(str[cont + sum]) && str[cont + sum])
        sum++;
      if (str[cont + sum] == ',') {
        sum++;
        y = atoi(&str[cont + sum]);
        while (isdigit(str[cont + sum]) && str[cont + sum])
          sum++;
        if ((str[cont + sum] == ')') && multi) {
          ret += (x * y);
          cont += sum;
        }
      }
    }
    cont++;
  }
  return (ret);
}

int main(int argc, char **argv) {
  if (argc < 2)
    return (1);
  printf("El resultado de la multiplicacion es: %d\n", isMul(argv[1]));
  return (0);
}
