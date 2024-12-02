#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int safeOrUnsafe(int *list, int length, int lifes);

static size_t count_words(char const *s, char c) {
  size_t cont;

  if (!*s)
    return (0);
  cont = 1;
  if (*s == c)
    cont = 0;
  while (*s) {
    if (*s == c && s[1] != c && s[1])
      cont++;
    s++;
  }
  return (cont);
}

static size_t take_len(char const *s, char c) {
  size_t cont;

  cont = 0;
  while (s[cont] && s[cont] != c)
    cont++;
  return (cont);
}

static char **free_back(char **words) {
  size_t i;

  i = 0;
  while (words[i]) {
    free(words[i]);
    i++;
  }
  free(words);
  return (NULL);
}

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

char **ft_split(char const *s, char c) {
  char **ret;
  size_t i;
  size_t len_word;

  i = 0;
  ret = (char **)calloc(count_words(s, c) + 1, sizeof(char *));
  if (!ret)
    return (NULL);
  while (*s) {
    while (*s == c && *s != 0)
      s++;
    if (*s) {
      len_word = take_len(s, c);
      ret[i] = ft_substr(s, 0, len_word);
      if (!ret[i])
        return (free_back(ret));
      i++;
      s += len_word;
    }
  }
  ret[i] = 0;
  return (ret);
}

int ft_atoi(const char *nptr) {
  int minus;
  int number;

  number = 0;
  minus = 1;
  while (*nptr == ' ' || *nptr == '\n' || *nptr == '\t' || *nptr == '\r' ||
         *nptr == '\v' || *nptr == '\f')
    nptr++;
  if (*nptr == '+' || *nptr == '-') {
    if (*nptr == '-')
      minus = -1;
    nptr++;
  }
  while (isdigit(*nptr) && *nptr) {
    number = (number * 10 + ((*nptr) - '0'));
    nptr++;
  }
  return (number * minus);
}

int diffOk(int a, int b, int mode) {
  int minus = a - b;
  if ((mode == 1 && a > b) || (mode == 0 && a < b)) {
    return (0);
  }
  if (minus < 0) {
    minus *= -1;
  }
  if (minus >= 1 && minus <= 3) {
    return (1);
  }
  return (0);
}

int remake(int *list, int length) {
  int pos = 0;
  int sOu = 0;
  int sum;
  while (pos < length && !sOu) {
    int *ret = (int *)calloc(1, (length - 1) * sizeof(int));
    if (!ret) {
      return 0;
    }
    sum = 0;

    for (int i = 0; i < length; i++) {
      if (i != pos) {
        ret[i - sum] = list[i];
      } else {
        sum = 1;
      }
    }

    if (safeOrUnsafe(ret, length - 1, 1)) {
      sOu = 1;
    }
    free(ret);

    pos++;
  }
  return (sOu);
}

int safeOrUnsafe(int *list, int length, int lifes) {
  int ret = lifes;
  int mode;
  /**
   * Mode = 1 --> Increase
   * Mode = 0 --> Decrease
   */
  if (list[0] < list[1]) {
    mode = 1;
  } else {
    mode = 0;
  }
  for (int i = 0; (i < (length - 1)) && ret; i++) {
    if (!diffOk(list[i], list[i + 1], mode)) {
      ret--;
      if (ret) {
        return (remake(list, length));
      }
    }
  }
  return (ret);
}

int *splitted(char *argv) {
  char **splitted = ft_split(argv, ' ');
  int *ret = (int *)calloc(1, count_words(argv, ' ') * sizeof(int));
  if (!splitted) {
    free(splitted);
    free(ret);
    return (NULL);
  }
  for (int i = 0; splitted[i]; i++) {
    ret[i] = ft_atoi(splitted[i]);
  }
  free_back(splitted);
  return (ret);
}

int main(int argc, char **argv) {
  int len;
  int *list;
  int contSafe = 0;
  int contSafeDampener = 0;
  for (int i = 1; i < argc; i++) {
    list = splitted(argv[i]);
    if (!list) {
      exit(EXIT_FAILURE);
    }
    len = count_words(argv[i], ' ');
    if (safeOrUnsafe(list, len, 1)) {
      contSafe++;
    }
    if (safeOrUnsafe(list, len, 2)) {
      contSafeDampener++;
    }
    free(list);
    list = NULL;
  }

  printf("%d are safe. And with the Dampener %d are safe\n ", contSafe,
         contSafeDampener);
}
