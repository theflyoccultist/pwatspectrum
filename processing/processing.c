#include "processing.h"
#include <fftw3.h>
#include <stdlib.h>

FFTData *init_fft(int buffer_size) {
  FFTData *fft = malloc(sizeof(FFTData));
  fft->buffer_size = buffer_size;

  fft->input = fftw_malloc(sizeof(double) * buffer_size);
  fft->output = fftwf_malloc(sizeof(fftw_complex) * (buffer_size / 2 + 1));

  fft->plan =
      fftw_plan_dft_r2c_1d(buffer_size, fft->input, fft->output, FFTW_ESTIMATE);

  return fft;
}

void apply_fft(FFTData *fft, int16_t *samples) {
  for (int i = 0; i < fft->buffer_size; ++i)
    fft->input[i] = (double)samples[i];

  fftw_execute(fft->plan);
}

void destroy_fft(FFTData *fft) {
  fftw_destroy_plan(fft->plan);
  fftw_free(fft->input);
  fftw_free(fft->output);
  free(fft);
}
