/**
 * Chip:     dsPIC30f401230I/SP
 * IDE:      MPLABx
 * Complier: xc16
 * File:     playSimon.c
 * Authors:  David Myers, Lee Napier
 * Date:     12Nov2014
 *
 * Dependent on:
 *      simonFunctions.c
 *      ADC_init.c
 *      simonFunctions.h
 *      ADC_init.h
 *
 * Datasheet, family reference manual, and excel files including the ADC
 * configuration and flow chart can be found on the robot computer desktop
 * in the folder SimonShenanagins.
 */

/*Defines & Includes*/
#define FCY 7370000UL                                                           //Defining throughput for delay function
#include <stdio.h>
#include <stdlib.h>
#include <p30F4012.h>
#include <libpic30.h>
#include "ADC_init.h"
#include "simonFunctions.h"

/*Clock setup and Chip Initializaiton*/
  _FOSC(CSW_FSCM_OFF & FRC_PLL4);                                               //Run project using internal rc oscillator
                                                                                //routed via the 4x multiplier mode.
                                                                                //7.37MHz will derive a throughput of 7.37e+6*4/4
                                                                                //= 7.37 MIPS(Fcy), 136 nanoseconds instruction
                                                                                //cycle time(Tcy)

  _FWDT(WDT_OFF);                                                               //Turn off the Watch-Dog Timer

  _FBORPOR(MCLR_EN & PWRT_16);                                                  //Enable MCLR reset pin, set the power-up
                                                                                //timers to 16ms

  _FGS(CODE_PROT_OFF);                                                          //Disable Code Protection

int main(void) {
	
    ADC_init();                                                                 //ADC Setup

    /*Configure output pins*/
    TRISE = 0;                                                                  //Port E is set to output
                                                                                //RE0 -- Start Button
                                                                                //RE1 -- Red Button
                                                                                //RE2 -- Blue Button
                                                                                //RE3 -- Yellow Button
                                                                                //RE4 -- Green Button
                                                                                //RE5 -- empty
    PORTE = 0;                                                                  //All pins initially low

    /*Declare and Initialize Variables*/
    int buttonArray[20];                                                        //Array to hold button values
    int roundCounter;                                                           //Tracks the rounds
    int buttonCounter;                                                          //Tracks the illuminated buttons
    int actuatorCounter;                                                        //Tracks the # of button presses 
    int lastRead;                                                               //Button that was detected on the last 
                                                                                //sensor read
    int playGame = 1;                                                           //If zero stop playing and set timeout 
                                                                                //pin high
    /*Start Game Operation*/
    calibrateSensor();                                                          //Get initial values

    /*Rounds*/
    for(roundCounter = 0; playGame == 1; roundCounter++) {

        /*Watch*/
        for(buttonCounter = 0; buttonCounter <= roundCounter; buttonCounter++) {
            lastRead = buttonState();                                           //Get new sensor reading
            while (lastRead != 0) lastRead = buttonState();                     //Wait for light to go off

            if (roundCounter == 0){                                             //If first go press start
                press(0);
            } //End if: Test for first round

            lastRead = buttonState();                                           //Get new sensor reading
            while (lastRead == 0) lastRead = buttonState();                     //Wait for a color to appear
        } // End for: Watch

        buttonArray[roundCounter] = lastRead;                                   //Store last read in roundCounter
        __delay_ms(5000);                                                       //Pause before playing

        //**Play**
        for(actuatorCounter = 0; actuatorCounter<= roundCounter;
            actuatorCounter++){
            lastRead = buttonState();                                           //Get new sensor reading
            while (lastRead != 0) lastRead = buttonState();                     //Wait for light to go off
            press(buttonArray[actuatorCounter]);                                //Push button
            if (actuatorCounter != roundCounter) __delay_ms(1000);              //If not the last button pause
        } //End for: Play

    } //End for: Round

    return (EXIT_SUCCESS);
} // End main