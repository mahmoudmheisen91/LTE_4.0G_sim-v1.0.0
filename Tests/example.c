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
void poly_interlever(int *data, int length, int f1, int f2, int poly_data[length]);
void poly_deinterlever(int *data, int length, int f1, int f2, int depoly_data[length]);
int nbits_number(int num);
void lte_turbo_coding(int *data, int length, int gf, int gr,
                      int f1, int f2, int turbo_data[length]);
void lte_turbo_decoder(int *data, int length, int gf, int gr,
                      int f1, int f2, int decoded_data[length]);

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

    //double data2[10] = {0,1,2,3,4,5,6,7,8,9};
    //printf("%.4f\n", var(data2, 10));

    //double test1[10];
    //poly_interlever(data2, 10, 9, 0, test1);
    //printf("%.4f\n", var(test1, 10));

    //double test2[10];
    //poly_deinterlever(test1, 10, 9, 0, test2);
    //printf("%.4f\n", var(test2, 10));

    //printf("bits %d\n", nbits_number(2));

    int i;
    for(i = 0; i < 10; i++) {
        //printf("%.4f\n", test2[i]);
    }

    //plot_x(data, length, "lines", "Time", "Amplitute", "Test Signal");

    double quantized_data[length];
    int encoded_data[length];
    double error_signal[length];
    double snr_db = lte_adc(data, length, 2, quantized_data, encoded_data, error_signal);

    //printf("%.4f\n", snr_db);

    //plot_x(quantized_data, length, "lines", "Time", "Amplitute", "Test Signal");

    int gf   = 0b1101;
    int gr   = 0b1011;
    int f1   = 9;
    int f2   = 0;
    int turbo_data[2 * length];
    lte_turbo_coding(encoded_data, length, gf, gr, f1, f2, turbo_data);

    int decoded_data[length];
    lte_turbo_decoder(encoded_data, length, gf, gr, f1, f2, decoded_data);

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
    double SNR_dB    = 10 * log10(SNR);

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

void lte_turbo_coding(int *data, int length, int gf, int gr,
                      int f1, int f2, int turbo_data[2 * length]) {
    // 6)- Turbo Coding :
    int L = nbits_number(gr);

    // Encoding:
    int poly_data[length];
    poly_interlever(data, length, f1, f2, poly_data);

    int i;
    for(i = 0; i < 2 * length; i++) {
        if ((int) fmod(i, 2) == 0)
            turbo_data[i] = data[i/2];
        else
            turbo_data[i] = poly_data[i/2];
    }
}

void lte_turbo_decoder(int *data, int length, int gf, int gr,
                      int f1, int f2, int decoded_data[length]) {

    // Decoding:
    int depoly_data[length];

    int i, j;
    for(i = 0; i < 2 * length; i++) {
        if (i % 2 != 0)
            depoly_data[j++] = data[i];
    }

    poly_deinterlever(depoly_data, length, f1, f2, decoded_data);
}

void poly_interlever(int *data, int length, int f1, int f2, int poly_data[length]) {
    int i;
    for(i = 0; i < length; i++) {
        //printf("%.4f\n", fmod((f1 * i + f2 * pow(i, 2)), length));
        poly_data[i] = data[(int) fmod((f1 * i + f2 * pow(i, 2)), length)];
    }
}

void poly_deinterlever(int *data, int length, int f1, int f2, int depoly_data[length]) {
    int i;
    for(i = 0; i < length; i++) {
        //printf("%.4f\n", fmod((f1 * i + f2 * pow(i, 2)), length));
        depoly_data[(int) fmod((f1 * i + f2 * pow(i, 2)), length)] = data[i];
    }
}

int nbits_number(int num) {
    int nbits = 1;

    nbits = log10(num+1)/log10(2) + 1;

    return nbits;
}
