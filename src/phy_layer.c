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
