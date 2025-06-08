#ifndef PROCESSING_H
#define PROCESSING_H

#include <fftw3.h>
#include <stdint.h>

typedef struct {
  fftw_plan plan;
  double *input;
  fftw_complex *output;
  int buffer_size;
} FFTData;

FFTData *init_fft(int buffer_size);
void apply_fft(FFTData *fft, int16_t *samples);
void destroy_fft(FFTData *fft);

#endif // !PROCESSING_H
