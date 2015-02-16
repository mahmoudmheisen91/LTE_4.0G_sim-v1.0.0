/*-------------------------------------------------------------------------*/
/**
  @file     interleaver.c
  @author   Mahmoud Mheisen
  @date     Feb 2015
  @version  $Revision: 1.0 $
  @brief    Resource file for LTE simulator

  LTE Simulator Project: Undergraduate project for simulation the physical
  layer of fourth generation wirless communication standerd (LTE).
*/
/*--------------------------------------------------------------------------*/

// Including Libraries:
#include "phy_layer.h"

void poly_interleaver(int *data, int length, int f1, int f2, int poly_data[]) {
    int i;
    for(i = 0; i < length; i++) {
        //printf("%.4f\n", fmod((f1 * i + f2 * pow(i, 2)), length));
        poly_data[i] = data[(int) fmod((f1 * i + f2 * pow(i, 2)), length)];
    }
}

void poly_deinterleaver(int *data, int length, int f1, int f2, int depoly_data[length]) {
    int i;
    for(i = 0; i < length; i++) {
        //printf("%.4f\n", fmod((f1 * i + f2 * pow(i, 2)), length));
        depoly_data[(int) fmod((f1 * i + f2 * pow(i, 2)), length)] = data[i];
    }
}
