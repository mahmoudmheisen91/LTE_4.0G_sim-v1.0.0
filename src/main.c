/*-------------------------------------------------------------------------*/
/**
  @file     main.c
  @author   Mahmoud Mheisen
  @date     Jan 2015
  @version  $Revision: 1.0 $
  @brief    main file

  LTE Simulator Project: Undergraduate project for simulation the physical
  layer of fourth generation wirless communication standerd (LTE).
*/
/*--------------------------------------------------------------------------*/

// Including Libraries:
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sndfile.h>
#include <signal.h>
#include <time.h>
#include "LTE_err.h"
#include "gnuplot_i.h"
#include "resources.h"
#include "phy_layer.h"

int main(void) {

    // TODO:
    // S2P
    // P2S
    // encoder
    // decoder
    // bud database: makefile seperation error: use tap instead of four spaces

    // Software init:
    init();

    // Decleration:
    SNDFILE *sf1, *sf2;
    SF_INFO info;
    info.format = 0;

    // TODO: image
    // TODO: imshow
    printf("Enter 1 for image and 2 for voice.\n");

    // open sound file and read it:
    // TODO: know number of bits
    // TODO: sound matlab
    sf1 = sf_open("test_signal.wav", SFM_READ, &info);
    double data[info.frames];
    int length = sf_read_double(sf1, data, info.frames);
    int Fs = info.samplerate;
    sf_close(sf1);

    // print info to screen:
    printf("---------------------------------\n");
    printf("Length = %d sample\n", length );
    printf("Fs     = %d KHz   \n", Fs/1000 );
    printf("---------------------------------\n");
    //wait_for_ctrl_c();

    // plot original signal:
    //plot_y(data, length, "lines", "Sample", "Amplitude", "Audio Signal");

    // plot vs orignal time:
    //int i;
    //double time[length];
    //for(i = 0; i < length; i++) {
        //time[i] = i / Fs;
    //}
    //plot_xy(time, data, length, "lines", "Time", "Amplitute", "Test Signal");


    // ADC using 8 bits:
    double quantized_data[length];
    int encoded_data[length];
    double error_signal[length];
    int nbits = 8; // TODO as user/command input
    double snr_db = lte_adc(data, length, nbits, quantized_data, encoded_data, error_signal);

    int i;
    for(i = 0; i < length; i++) {
        //printf("%d ", encoded_data[i]);
    }

    //free(error_signal);
    //free(quantized_data);

    // print info to screen:
    printf("---------------------------------\n");
    printf("nlevels = %.1f level \n", pow(2, nbits));
    printf("SNR_dB  = %.4f dB   \n", snr_db);
    printf("---------------------------------\n");
    //wait_for_ctrl_c();

    // plot quantized signal:
    //plot_y(quantized_data, length, "lines", "Time", "Amplitute", "Quantized Signal");

    // plot error signal:
    // TODO: FFT plot:
    //plot_y(error_signal, length, "lines", "Time", "Amplitute", "Error Signal");

    // TODO:
    /*
    fprintf('-----------------------------------  \n');
    fprintf('Nbits before Encoding = %d  bit \n', length(enycrptedData));
    fprintf('Nbits after  Encoding = %d bit \n', length(turboData));
    fprintf('-----------------------------------  \n');
    */

    // Encoding:
    int gf   = 0b1101;
    int gr   = 0b1011;
    int f1   = 9;
    int f2   = 0;
    int turbo_data[2 * length];
    lte_turbo_encoder(encoded_data, length, gf, gr, f1, f2, turbo_data);
    // printf("here??\n");

    // Modulation:
    /*
    fprintf('---------------------------------------\n');
    M  = input('Enter Modulation order,       M  = ') ;
    M1 = input('Enter Modulation Type Number, M1 = ') ;
    fprintf('---------------------------------------\n');
    type2 = 'qam' ;
    [ MappingTable , trell ] = LTE_CONTROL( M , M1 , type2 , gf , gr ) ;

    title( ' QAM Cancelation ' )
    plot( MappingTable , ':' )
    [ MappedSymbols , LengthMatcher ] = LTE_MODULATION( turboData , M , MappingTable ) ;
    title( ' Mapped Symbols ' )
    plot( MappingTable , '--m' )
    */

    /*
      channel
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
      */

    /*
    %% 9)- Demodulation :
    ReceivedBits = LTE_DEMODULATION( ReceivedSignal ,  MappingTable , M , LengthMatcher ) ;
    title( ' Received Signal ' )
    plot( MappingTable , '--m' )
    error = sum( abs( xor( ReceivedBits , turboData ) ) ) ;
    BER   = error / length( turboData )  ;
    fprintf('-----------------------------  \n');
    fprintf('BER before Decoding = %2.4f \n', BER);
    fprintf('-----------------------------  \n');}
    */

    // Decoding:
    int decoded_data[length];
    lte_turbo_decoder(turbo_data, length, gf, gr, f1, f2, decoded_data);

    /*
    error = sum( abs( xor( decodedBits , enycrptedData ) ) ) ;
    BER2  = error / length( enycrptedData )  ;
    fprintf('-----------------------------  \n');
    fprintf('BER before Decoding = %2.4f \n', BER);
    fprintf('BER after  Decoding = %2.4f \n', BER2);
    fprintf('-----------------------------  \n');
    */

    // Normalization:
    static double final_data[184705];
    normalization(encoded_data, length, final_data);
    /*
        ReceivedData = expandedData / max(expandedData) ;
        encodedData3  = S2P(ReceivedData,r,c) ;
        encodedData4 = bi2de(encodedData3 , 'left-msb' ) ;
        title( ' Audio Signal ' )
        plot( encodedData4 )
    */

    // open new sound file and write to it:
    sf2 = sf_open("test_signal_2.wav", SFM_WRITE, &info);
    sf_write_double(sf2, quantized_data, length) ;
    sf_close(sf2);

    // print info to screen:
    printf("---------------------------------\n");
    printf("            THANK YOU\n");
    printf("---------------------------------\n");

    return SUCCESS;
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

*/
