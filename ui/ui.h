#ifndef UI_H
#define UI_H

#include <curses.h>

typedef struct {
  WINDOW *win;
  int error;
} UI;

UI *init_ui(int win_height, int win_width);
int render_ui(UI *window, int win_height, int win_width);
void free_ui(UI *window);

#endif // !UI_H
