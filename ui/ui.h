#ifndef UI_H
#define UI_H

#include <curses.h>

typedef struct {
  int max_y;
  int max_x;
  WINDOW *win;
  int error;
} UI;

UI *init_ui();
void free_ui(UI *window);

#endif // !UI_H
