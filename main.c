#include "ui/ui.h"
#include <stdio.h>

int main() {
  UI *ui = init_ui();
  if (!ui || ui->error) {
    fprintf(stderr, "Failed to initialize UI\n");
    return 1;
  }

  render_ui(ui);
  free_ui(ui);

  return 0;
}
