#include <stdio.h>
#include <stdlib.h>
#include <sndfile.h>
#include "gnuplot_i.h"
#include <signal.h>

void catch_signal(int sig);
void wait_for_ctrl_c(void);
void plot_x(double *x, int length, char *style, char *xlabel, char *ylabel, char *title);
double *wav_read(char *dir, int *length, int *FS);

void main(void) {

    // Decleration:
    //SNDFILE *sf1, *sf2;

    int length = 0;
    int fs = 0;
    double *data;

    // open sound file and read it:
    data = wav_read("test_signal.wav", &length, &fs);

    plot_x(data, length, "lines", "Time", "Amplitute", "Test Signal");
    plot_x(data, length, "lines", "Time", "Amplitute", "Test Signal");

    // open new sound file and write to it:
//    sf2 = sf_open("test_signal_2.wav", SFM_WRITE, &info);
  //  sf_write_double(sf2, data, length) ;
    //sf_close(sf2);
}

// Empty signal handler:
void catch_signal(int sig) {
}

// Catch signal CTRL-C:
void wait_for_ctrl_c(void) {
    signal(SIGTERM, catch_signal);
    signal(SIGINT, catch_signal);
    pause();
}

void plot_x(double *x, int length, char *style, char *xlabel, char *ylabel, char *title) {

    // init plot:
    gnuplot_ctrl *handler;
    handler = gnuplot_init();

    // Style and Labels:
    gnuplot_setstyle(handler, style) ;
    gnuplot_set_xlabel(handler, xlabel) ;
    gnuplot_set_ylabel(handler, ylabel) ;

    // Plot:
    gnuplot_plot_x(handler, x, length, title);

    // wait for CTRL-c is typed:
    wait_for_ctrl_c();

    // Close plot to remove tmp files:
    gnuplot_close(handler);
}

double* wav_read(char *dir, int *length, int *FS) {

    SNDFILE *sfp;
    SF_INFO info;
    info.format = 0;

    sfp = sf_open(dir, SFM_READ, &info);
    double data2[info.frames];
    *FS = info.samplerate;
    int len = sf_read_double(sfp, data2, info.frames);
    *length = len;

    double *data;
    data = &data2;
    sf_close(sfp);

    return data2;
}
