#include <stdio.h>
#include <stdlib.h>
#include <p30F4012.h>
#include <libpic30.h>
void press(int button, const int MS_DELAY) {
    if (button == 0) {
        PORTEbits.RE0 = 1;                                                      //Press start button
        __delay_ms(MS_DELAY);                                                   //Hold start button
        PORTEbits.RE0 = 0;                                                      //Release start button
    } else if (button == 1) {
        PORTEbits.RE1 = 1;                                                      //Press red button
        __delay_ms(MS_DELAY);                                                   //Hold red button
        PORTEbits.RE1 = 0;                                                      //Release red button
    } else if (button == 2) {
        PORTEbits.RE2 = 1;                                                      //Press blue button
        __delay_ms(MS_DELAY);                                                   //Hold blue button
        PORTEbits.RE2 = 0;                                                      //Release blue button
    } else if (button == 3) {
        PORTEbits.RE3 = 1;                                                      //Press yellow button
        __delay_ms(MS_DELAY);                                                   //Hold yellow button
        PORTEbits.RE3 = 0;                                                      //Release yellow button
    } else if (button == 4) {
        PORTEbits.RE4 = 1;                                                      //Press green button
        __delay_ms(MS_DELAY);                                                   //Hold green button
        PORTEbits.RE4 = 0;                                                      //Release green button
    } // End else/if: press defined button

} // End press()
