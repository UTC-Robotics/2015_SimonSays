/**
 * Chip:     dsPIC30f401230I/SP
 * IDE:      MPLABx
 * Complier: xc16
 * File:     ADC_init.c
 * Author:   Lee Napier
 * Date:     12Nov2014
 *
 * Initializes the ADC.
 *
 * Datasheet, family reference manual, and excel files including the ADC
 * configuration and flow chart can be found on the robot computer desktop
 * in the folder SimonShenanagins.
 */
#include <p30F4012.h>
void ADC_init(void) {
    ADCON1bits.ADON = 0;                                                        //Disable ADC

   /*ADCON1 Register*/
    ADCON1 = 0;                                                                 //Clear ADCON1
    ADCON1bits.FORM = 0;                                                        //Unsigned Integer
    ADCON1bits.SSRC = 0;                                                        //Clearing sample bit ends sampling and starts conversion
    ADCON1bits.SIMSAM = 1;                                                      //Sample CH0, CH1, CH2, CH3 simultaneously
                                                                                //when CHPS = 1x
    ADCON1bits.ASAM = 0;                                                        //Sampling begins when SAMP bit is set

  /*ADCON2 Register*/
    ADCON2 = 0;                                                                 //Clear ADCON1
    ADCON2bits.VCFG = 0;                                                        //AVdd & AVss are voltage ref config
    ADCON2bits.CHPS = 2;                                                        //Convert CH0, CH1, CH2, CH3 sequentially
    ADCON2bits.BUFM = 0;                                                        //One 16-word buffer ADCBUF(15...0)
    ADCON2bits.ALTS = 0;                                                        //Always uses MUX A input multiplexer
                                                                                //settings

  /*ADCON3 Register*/
    ADCON3 = 0;
    ADCON3bits.ADRC = 0;                                                        //Clock derived from system clock
    ADCON3bits.ADCS = 1;                                                        //Tad = Tcy*(ADCS + 1)/2 = 136 nanoseconds
                                                                                
  /*ADCHS Register*/
    ADCHS = 0;
    ADCHSbits.CH123NA = 0;                                                      //CH 1, 2 ,3 (-) input is Vref(-)
    ADCHSbits.CH123SA = 0;                                                      //CH1 (+) input AN0, CH2:AN1, CH3:AN2
    ADCHSbits.CH0NA = 0;                                                        //CH0 (-) input is Vref(-)
    ADCHSbits.CH0SA = 3;                                                        //CH0 (+) input is AN3

  /*ADCSSL Register*/
    ADCSSL = 0x0000;                                                            //Channel scanning is disabled

  /*ADPCFG Register*/
    ADPCFG = 0xFFF0;                                                            //Set channels AN0, AN1, AN2, & AN3 (4 photoresistor reads)
                                                                                //as analog input and the rest to digital

    ADCON1bits.ADON = 1;                                                        //Activate ADC
}
