/*-------------------------------------------------------------------------*/
/**
  @file     main.c
  @author   Mahmoud Mheisen
  @date     Jan 2015
  @version  $Revision: 1.0 $
  @brief    main file

  LTE Simulator Project: Undergraduate project for simulation the physical
  layer of fourth generation wirless communication standerd (LTE).
*/
/*--------------------------------------------------------------------------*/

// Including Libraries:
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sndfile.h>
#include <signal.h>
#include <time.h>
#include "LTE_err.h"
#include "gnuplot_i.h"
#include "resources.h"
#include "phy_layer.h"

void main(void) {

    // TODO:
    // S2P
    // P2S
    // encoder
    // decoder

    // Software init:
    init();

    // Decleration:
    SNDFILE *sf1, *sf2;
    SF_INFO info;
    info.format = 0;

    // TODO: image
    // TODO: imshow
    printf("Enter 1 for image and 2 for voice.\n");

    // open sound file and read it:
    // TODO: know number of bits
    // TODO: sound matlab
    sf1 = sf_open("test_signal.wav", SFM_READ, &info);
    double data[info.frames];
    int length = sf_read_double(sf1, data, info.frames);
    int Fs = info.samplerate;
    sf_close(sf1);

    // print info to screen:
    printf("---------------------------------\n");
    printf("Length = %d sample\n", length );
    printf("Fs     = %d KHz   \n", Fs/1000 );
    printf("---------------------------------\n");
    wait_for_ctrl_c();

    // plot original signal:
    plot_y(data, length, "lines", "Sample", "Amplitude", "Audio Signal");

    // plot vs orignal time:
    int i;
    double time[length];
    for(i = 0; i < length; i++) {
        time[i] = i / fs;
    }
    plot_xy(time, data, length, "lines", "Time", "Amplitute", "Test Signal");


    // ADC using 4 bits:
    double quantized_data[length];
    int encoded_data[length];
    double error_signal[length];
    int nbits = 4; // TODO as user/command input
    double snr_db = lte_adc(data, length, nbits, quantized_data, encoded_data, error_signal);

    // print info to screen:
    printf("---------------------------------\n");
    printf('nlevels = %d level \n', pow(2, nbits));
    printf("SNR_dB  = %.4f dB   \n", snr_db);
    printf("---------------------------------\n");
    wait_for_ctrl_c();

    // plot quantized signal:
    plot_x(quantized_data, length, "lines", "Time", "Amplitute", "Quantized Signal");

    // plot error signal:
    // TODO: FFT plot:
    plot_x(error_signal, length, "lines", "Time", "Amplitute", "Error Signal");

    // TODO:
    /*
    fprintf('-----------------------------------  \n');
    fprintf('Nbits before Encoding = %d  bit \n', length(enycrptedData));
    fprintf('Nbits after  Encoding = %d bit \n', length(turboData));
    fprintf('-----------------------------------  \n');
    */

    // Encoding:
    int gf   = 0b1101;
    int gr   = 0b1011;
    int f1   = 9;
    int f2   = 0;
    int turbo_data[2 * length];
    lte_turbo_coding(encoded_data, length, gf, gr, f1, f2, turbo_data);

    // Decoding:
    int decoded_data[length];
    lte_turbo_decoder(encoded_data, length, gf, gr, f1, f2, decoded_data);

    // open new sound file and write to it:
    sf2 = sf_open("test_signal_2.wav", SFM_WRITE, &info);
    sf_write_double(sf2, quantized_data, length) ;
    sf_close(sf2);


}
