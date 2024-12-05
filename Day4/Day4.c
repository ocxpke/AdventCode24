#include <stdio.h>
#include <string.h>

int readDiagonal(int argc, char **argv) {
  int ret = 0;
  int line = 1;
  int len;
  len = strlen(argv[line]);
  while (line < argc) {
    for (int i = 0; i < len; i++) {
      if (((line + 3) < argc) && ((i + 3) < len) && (argv[line][i] == 'X') &&
          (argv[line + 1][i + 1] == 'M') && (argv[line + 2][i + 2] == 'A') &&
          (argv[line + 3][i + 3] == 'S')) {
        ret++;
      }
      if ((line + 3) < argc && ((i + 3) < len) && (argv[line][i] == 'S') &&
          (argv[line + 1][i + 1] == 'A') && (argv[line + 2][i + 2] == 'M') &&
          (argv[line + 3][i + 3] == 'X')) {
        ret++;
      }
      if (((line - 3) > 0) && ((i - 3) >= 0) && (argv[line][i] == 'X') &&
          (argv[line - 1][i - 1] == 'M') && (argv[line - 2][i - 2] == 'A') &&
          (argv[line - 3][i - 3] == 'S')) {
        ret++;
      }
      if (((line - 3) > 0) && ((i - 3) >= 0) && (argv[line][i] == 'S') &&
          (argv[line - 1][i - 1] == 'A') && (argv[line - 2][i - 2] == 'M') &&
          (argv[line - 3][i - 3] == 'X')) {
        ret++;
      }
    }
    line++;
  }
  return (ret);
}

int readVertical(int argc, char **argv) {
  int ret = 0;
  int line = 1;
  int len;
  len = strlen(argv[line]);
  for (int i = 0; i < len; i++) {
    line = 1;
    while (line < argc) {
      if ((line + 3 < argc) && (argv[line][i] == 'X') &&
          (argv[line + 1][i] == 'M') && (argv[line + 2][i] == 'A') &&
          (argv[line + 3][i] == 'S')) {
        ret++;
      }
      if ((line + 3 < argc) && (argv[line][i] == 'S') &&
          (argv[line + 1][i] == 'A') && (argv[line + 2][i] == 'M') &&
          (argv[line + 3][i] == 'X')) {
        ret++;
      }
      line++;
    }
  }
  return (ret);
}

int readHorizontal(char *str) {
  int ret = 0;

  while (*str) {
    if (!strncmp(str, "XMAS", 4) || !strncmp(str, "SAMX", 4)) {
      ret++;
    }
    str++;
  }
  return (ret);
}

int main(int argc, char **argv) {
  long long int total = 0;
  int contLines = 1;
  while (contLines < argc) {
    total += readHorizontal(argv[contLines]);
    contLines++;
  }
  printf("Horizontal = %d\n", total);
  total += readVertical(argc, argv);
  printf("Horizontal + vertical = %d\n", total);
  total += readDiagonal(argc, argv);
  printf("Horizontal + vertical + diagonal = %d\n", total);
}
