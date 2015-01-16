/*-------------------------------------------------------------------------*/
/**
  @file     resources.h
  @author   Mahmoud Mheisen
  @date     Jan 2015
  @version  $Revision: 1.0 $
  @brief    Resource file for LTE simulator

  LTE Simulator Project: Undergraduate project for simulation the physical
  layer of fourth generation wirless communication standerd (LTE).
*/
/*--------------------------------------------------------------------------*/

#ifndef RESOURCES_H_
#define RESOURCES_H_

    // Including Libraries:
    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <string.h>
    #include <sndfile.h>
    #include <signal.h>
    #include <math.h>
    #include <time.h>
    #include "gnuplot_i.h"
    #include "LTE_err.h"

	// Define Constants::
	#define TRUE 		1
	#define FALSE 		0

	// type definition:


	// Functions Prototypes:
	int init(void);
    void catch_signal(int sig);
    void wait_for_ctrl_c(void);
    int plot_x(double *x, int length, char *style, char *xlabel, char *ylabel, char *title);
    double max(double  *data, int length);
    double min(double  *data, int length);
    double mean(double *data, int length);
    double var(double *data, int length);


#endif /* RESOURCES_H_ */

