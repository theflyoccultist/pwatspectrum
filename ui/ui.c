// This is the ncurses ui to visualize audio bars to the terminal.

#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ui.h"

UI *init_ui() {
  UI *window = malloc(sizeof(UI));
  if (!window)
    return NULL;

  window->win = NULL;
  window->error = 0;

  initscr();
  cbreak();
  noecho();
  curs_set(FALSE);
  nodelay(stdscr, TRUE);

  if (!has_colors()) {
    endwin();
    fprintf(stderr, "init_ui : No colors detected");
    window->error = 1;
    return window;
  }

  start_color();
  init_pair(1, COLOR_GREEN, COLOR_BLUE);
  init_pair(2, COLOR_RED, COLOR_GREEN);

  getmaxyx(stdscr, window->max_y, window->max_x);
  window->win = newwin(window->max_y, window->max_x, 0, 0);
  if (!window->win) {
    fprintf(stderr, "init_ui : newwin() failed");
    window->error = 2;
  }

  return window;
}

void free_ui(UI *window) {
  if (!window)
    return;
  if (window->win)
    delwin(window->win);

  endwin();
  free(window);
}
