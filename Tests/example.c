#include <stdio.h>
#include <stdlib.h>
#include <sndfile.h>
#include <math.h>
#include "gnuplot_i.h"
#include <signal.h>

void catch_signal(int sig);
void wait_for_ctrl_c(void);
void plot_x(double *x, int length, char *style, char *xlabel, char *ylabel, char *title);
double lte_adc(double *data, int length, int nbits,double quantized_data[length],
               int encoded_data[length], double error_signal[length]);
double max(double *data, int length);
double min(double *data, int length);
double mean(double *data, int length);
double var(double *data, int length);

void main(void) {

    // Decleration:
    SNDFILE *sf1, *sf2;
    SF_INFO info;
    info.format = 0;

    // open sound file and read it:
    sf1 = sf_open("test_signal.wav", SFM_READ, &info);
    double data[info.frames];
    int length = sf_read_double(sf1, data, info.frames);
    sf_close(sf1);

    double data2[10] = {0,1,2,3,4,5,6,7,8,9};
    printf("%.4f\n", var(data2, 10));

    //plot_x(data, length, "lines", "Time", "Amplitute", "Test Signal");

    double quantized_data[length];
    int encoded_data[length];
    double error_signal[length];
    double snr_db = lte_adc(data, length, 2, quantized_data, encoded_data, error_signal);

    printf("%.4f\n", snr_db);

    plot_x(quantized_data, length, "lines", "Time", "Amplitute", "Test Signal");

    // open new sound file and write to it:
    sf2 = sf_open("test_signal_2.wav", SFM_WRITE, &info);
    sf_write_double(sf2, quantized_data, length) ;
    sf_close(sf2);
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

double lte_adc(double *data, int length, int nbits, double quantized_data[length],
               int encoded_data[length], double error_signal[length]) {

    // Parameters:
    double data_max = max(data, length);
    double data_min = min(data, length);
    int nlevels = pow(2, nbits);
    double delta = (data_max - data_min) / (nlevels - 1);

    // Function:
    long i;
    int j;
    for(i = 0; i < length; i++) {
        for(j = 1; j <= nlevels; j++) {
            if ((data[i] > data_min + delta * (j-1)) && (data[i] < data_min + delta * j)) {
                if ((data_min + delta * (j-1)) > data_max) {
                    break;
                }

                quantized_data[i] =  data_min + delta * (j-1);
                encoded_data[i] = j;
            }
        }
    }

    // Error:
    int k;
    for (k = 0; k < length; k++)
        error_signal[k] = quantized_data[k] - data[k];

    double data_var  = var(data, length);
    double error_var = var(error_signal, length);
    double SNR       = pow((data_var / error_var), 2);
    double SNR_dB    = 10 * log(SNR);

    return SNR_dB;
}

double max(double *data, int length) {
    int i;
    double result = -999999.99;
    for(i = 0; i < length; i++) {
        if(data[i] > result)
            result = data[i];
    }
    return result;
}

double min(double *data, int length) {
    int i;
    double result = 999999.99;
    for(i = 0; i < length; i++) {
        if(data[i] < result)
            result = data[i];
    }
    return result;
}

double mean(double *data, int length) {
    int i;
    double result = 0.0;
    for(i = 0; i < length; i++)
        result += data[i];

    return result / length;
}

double var(double *data, int length) {
    int i;
    double result = 0;
    double data_mean = mean(data, length);

    for(i = 0; i < length; i++)
        result += pow((data[i] - data_mean), 2);

    return result / (length - 1);
}
