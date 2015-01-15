/*
 * resources.c
 *
 *  Created on: Jan 7, 2015
 *      Author: redapple
 */

// Including Libraries:
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "LTE_err.h"
#include "resources.h"

// Print Heading:
int init(void) {

	printf("---------------------------------\n");
	printf("PROJECT : LTE SIMULATOR\n");
	printf("AUTHOR  : MAHMOUD MHEISEN\n");
	printf("COURSE  : Undergraduate Project\n");
	printf("---------------------------------\n");

	return SUCCESS;
}

// Read .wav file:
void wav_read(char* dir) {
    SNDFILE *sound_file;
    SF_INFO sound_info;
    int f, sr, c;

    /* Open the WAV file. */
    sound_info.format = 0;
    sound_file = sf_open(dir, SFM_READ, &sound_info);

    if (sound_file == NULL) {
        printf("Failed to open the file.\n");
        FAIL;
    }

    /* Print some of the info, and figure out how much data to read. */
    f = sound_info.frames;
    sr = sound_info.samplerate;
    c = sound_info.channels;

    /*
	[ data , Fs , nbits ] = wavread( 'testSignal' ) ;

    fprintf('----------------  \n');
	fprintf('nbits = %d bits \n', nbits );
	fprintf('Fs    = %d KHz   \n', Fs/1000 );
	fprintf('----------------  \n');
	pause

	f1 = figure('position',[150 115 1100 500]) ;
	hold on
	grid on
	xlabel('Sample');
	ylabel('Amplitude')
	title( ' Audio Signal ' )
	plot( data )
	%sound( data , Fs )
	print( f1 , '-dbmp', '-noui', 'C:\Users\win7\Desktop\Results\OriginalSignal' );
	hold off
    */
	return (Sound) SUCCESS;
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
