/*-------------------------------------------------------------------------*/
/**
  @file     lte_adc.c
  @author   Mahmoud Mheisen
  @date     Jan 2015
  @version  $Revision: 1.0 $
  @brief    Physical layer block diagrams

  LTE Simulator Project: Undergraduate project for simulation the physical
  layer of fourth generation wirless communication standerd (LTE).
*/
/*--------------------------------------------------------------------------*/

// Including Libraries:
#include "phy_layer.h"

double lte_adc(double *data, int length, int nbits, double quantized_data[length],
               int encoded_data[length], double error_signal[length]) {

    // Parameters:
    double data_max = max(data, length);
    double data_min = min(data, length);
    int nlevels = pow(2, nbits);
    double delta = (data_max - data_min) / (nlevels - 1);

    // Function:
    long i;
    int j;
    for(i = 0; i < length; i++) {
        for(j = 1; j <= nlevels; j++) {
            if ((data[i] > data_min + delta * (j-1)) && (data[i] < data_min + delta * j)) {
                if ((data_min + delta * (j-1)) > data_max) {
                    break;
                }

                quantized_data[i] =  data_min + delta * (j-1);
                encoded_data[i] = j;
            }
        }
    }

    // Error:
    int k;
    for (k = 0; k < length; k++)
        error_signal[k] = quantized_data[k] - data[k];

    double data_var  = var(data, length);
    double error_var = var(error_signal, length);
    double SNR       = pow((data_var / error_var), 2);
    double SNR_dB    = 10 * log(SNR);

    return SNR_dB;
}
