/*-------------------------------------------------------------------------*/
/**
  @file     resources.c
  @author   Mahmoud Mheisen
  @date     Jan 2015
  @version  $Revision: 1.0 $
  @brief    Resource file for LTE simulator

  LTE Simulator Project: Undergraduate project for simulation the physical
  layer of fourth generation wirless communication standerd (LTE).
*/
/*--------------------------------------------------------------------------*/

// Including Libraries:
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

// Empty signal handler:
void catch_signal(int sig) {
}

// Catch signal CTRL-C:
void wait_for_ctrl_c(void) {
    signal(SIGTERM, catch_signal);
    signal(SIGINT, catch_signal);
    pause();
}

// Plot data:
int plot_y(double *y, int length, char *style, char *xlabel, char *ylabel, char *title) {

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

    return SUCCESS;
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

int nbits_number(int num) {
    int nbits = 1;

    nbits = log10(num+1)/log10(2) + 1;

    return nbits;
}
