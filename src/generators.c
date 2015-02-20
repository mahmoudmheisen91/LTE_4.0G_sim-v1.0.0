/*-------------------------------------------------------------------------*/
/**
  @file     generators.c
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
#include "resources.h"

void generate_mapping_table(int M, int M1, double *table) {

    int angle = 0 ;
    int ampde = 1 ;
    int vector[M1];

    int i;
    for(i = 0; i < M1; i++) {
        vector[i] = i+1;
    }

    int j;
    for(j = 0; j < M; j++) {
        table[j] = vector[ampde] * exp(angle * 3.14 / (M/M1));
        angle += 2;
        if ((int) fmod(j, (M/M1)) == 0 ) {
            ampde++;
            angle = 0;
        }
    }
}
