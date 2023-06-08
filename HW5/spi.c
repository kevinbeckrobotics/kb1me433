#include <xc.h>

// initialize SPI1
void initSPI() {
    // Pin B14 has to be SCK1
    TRISBbits.TRISB14 = 0;
    RPB14Rbits.RPB14R = 3;
    
    // Turn of analog pins
    ANSELA = 0;
    ANSELB = 0;
    
    
    //...
    // Make an output pin for CS
    TRISBbits.TRISB0 = 0;
    
    //...
    //...
    // Set SDO1
    TRISBbits.TRISB11 = 0;
    RPB11Rbits.RPB11R = 3;
    //...
    // Set SDI1
    TRISBbits.TRISB1 = 1;  // Set pin B1 as an input
    RPB1Rbits.RPB1R = 4;   // Assign SDI1 functionality to pin B1
    
    SPI1CONbits.MSTEN = 1;  // Controller mode enabled

    //...

    // setup SPI1
    SPI1CON = 0; // turn off the spi module and reset it
    SPI1BUF; // clear the rx buffer by reading from it
    SPI1BRG = 1000; // 1000 for 24kHz, 1 for 12MHz; // baud rate to 10 MHz [SPI1BRG = (48000000/(2*desired))-1]
    SPI1STATbits.SPIROV = 0; // clear the overflow bit
    SPI1CONbits.CKE = 1; // data changes when clock goes from hi to lo (since CKP is 0)
    SPI1CONbits.MSTEN = 1; // master operation
    SPI1CONbits.MODE32 = 0;
    SPI1CONbits.MODE16 = 1;
    SPI1CONbits.ON = 1; // turn on spi 
}


// send a byte via spi and return the response
unsigned short spi_io(unsigned short o) {
  LATBbits.LATB0 = 0;
  SPI1BUF = o;
  while(!SPI1STATbits.SPIRBF) { // wait to receive the byte
    ;
  }
  LATBbits.LATB0 = 1;
  return SPI1BUF;
}