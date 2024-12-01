/**
 * Done by @ocxpke
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int *paramToStack(char *arg) {
  char **splitted = ft_split(arg, ' ');
  int *ret = (int *)calloc(1, count_words(arg, ' ') * sizeof(int));
  if (!ret || !splitted) {
    free(splitted);
    free(ret);
    return (NULL);
  }
  int contw = 0;
  while (splitted[contw]) {
    ret[contw] = atoi(splitted[contw]);
    contw++;
  }
  free_back(splitted);
  return (ret);
}

void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

void quickSort(int *stack, int ini, int end) {
  if (ini >= end)
    return;
  int i = ini - 1;
  int j = ini;
  int pivot = stack[end];

  while (j <= end) {
    if (stack[j] <= pivot) {
      i++;
      swap(&stack[i], &stack[j]);
    }
    j++;
  }

  quickSort(stack, ini, i - 1);
  quickSort(stack, i + 1, end);
}

int repeated(int *stack, int len, int x) {
  int ret = 0;
  for (int i = 0; i < len; i++) {
    if (x == stack[i]) {
      ret++;
    }
  }
  return (ret);
}

int main(int argc, char **argv) {
  int *stack1 = paramToStack(argv[1]);
  int *stack2 = paramToStack(argv[2]);

  int len1 = count_words(argv[1], ' ');
  int len2 = count_words(argv[2], ' ');

  quickSort(stack1, 0, len1 - 1);
  quickSort(stack2, 0, len2 - 1);

  for (int i = 0; i < len1; i++) {
    printf("%d ", stack1[i]);
  }
  printf("\n");

  for (int i = 0; i < len2; i++) {
    printf("%d ", stack2[i]);
  }
  printf("\n");

  int minus;
  long long int totDiff = 0;
  for (int i = 0; i < len1; i++) {
    minus = (stack1[i] - stack2[i]);
    printf("%d ", minus);
    if (minus < 0) {
      minus *= -1;
    }
    totDiff += minus;
  }
  printf("\n");

  printf("The total diff is: %d \n", totDiff);

  // Part 2
  int act;
  long long int totRep = 0;

  for (int i = 0; i < len1; i++) {
    act = stack1[i];
    totRep += (act * repeated(stack2, len2, act));
  }

  printf("The total repeated is: %d \n", totRep);

  free(stack1);
  free(stack2);
}
