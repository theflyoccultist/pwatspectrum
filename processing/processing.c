#include <fftw3.h>

#define BUFFER_SIZE 1024

fftw_plan init_process() {
  float input[BUFFER_SIZE];
  fftw_complex out[BUFFER_SIZE];
  fftw_plan fft_plan =
      fftw_plan_dft_r2c_1d(BUFFER_SIZE, (double *)input, out, FFTW_ESTIMATE);
  return fft_plan;
}

void apply_fft() { fftw_execute(init_process()); }

void clean_process(fftw_plan fft_plan) { fftw_destroy_plan(fft_plan); }
