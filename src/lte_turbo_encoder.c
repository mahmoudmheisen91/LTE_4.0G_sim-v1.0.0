/*-------------------------------------------------------------------------*/
/**
  @file     lte_turbo_encoder.c
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

void lte_turbo_encoder(int *data, int length, int gf, int gr,
                      int f1, int f2, int turbo_data[2 * length]) {
    // 6)- Turbo Coding :
    //int L = nbits_number(gr);

    // Encoding:
    int *poly_data;
    poly_data = (int*)malloc(sizeof(int) * length);

    poly_interleaver(data, length, f1, f2, poly_data);

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

    poly_deinterleaver(depoly_data, length, f1, f2, decoded_data);
}
