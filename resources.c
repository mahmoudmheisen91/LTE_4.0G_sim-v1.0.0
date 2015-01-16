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
int plot_x(double *x, int length, char *style, char *xlabel, char *ylabel, char *title) {

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
