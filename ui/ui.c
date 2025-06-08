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

  if (!has_colors()) {
    endwin();
    fprintf(stderr, "init_ui : No colors detected");
    window->error = 1;
    return window;
  }

  start_color();
  init_pair(1, COLOR_GREEN, COLOR_BLUE);
  init_pair(2, COLOR_BLACK, COLOR_GREEN);

  getmaxyx(stdscr, window->max_y, window->max_x);
  window->win = newwin(window->max_y, window->max_x, 0, 0);
  if (!window->win) {
    fprintf(stderr, "init_ui : newwin() failed");
    window->error = 2;
  }

  return window;
}

int render_ui(UI *window) {
  if (!window || !window->win)
    return -1;

  char *msg = "Audio Visualizer";
  int len = strlen(msg);

  box(window->win, 0, 0);
  refresh();

  // Title position, near the top, but below the border
  wattron(window->win, COLOR_PAIR(1));
  int msg_y = 1;
  int msg_x = (window->max_x - len) / 2;
  mvwprintw(window->win, msg_y, msg_x, "%s", msg);
  wattroff(window->win, COLOR_PAIR(1));

  // bar area, avoid title and borders
  int bar_top = msg_y + 2;
  int bar_bottom = window->max_y - 2;
  int bar_height = bar_bottom - bar_top;

  int bar_width = window->max_x - 2;
  int num_bars = bar_width;

  wattron(window->win, COLOR_PAIR(2));
  for (int i = 0; i < num_bars; ++i) {
    int bar_val = rand() % bar_height; // fake value
    for (int j = 0; j < bar_val; ++j) {
      int y = bar_bottom - j; // draw upward
      int x = i + 1;          // offset from left border
      mvwprintw(window->win, y, x, ".");
    }
  }
  wattroff(window->win, COLOR_PAIR(2));

  wrefresh(window->win);
  getch();

  return 0;
}

void free_ui(UI *window) {
  if (!window)
    return;
  if (window->win)
    delwin(window->win);

  endwin();
  free(window);
}
