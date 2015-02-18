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
