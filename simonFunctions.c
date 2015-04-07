/**
 * Chip:     dsPIC30f401230I/SP
 * IDE:      MPLABx
 * Complier: xc16
 * File:     simonFunctions.c
 * Author:   Lee Napier
 * Date:     12Nov2014
 *
 * This file contains several helper functions to assist playSimon.c
 * Since I am the only one writing to this microchip, I used GLOBALS.
 *
 * Datasheet, family reference manual, and excel files including the ADC
 * configuration and flow chart can be found on the robot computer desktop
 * in the folder SimonShenanagins.
 */
#define FCY 7370000UL
#include <p30F4012.h>
#include <libpic30.h>

/*Globals*/
const int BUTTON_PRESS_MS = 100;                                                //Amount of time the button is pressed
const int START_PRESS_MS = 100;                                                 //Amount of time the start button is pressed
const int VARIATION = 100;                                                      //ADC level change required to detect a button is on.
const int NUM_SAMPLES = 30;                                                     //Number of samples per button
int redValue;                                                                   //ADC level of representive button
int blueValue;
int yellowValue;
int greenValue;
int rStartValue;                                                                //Initial dark value of sensors
int bStartValue;
int yStartValue;
int gStartValue;

/**
 * Reads the photocell voltage divider. It takes as many samples as defined by
 * user above (NUM_SAMPLES) and assigns the averaged value to the appropriate
 * color.
 */
void sensorRead(void) {
    
    int tempArray[NUM_SAMPLES * 4];                                             //Array to store buffer values
    int sampleCounter = 1;                                                      //Count samples
    int indexCounter = 0;                                                       //Track tempArray index
    redValue = 0;
    blueValue = 0;
    yellowValue = 0;
    greenValue = 0;

    /*Get ADC Values*/
    while(sampleCounter <= NUM_SAMPLES) {                                       //Get the number of samples
        ADCON1bits.SAMP = 1;                                                    //Start Sampling
        __delay_us(1);
        ADCON1bits.SAMP = 0;                                                    //End sampling and start conversion
        while(!ADCON1bits.DONE);                                                //Wait for conversion to finish
        tempArray[indexCounter] = (int)ADCBUF0; indexCounter++;                 //Move samples out of buffers
        tempArray[indexCounter] = (int)ADCBUF1; indexCounter++;
        tempArray[indexCounter] = (int)ADCBUF2; indexCounter++;
        tempArray[indexCounter] = (int)ADCBUF3; indexCounter++;
        sampleCounter++;
    } // End while: Sample/convert complete

    /*Calculate Averages*/
    int stopForLoop = (NUM_SAMPLES * 4) - 4;
    int i;
    for(i = 0; i <= stopForLoop; i += 4) {
        redValue += tempArray[i];                                               //Sum red values
        blueValue += tempArray[i + 1];                                          //Sum blue values
        yellowValue += tempArray[i + 2];                                        //Sum yellow values
        greenValue += tempArray[i + 3];                                         //Sum green values
    } // End for: loop thru array

    redValue /= NUM_SAMPLES;                                                    //Average values
    blueValue /= NUM_SAMPLES;
    yellowValue /= NUM_SAMPLES;
    greenValue /= NUM_SAMPLES;
} // End sensorRead()

/**
 * Determines if a button is 'on' or if all buttons are 'off'.
 * @return int value representing which button is 'on' or if all buttons are 'off'
 */
int buttonState(void) {
    sensorRead();                                                               //Get new button values
    if (redValue  >  rStartValue + VARIATION) { return 1;                       //Return appropriate value
    } else if (blueValue > bStartValue +  VARIATION) { return 2;
    } else if (yellowValue > yStartValue + VARIATION) { return 3;
    } else if (greenValue > gStartValue + VARIATION) { return 4;
    } else { return 0;
    } // End else/if: Determine if a button is on

} // End getButton()

/**
 * Presses, holds, and releases a button.
 * @param button integer value representing a button
 */
void press(int button) {

    if (button == 0) {
        PORTEbits.RE0 = 1;                                                      //Press start button
        __delay_ms(START_PRESS_MS);                                             //Hold startbutton
        PORTEbits.RE0 = 0;                                                      //Release start button
    } else if (button == 1) {
        PORTEbits.RE1 = 1;                                                      //Press red button
        __delay_ms(BUTTON_PRESS_MS);                                            //Hold red button
        PORTEbits.RE1 = 0;                                                      //Release red button
    } else if (button == 2) {
        PORTEbits.RE2 = 1;                                                      //Press blue button
        __delay_ms(BUTTON_PRESS_MS);                                            //Hold blue button
        PORTEbits.RE2 = 0;                                                      //Release blue button
    } else if (button == 3) {
        PORTEbits.RE3 = 1;                                                      //Press yellow button
        __delay_ms(BUTTON_PRESS_MS);                                            //Hold yellow button
        PORTEbits.RE3 = 0;                                                      //Release yellow button
    } else if (button == 4) {
        PORTEbits.RE4 = 1;                                                      //Press green button
        __delay_ms(BUTTON_PRESS_MS);                                            //Hold green button
        PORTEbits.RE4 = 0;                                                      //Release green button
    } // End else/if: press defined button

} // End press()

/**
 * Gets dark values of the sensors before the game begins.
 */
void calibrateSensor(void) {
    sensorRead();                                                               //Get new button values
    rStartValue = redValue;                                                     //These are acquired before the start button
    bStartValue = blueValue;                                                    //is pressed
    yStartValue = yellowValue;
    gStartValue = greenValue;
} // End calibrateSensor()
