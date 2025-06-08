// What i tried making:
// use the pulseaudio api to visualize music. at the moment, i want it to grab
// an audio input from a microphone
// testing:
// ./myaudio > test.raw
// aplay -f S16_LE -r 44100 -c 1 test.raw

#include <errno.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#include <pulse/error.h>
#include <pulse/simple.h>

#include "audio.h"

AudioInput *init_audio() {
  AudioInput *audio = malloc(sizeof(AudioInput));
  if (!audio)
    return NULL;

  static const pa_sample_spec ss = {
      .format = PA_SAMPLE_S16LE,
      .channels = 1,
      .rate = 44100,
  };

  audio->stream = pa_simple_new(NULL, "rec", PA_STREAM_RECORD, NULL, "Record",
                                &ss, NULL, NULL, &audio->error);
  if (!audio->stream) {
    fprintf(stderr, "init_audio : pa_simple_new() failed: %s\n",
            pa_strerror(audio->error));
    free(audio);
    return NULL;
  }

  return audio;
}

static ssize_t loop_write(int fd, const void *data, size_t size) {
  ssize_t ret = 0;

  while (size > 0) {
    ssize_t r;

    if ((r = write(fd, data, size)) < 0)
      return r;

    if (r == 0)
      break;

    ret += r;
    data = (const uint8_t *)data + r;
    size -= (size_t)r;
  }
  return ret;
}

int read_audio(AudioInput *audio, int16_t *buffer, size_t buffer_size) {
  if (!audio || !audio->stream)
    return -1;

  if (pa_simple_read(audio->stream, buffer, buffer_size, &audio->error) < 0) {
    fprintf(stderr, "read_audio : pa_simple_read() failed: %s\n",
            pa_strerror(audio->error));
    return -1;
  }

  ssize_t written = loop_write(STDOUT_FILENO, buffer, buffer_size);
  if (written < 0 || written != (ssize_t)buffer_size) {
    fprintf(stderr, "read_audio : loop_write() failed: %s\n", strerror(errno));
    return -1;
  }

  return 0;
}

void free_audio(AudioInput *audio) {
  if (!audio)
    return;
  if (audio->stream)
    pa_simple_free(audio->stream);
  free(audio);
}
