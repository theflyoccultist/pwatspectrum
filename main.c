#include "ui/ui.h"
#include <stdio.h>

int main() {
  UI *ui = init_ui(35, 50);
  if (!ui || ui->error) {
    fprintf(stderr, "Failed to initialize UI\n");
    return 1;
  }

  render_ui(ui, 35, 50);
  free_ui(ui);

  return 0;
}
