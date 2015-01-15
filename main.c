/*
 * main.c
 *
 *  Created on: Jan 7, 2015
 *      Author: redapple
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "LTE_err.h"
#include "resources.h"
#include "phy_layer.h"

void main(void) {

    init();

    // Decleration:
    SNDFILE *sf1, *sf2;
    SF_INFO info;
    info.format = 0;

    // open sound file and read it:
    sf1 = sf_open("test_signal.wav", SFM_READ, &info);
    double data[info.frames];
    int length = sf_read_double(sf1, data, info.frames);
    sf_close(sf1);

    // plot original signal:
    plot_x(data, length, "lines", "Time", "Amplitute", "Test Signal");

    // open new sound file and write to it:
    sf2 = sf_open("test_signal_2.wav", SFM_WRITE, &info);
    sf_write_double(sf2, data, length) ;
    sf_close(sf2);


}
