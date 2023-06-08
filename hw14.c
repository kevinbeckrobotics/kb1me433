#include "nu32dip.h" // constants, functions for startup and UART
#include <math.h>

void startTimers(void);

int main(void) {
    char message[100];
    
    NU32DIP_Startup();
    
    startTimers();

    int t;
    while(1){
        t = _CP0_GET_COUNT();
        while(_CP0_GET_COUNT() < t + 48000000){
            
        }
        OC2RS = 11250;
        OC2R = 11250;
        t = _CP0_GET_COUNT();
        
        while(_CP0_GET_COUNT() < t + 48000000){
            
        }
        OC2RS = 3750;
        OC2R = 3750;
    }
}

void startTimers(){
    // Turn on Timer 2 with Output Compare 1
    TRISBbits.TRISB15 = 0;
    RPB15Rbits.RPB15R = 5;
    T2CONbits.TCKPS = 2;     // Timer2 prescaler N=4 (1:4)
    PR2 = 1999;              // period = (PR2+1) * N * (1/48000000) = 6 kHz
    TMR2 = 0;                // initial TMR2 count is 0
    OC1CONbits.OCM = 0b110;  // PWM mode without fault pin; other OC1CON bits are defaults
    OC1CONbits.OCTSEL = 0;   // Use timer2
    OC1RS = 500;             // duty cycle = OC1RS/(PR2+1) = 25%
    OC1R = 500;              // initialize before turning OC1 on; afterward it is read-only
    T2CONbits.ON = 1;        // turn on Timer2
    OC1CONbits.ON = 1;       // turn on OC1
    
    // Turn on Timer 3 with Output Compare 2
    TRISBbits.TRISB11 = 0;
    RPB11Rbits.RPB11R = 5;
    T3CONbits.TCKPS = 4;     // Timer2 prescaler N=16 (1:4)
    PR3 = 14999;              // period = (PR2+1) * N * (1/48000000) = 6 kHz
    TMR3 = 0;                // initial TMR3 count is 0
    OC2CONbits.OCM = 0b110;  // PWM mode without fault pin; other OC1CON bits are defaults
    OC2CONbits.OCTSEL = 1;   // Use timer3
    OC2RS = 3750;             // duty cycle = OC1RS/(PR2+1) = 25%
    OC2R = 3750;              // initialize before turning OC1 on; afterward it is read-only
    T3CONbits.ON = 1;        // turn on Timer2
    OC2CONbits.ON = 1;       // turn on OC1
    
    //TRISBbits.TRISB10 = 0b0101;
}
