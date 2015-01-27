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

void poly_interlever(int *data, int length, int f1, int f2, int poly_data[]) {
    int i;
    for(i = 0; i < length; i++) {
        //printf("%.4f\n", fmod((f1 * i + f2 * pow(i, 2)), length));
        poly_data[i] = data[(int) fmod((f1 * i + f2 * pow(i, 2)), length)];
    }
}

void poly_deinterlever(int *data, int length, int f1, int f2, int depoly_data[length]) {
    int i;
    for(i = 0; i < length; i++) {
        //printf("%.4f\n", fmod((f1 * i + f2 * pow(i, 2)), length));
        depoly_data[(int) fmod((f1 * i + f2 * pow(i, 2)), length)] = data[i];
    }
}

void lte_turbo_encoder(int *data, int length, int gf, int gr,
                      int f1, int f2, int turbo_data[2 * length]) {
    // 6)- Turbo Coding :
    int L = nbits_number(gr);

    // Encoding:
    int *poly_data;
    poly_data = (int*)malloc(sizeof(int) * length);

    poly_interlever(data, length, f1, f2, poly_data);

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

    poly_deinterlever(depoly_data, length, f1, f2, decoded_data);
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
    double k = log10(M) / log10(2);

    /*
    for i = 1 : k : numberOfBits
        symbolIndex( (i - 1) / k + 1 ) = bi2de( input( i : i + k - 1 ) ,'left-msb' ) ;
    end
    MappedSymbols = MappingTable( symbolIndex + 1 ) ;
    */
}

void lte_demodulation(int *data, int length, int M, double *table, double *receives_signal) {
    double k = log10(M) / log10(2);

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

/*
void normalization(void) {
	%% 13)- Normalization :

	ReceivedData = expandedData / max(expandedData) ;

	encodedData3  = S2P(ReceivedData,r,c) ;
	encodedData4 = bi2de(encodedData3 , 'left-msb' ) ;

	title( ' Audio Signal ' )
	plot( encodedData4 )
}
*/
