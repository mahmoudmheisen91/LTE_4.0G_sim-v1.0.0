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
    int poly_data[length];
    poly_interlever(data, length, f1, f2, poly_data);

    int i;
    for(i = 0; i < 2 * length; i++) {
        if ((int) fmod(i, 2) == 0)
            turbo_data[i] = data[i/2];
        else
            turbo_data[i] = poly_data[i/2];
    }
}

/*

void compression(void) {
	%% 4)- Compression :

	[ encodedDataCompressed , finder , N1 ] = LTE_COMPRESS( encodedData' ,Nlevels ) ;

	fprintf('----------------------------------------  \n');
	fprintf('Nbits before Compression = %d bit \n', length(encodedData) * 8 );
	fprintf('Nbits after  Compression = %d  bit \n', length(encodedDataCompressed));
	fprintf('Compression Ratio        = %2.2f percent \n', length(encodedDataCompressed)*100/(length(encodedData) * 8) );
	fprintf('----------------------------------------  \n');

	% sound(encodedDataCompressed,10*Fs)
	pause

}

void security(void) {
	%% 5)- Securety :

	MAC = '8A89F6F0' ;

	enycrptedData = encodedDataCompressed ;
	% [ enycrptedData , MAC ] = LTE_SECURITY( encodedDataCompressed , Count , Bearer , Fresh , Direction , CK , IK ) ;

	fprintf('------------------------------------  \n');
	fprintf('Nbits before Encryption = %d bit \n', length(encodedDataCompressed));
	fprintf('Nbits after  Encryption = %d bit \n', length(enycrptedData));
	fprintf('MAC = %s \n', MAC );
	fprintf('------------------------------------  \n');

	pause
}

void modulation(void) {
	%% 7)- Modulation :

	fprintf('---------------------------------------\n');
	M  = input('Enter Modulation order,       M  = ') ;
	M1 = input('Enter Modulation Type Number, M1 = ') ;
	fprintf('---------------------------------------\n');

	type2 = 'qam' ;
	[ MappingTable , trell ] = LTE_CONTROL( M , M1 , type2 , gf , gr ) ;

	f5 = figure('position',[300 80 800 600]) ;

	hold on
	grid on
	xlabel('Real Part');
	ylabel('Imaginary Part')
	title( ' QAM Cancelation ' )
	plot( MappingTable , ':' )
	plot( MappingTable , 'sr' )
	print( f5 , '-dbmp', '-noui', 'C:\Users\win7\Desktop\Results\QAM Cancelation' );
	hold off

	pause
	close all

	[ MappedSymbols , LengthMatcher ] = LTE_MODULATION( turboData , M , MappingTable ) ;

	f6 = figure('position',[300 80 800 600]) ;

	hold on
	grid on
	xlabel('Real Part');
	ylabel('Imaginary Part')
	title( ' Mapped Symbols ' )
	plot( MappingTable , '--m' )
	plot( MappedSymbols , 'sk' )
	print( f6 , '-dbmp', '-noui', 'C:\Users\win7\Desktop\Results\Mapped Symbols' );
	hold off

	pause
	close all

}

void channel(void) {
	%% 8)- Channel :

	fprintf('-------------------------\n');
	SNR  = input('Enter AWGN SNR, SNR  = ') ;
	fprintf('-------------------------\n');

	[ ReceivedSignal , Lc ] = LTE_CHANNEL( MappedSymbols  , SNR  ) ;

	channelResponse = ones(1,1000) ;
	output  = LTE_CHANNEL( channelResponse  , SNR  ) ;

	f7 = figure('position',[300 80 800 600]) ;

	hold on
	grid on
	xlabel('Time Slot');
	ylabel('Amplitude')
	title( ' Channel Response ' )
	plot( output)
	print( f7 , '-dbmp', '-noui', 'C:\Users\win7\Desktop\Results\Channel Response' );
	hold off

	pause
	close all

	f8 = figure('position',[300 80 800 600]) ;

	hold on
	grid on
	xlabel('Real Part');
	ylabel('Imaginary Part')
	title( ' Received Signal ' )
	plot( MappingTable , '--m' )
	plot( ReceivedSignal , 'sk' )
	print( f8 , '-dbmp', '-noui', 'C:\Users\win7\Desktop\Results\Received Signal' );
	hold off

	pause
	close all
}

void demodulation(void) {
	%% 9)- Demodulation :

	ReceivedBits = LTE_DEMODULATION( ReceivedSignal ,  MappingTable , M , LengthMatcher ) ;

	f9 = figure('position',[300 80 800 600]) ;

	hold on
	grid on
	xlabel('Real Part')
	ylabel('Imaginary Part')
	title( ' Received Signal ' )
	plot( MappingTable , '--m' )
	plot( MappingTable , '*k' )
	print( f9 , '-dbmp', '-noui', 'C:\Users\win7\Desktop\Results\Received Bits cancelation' );
	hold off

	pause
	close all

	error = sum( abs( xor( ReceivedBits , turboData ) ) ) ;
	BER   = error / length( turboData )  ;

	fprintf('-----------------------------  \n');
	fprintf('BER before Decoding = %2.4f \n', BER);
	fprintf('-----------------------------  \n');

	pause

}

void decoding(void) {
	%% 10)- Decoding :

	fprintf('----------------------------------------------\n');
	iterationNum  = input('Enter decoder iteration Num, iterationNum  = ') ;
	fprintf('----------------------------------------------\n');

	decodedBits  = LTE_DECODER( ReceivedBits , trell  , gr , Lc , iterationNum , type1 );

	error = sum( abs( xor( decodedBits , enycrptedData ) ) ) ;
	BER2  = error / length( enycrptedData )  ;

	fprintf('-----------------------------  \n');
	fprintf('BER before Decoding = %2.4f \n', BER);
	fprintf('BER after  Decoding = %2.4f \n', BER2);
	fprintf('-----------------------------  \n');

	pause
}

void security(void) {

	%% 11)- Securety :

	decryptedData = decodedBits ;
	% [ decryptedData , MAC ] = LTE_SECURITY( decodedBits , Count , Bearer , Fresh , Direction , CK , IK ) ;

	fprintf('------------------------------------  \n');
	fprintf('Nbits before Decryption = %d bit \n', length(encodedDataCompressed));
	fprintf('Nbits after  Decryption = %d bit \n', length(enycrptedData));
	fprintf('------------------------------------  \n');

	pause
}

void expansion(void) {

	%% 12)- Expantion :

	expandedData  = LTE_EXPANDER( decryptedData , finder , N1 ) ;

	fprintf('----------------------------------------  \n');
	fprintf('Nbits before Expantion = %d bit \n', length(decryptedData) );
	fprintf('Nbits after  Expantion = %d bit \n', length(expandedData)*8);
	fprintf('Compression Ratio      = %2.2f percent \n', length(decryptedData)*100/(length(expandedData)*8) );
	fprintf('----------------------------------------  \n');

	pause
}

void normalization(void) {
	%% 13)- Normalization :

	ReceivedData = expandedData / max(expandedData) ;

	encodedData3  = S2P(ReceivedData,r,c) ;
	encodedData4 = bi2de(encodedData3 , 'left-msb' ) ;


	f10 = figure('position',[150 115 1100 500]) ;
	hold on
	grid on
	xlabel('Sample');
	ylabel('Amplitude')
	title( ' Audio Signal ' )
	plot( encodedData4 )
	%soundsc(ReceivedData,Fs)
	print( f10 , '-dbmp', '-noui', 'C:\Users\win7\Desktop\Results\finalSignal' );
	hold off

	pause
	close all

	fprintf('----------------------------------------------------------------------------------------------------\n');
	fprintf('                                             THANK YOU \n');
	fprintf('----------------------------------------------------------------------------------------------------\n');


}



*/






