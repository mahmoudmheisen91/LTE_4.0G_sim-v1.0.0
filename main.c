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

    // Software init:
    init();

    // Decleration:
    SNDFILE *sf1, *sf2;
    SF_INFO info;
    info.format = 0;

    // open sound file and read it:
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
    plot_x(data, length, "lines", "Sample", "Amplitude", "Audio Signal");

    // open new sound file and write to it:
    sf2 = sf_open("test_signal_2.wav", SFM_WRITE, &info);
    sf_write_double(sf2, data, length) ;
    sf_close(sf2);


}
