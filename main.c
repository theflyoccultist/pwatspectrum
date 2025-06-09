#include "processing/processing.h"
#include "sound/audio.h"
#include "ui/ui.h"

#include <curses.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main() {
  UI *ui = init_ui();
  if (!ui || ui->error) {
    fprintf(stderr, "Failed to initialize UI\n");
    return 1;
  }

  AudioInput *audio = init_audio();
  if (!audio || audio->error) {
    fprintf(stderr, "Failed to initialize audio\n");
    return 1;
  }
  int16_t samples[BUFFER_SIZE];

  FFTData *fft = init_fft(BUFFER_SIZE);
  if (!fft) {
    fprintf(stderr, "Failed to initialize FFT\n");
    return 1;
  }

  while (1) {
    int ch = getch();
    if (ch == 'q')
      break;

    read_audio(audio, samples, BUFFER_SIZE);
    // printf("First sample: %d\n", samples[0]);
    apply_fft(fft, samples);

    werase(ui->win);
    box(ui->win, 0, 0);

    int bar_height = ui->max_y - 2;
    int total_width = ui->max_x - 2;
    int max_bins = BUFFER_SIZE / 2;
    static int prev_heights[BUFFER_SIZE / 2] = {0};

    for (int i = 1; i < total_width && i < max_bins; ++i) {
      double real = fft->output[i][0];
      double imag = fft->output[i][1];
      double magnitude = sqrt(real * real + imag * imag);
      magnitude = log10(magnitude + 1);
      if (magnitude > 1.0)
        magnitude = 1.0;

      int target_height = (int)(magnitude * bar_height);

      // Apply decay
      if (target_height >= prev_heights[i]) {
        prev_heights[i] = target_height;
      } else {
        prev_heights[i] -= 3; // change decay here
        if (prev_heights[i] < 0)
          prev_heights[i] = 0;
      }

      for (int y = 0; y < prev_heights[i]; ++y) {
        int color_index = 1 + (y * 3) / bar_height;
        color_index = (color_index > 3) ? 3 : color_index;

        wattron(ui->win, COLOR_PAIR(color_index));
        mvwprintw(ui->win, bar_height - y, i + 1, "|");
        wattroff(ui->win, COLOR_PAIR(color_index));
      }
    }

    wrefresh(ui->win);
    usleep(8000); // tweak this for refresh rate
  }

  destroy_fft(fft);
  free_audio(audio);
  free_ui(ui);

  return 0;
}
