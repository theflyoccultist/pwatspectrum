#include "processing.h"
#include <fftw3.h>
#include <math.h>
#include <stdlib.h>

FFTData *init_fft(int buffer_size) {
  FFTData *fft = malloc(sizeof(FFTData));
  if (!fft)
    return NULL;

  fft->buffer_size = buffer_size;
  fft->input = fftw_malloc(sizeof(double) * buffer_size);
  fft->output = fftw_malloc(sizeof(fftw_complex) * (buffer_size / 2 + 1));

  if (!fft->input || !fft->output) {
    fftw_free(fft->input);
    fftw_free(fft->output);
    free(fft);
    return NULL;
  }

  fft->plan =
      fftw_plan_dft_r2c_1d(buffer_size, fft->input, fft->output, FFTW_ESTIMATE);
  if (!fft->plan) {
    fftw_free(fft->input);
    fftw_free(fft->output);
    free(fft);
    return NULL;
  }

  return fft;
}

void apply_fft(FFTData *fft, int16_t *samples) {
  for (int i = 0; i < fft->buffer_size; ++i)
    fft->input[i] = (double)samples[i] *
                    (0.5 * (1 - cos(2 * M_PI / (fft->buffer_size - 1))));

  fftw_execute(fft->plan);
}

void destroy_fft(FFTData *fft) {
  fftw_destroy_plan(fft->plan);
  fftw_free(fft->input);
  fftw_free(fft->output);
  free(fft);
}
