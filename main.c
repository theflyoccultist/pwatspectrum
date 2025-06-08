// #include "sound/audio.h"
#include "ui/ui.h"

#include <curses.h>
#include <stdio.h>

int main() {
  UI *ui = init_ui();
  if (!ui || ui->error) {
    fprintf(stderr, "Failed to initialize UI\n");
    return 1;
  }

  render_ui(ui);

  int c;
  while ((c = getch()) != 'q') {
    if (c == 114)
      printw("r pressed!\n");
  }

  free_ui(ui);

  return 0;
}
