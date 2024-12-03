#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *ft_substr(const char *s, unsigned int start, size_t len) {
  size_t cont;
  size_t len_s;
  char *substr;

  cont = 0;
  len_s = strlen(s);
  if (len > len_s)
    len = len_s;
  if (start > len_s)
    len = 0;
  if (len > (len_s - start))
    len = len_s - start;
  substr = (char *)calloc(1, len + 1);
  if (!substr)
    return (NULL);
  if (!(*s) || start > len_s)
    return (substr);
  while (cont < len && s[start + cont]) {
    substr[cont] = s[start + cont];
    cont++;
  }
  substr[cont] = 0;
  return (substr);
}

int isMul(char *str) {
  int ret = 0, x, y;
  int cont = 0, sum;
  while (str[cont]) {
    sum = 0;
    if (!strncmp(&str[cont + sum], "mul(", 4)) {
      sum += 4;
      x = atoi(&str[cont + sum]);
      printf("hola %d\n", x);
      while (isdigit(str[cont + sum]) && str[cont + sum])
        sum++;
      if (str[cont + sum] == ',') {
        sum++;
        y = atoi(&str[cont + sum]);
        printf("hola %d\n", y);
        while (isdigit(str[cont + sum]) && str[cont + sum])
          sum++;
        if (str[cont + sum] == ')') {
          ret += (x * y);
        }
      }
    }
    cont++;
  }
  return (ret);
}

int main(int argc, char **argv) {
  printf("El resultado de la multiplicacion es: %d\n", isMul(argv[1]));
  return (0);
}
