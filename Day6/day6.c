#include "day6.h"

void init_pos(t_point *start, int argc, char **argv, int len) {
  int found = 0;
  for (int i = 1; i < argc && !found; i++) {
    for (int j = 0; j < len && !found; j++) {
      if (argv[i][j] == '^') {
        start->x = i;
        start->y = j;
        start->dir = 0;
        found = 1;
      }
    }
  }
}

void print_map(int argc, char **argv, int len) {
  for (int i = 1; i < argc; i++) {
    for (int j = 0; j < len; j++) {
      printf("%c ", argv[i][j]);
    }
    printf("\n");
  }
}

void move_vertical(t_point *pos, char **argv, int max, int *ret, int mode,
                   t_path **listP) {
  if ((((pos->x - 1) > 1 && !mode) || ((pos->x + 1) < max && mode)) &&
      ((argv[pos->x - 1][pos->y] != '#' && !mode) ||
       (argv[pos->x + 1][pos->y] != '#' && mode))) {
    if (mode)
      pos->x++;
    else
      pos->x--;
    if (argv[pos->x][pos->y] != 'x') {
      argv[pos->x][pos->y] = 'x';
      (*ret)++;
    }
    add_node(listP, pos->x, pos->y);
  } else if ((((pos->x - 1) >= 1 && !mode) || ((pos->x + 1) < max && mode)) &&
             ((argv[pos->x - 1][pos->y] == '#' && !mode) ||
              (argv[pos->x + 1][pos->y] == '#' && mode))) {
    if (mode)
      pos->dir = 3;
    else
      pos->dir = 1;
  } else {
    if (mode)
      pos->x++;
    else
      pos->x--;
  }
}

void reset_map(int argc, char **argv, int len) {
  for (int i = 1; i < argc; i++) {
    for (int j = 0; j < len; j++) {
      if (argv[i][j] == 'x') {
        argv[i][j] = '.';
      }
    }
  }
}

void move_horizontal(t_point *pos, char **argv, int max, int *ret, int mode,
                     t_path **listP) {
  if ((((pos->y + 1) < max && !mode) || ((pos->y - 1) >= 0 && mode)) &&
      ((argv[pos->x][pos->y + 1] != '#' && !mode) ||
       (argv[pos->x][pos->y - 1] != '#' && mode))) {
    if (!mode)
      pos->y++;
    else
      pos->y--;
    if (argv[pos->x][pos->y] != 'x') {
      argv[pos->x][pos->y] = 'x';
      (*ret)++;
    }
    add_node(listP, pos->x, pos->y);
  } else if ((((pos->y + 1) < max && !mode) || ((pos->y - 1) >= 0 && mode)) &&
             ((argv[pos->x][pos->y + 1] == '#' && !mode) ||
              (argv[pos->x][pos->y - 1] == '#' && mode))) {
    if (!mode)
      pos->dir = 2;
    else
      pos->dir = 0;
  } else {
    if (!mode)
      pos->y++;
    else
      pos->y--;
  }
}

int rush_map(int argc, char **argv, int len, t_point *pos, t_path **listP) {
  int ret = 0;
  while ((pos->x >= 1 && pos->x < argc) && (pos->y >= 0 && pos->y < len)) {
    if (pos->dir == 0)
      move_vertical(pos, argv, argc, &ret, 0, listP);
    else if (pos->dir == 1)
      move_horizontal(pos, argv, len, &ret, 0, listP);
    else if (pos->dir == 2)
      move_vertical(pos, argv, argc, &ret, 1, listP);
    else
      move_horizontal(pos, argv, len, &ret, 1, listP);
    if (!check_five(*listP)) {
      return (-1);
    }
    // print_map(argc, argv, len);
    // printf("--\n");
  }

  return (ret);
}

int check_obs(int argc, char **argv, t_path *list, int xS, int yS) {
  int len = strlen(argv[1]);
  int ret = 0, cont = 0;
  int res;
  t_path *nL = NULL;
  t_point pos;

  while (list) {
    nL = NULL;
    reset_map(argc, argv, len);
    if (!(list->x == xS && list->y == yS)) {
      argv[list->x][list->y] = '#';
      // print_map(argc, argv, len);

      pos.x = xS;
      pos.y = yS;
      pos.dir = 0;
      res = rush_map(argc, argv, len, &pos, &nL);
      printf("%d\n", res);
      if (res == -1) {
        ret++;
      }
      printf("<------------------------------------------>\n");
      argv[list->x][list->y] = '.';
      free_list(&nL);
    }
    cont++;
    printf("%d\n", cont);
    list = list->next;
  }
  return (ret);
}

int main(int argc, char **argv) {
  t_point pos;
  t_path *points = NULL;
  int len, x, y, pathLen;
  len = strlen(argv[1]);

  init_pos(&pos, argc, argv, len);

  printf("Init pos is --> x:%d | y:%d\n", pos.x, pos.y);

  x = pos.x;
  y = pos.y;

  pathLen = rush_map(argc, argv, len, &pos, &points);

  printf("The number of distinct positions is: %d\n", pathLen);

  // print_map(argc, argv, len);
  // print_list(points);

  printf("The number of posible obstacle is: %d\n",
         check_obs(argc, argv, points, x, y));

  free_list(&points);
}
