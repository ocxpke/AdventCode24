#include <stdio.h>
#include <string.h>

int isXmas(char m, char a, char s) {
  return (m == 'M' && a == 'A' && s == 'S');
}

int isXXmas(char s, char a, char m, char s1) {
  return (s == 'S' && a == 'A' && m == 'M' && s1 == 'S');
}

int main(int argc, char **argv) {
  int ret = 0;
  int mas = 0;
  int vert = 0, hor = 0;
  int len = strlen(argv[1]);
  for (int i = 1; i < argc; i++) {
    for (int j = 0; j < len; j++) {
      if (argv[i][j] == 'X') {
        //
        if ((j + 3) < len) {
          hor += isXmas(argv[i][j + 1], argv[i][j + 2], argv[i][j + 3]);
        }
        //
        if ((j - 3) >= 0) {
          hor += isXmas(argv[i][j - 1], argv[i][j - 2], argv[i][j - 3]);
        }
        //
        if ((i + 3) < argc) {
          vert += isXmas(argv[i + 1][j], argv[i + 2][j], argv[i + 3][j]);
        }
        //
        if ((i - 3) >= 1) {
          vert += isXmas(argv[i - 1][j], argv[i - 2][j], argv[i - 3][j]);
        }
        //
        if (((i + 3) < argc) && ((j + 3) < len)) {
          ret += isXmas(argv[i + 1][j + 1], argv[i + 2][j + 2],
                        argv[i + 3][j + 3]);
        }
        //
        if (((i - 3) >= 1) && ((j - 3) >= 0)) {
          ret += isXmas(argv[i - 1][j - 1], argv[i - 2][j - 2],
                        argv[i - 3][j - 3]);
        }
        //
        if (((i + 3) < argc) && ((j - 3) >= 0)) {
          ret += isXmas(argv[i + 1][j - 1], argv[i + 2][j - 2],
                        argv[i + 3][j - 3]);
        }
        //
        if (((i - 3) >= 1) && ((j + 3) < len)) {
          ret += isXmas(argv[i - 1][j + 1], argv[i - 2][j + 2],
                        argv[i - 3][j + 3]);
        }
      }

      if (argv[i][j] == 'M') {
        // Normal
        if (((i + 2) < argc) && ((j + 2) < len)) {
          mas += isXXmas(argv[i][j + 2], argv[i + 1][j + 1], argv[i + 2][j],
                         argv[i + 2][j + 2]);
          mas += isXXmas(argv[i + 2][j], argv[i + 1][j + 1], argv[i][j + 2],
                         argv[i + 2][j + 2]);
        }
        // Espejo
        /*
        if (((i - 2) >= 1) && ((j - 2) >= 0)) {
          mas += isXXmas(argv[i][j - 2], argv[i - 1][j - 1], argv[i - 2][j],
                         argv[i - 2][j - 2]);
        }
        */
        //
        if (((i + 2) < argc) && ((j - 2) >= 0)) {
          mas += isXXmas(argv[i][j - 2], argv[i + 1][j - 1], argv[i + 2][j],
                         argv[i + 2][j - 2]);
        }
        //
        if (((i - 2) >= 1) && ((j + 2) < len)) {
          mas += isXXmas(argv[i - 2][j], argv[i - 1][j + 1], argv[i][j + 2],
                         argv[i - 2][j + 2]);
        }
      }
    }
  }
  printf("%d\n", ret + vert + hor);
  printf("%d\n", mas);
}
