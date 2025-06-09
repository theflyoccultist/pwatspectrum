# PwatSpectrum

PwatSpectrum is a real-time terminal audio visualizer powered by ncurses, PulseAudio, FFTW and caffeine. Written in C, it is inspired by the 2000s club nights. It is very performant, looks hot, and usually does not leak memory.

- `ui` folder:
Contains all the setup for the ncurses library, including window initialization and color setup.

- `sound` folder:
Initializes and sets up the audio input and read.

- `processing` folder:
Needed for the fftw setup, as well as for the Hann window.

- `main.c` file:
Binds those three libraries together so that the spectrogram can be displayed to the terminal.

---

![Preview](preview.png)

Simply compile with `make`, run the compiled binary on your terminal while playing some music or other forms of audio from your computer.

You will probably need to install those libraries so it runs on your machine:

```sh
sudo apt-get install libncurses-dev libpulse-dev
```

The FFTW library present in the apt package manager is outdated, so you would have to build `fftw-3.3.10.tar.gz` from source to get a more recent version. You would have to unzip the archive and run `make install`.

As someone who was very much into music and sound engineering before moving to programming, this kind of project was bound to happen. There will be more audio related projects to come.
