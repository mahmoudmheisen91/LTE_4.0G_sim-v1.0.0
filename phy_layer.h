/*-------------------------------------------------------------------------*/
/**
  @file     phy_layer.h
  @author   Mahmoud Mheisen
  @date     Jan 2015
  @version  $Revision: 1.0 $
  @brief    Physical layer block diagrams

  LTE Simulator Project: Undergraduate project for simulation the physical
  layer of fourth generation wirless communication standerd (LTE).
*/
/*--------------------------------------------------------------------------*/

#ifndef PHY_LAYER_H_
#define PHY_LAYER_H_

    // Including Libraries:
    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <string.h>
    #include <sndfile.h>
    #include <signal.h>
    #include <math.h>
    #include <time.h>
    #include "LTE_err.h"
    #include "resources.h"

	// Define Constants::
	#define TRUE 		1
	#define FALSE 		0

	// type definition:

	// Functions Prototypes:
    double lte_adc(double *data, int length, int nbits,double quantized_data[length],
                   int encoded_data[length], double error_signal[length]);
    void poly_interlever(double *data, int length, int f1, int f2, double poly_data[length]);
    void poly_deinterlever(double *data, int length, int f1, int f2, double depoly_data[length]);

#endif /* PHY_LAYER_H_ */
