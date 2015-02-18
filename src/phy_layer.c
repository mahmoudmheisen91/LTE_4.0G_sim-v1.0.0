/*-------------------------------------------------------------------------*/
/**
  @file     phy_layer.c
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

void lte_modulation(int *data, int length, int M, double *table, double *mapped_symbols) {
    //double k = log10(M) / log10(2);

    /*
    for i = 1 : k : numberOfBits
        symbolIndex( (i - 1) / k + 1 ) = bi2de( input( i : i + k - 1 ) ,'left-msb' ) ;
    end
    MappedSymbols = MappingTable( symbolIndex + 1 ) ;
    */
}

void lte_demodulation(int *data, int length, int M, double *table, double *receives_signal) {
    //double k = log10(M) / log10(2);

    /*
        for i = 1 : length( ReceivedSignal )

            [a, MinIndex] = min( ReceivedSignal( i ) - MappingTable );  %#ok<*ASGLU>
            symbolIndex   = MinIndex - 1;
            bits          = de2bi( symbolIndex , k ,'left-msb' ) ;
            for h = 1 : k
                TempReg( ( i - 1 ) * k + h ) = bits( h );
            end
        end
        ReceivedBits = TempReg( 1 : length( TempReg ) - LengthMatcher ) ;
    */
}

void normalization(int *data, int length, double output[length]) {
    double sub = max(data, length) / 2.0;
    double maxy = max(data, length) - sub;

    int i;
    for(i = 0; i < length; i++) {
        output[i] = (data[i] - sub) / maxy;
    }
}
