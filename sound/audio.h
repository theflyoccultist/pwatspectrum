#ifndef AUDIO_H
#define AUDIO_H

#include <pulse/simple.h>
#include <stddef.h>
#include <stdint.h>

typedef struct {
  pa_simple *stream;
  int error;
} AudioInput;

AudioInput *init_audio();
int read_audio(AudioInput *audio, int16_t *buffer, size_t buffer_size);
void free_audio(AudioInput *audio);

#endif // !AUDIO_H
