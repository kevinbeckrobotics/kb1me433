#include "nu32dip.h" // constants, functions for startup and UART
#include "i2c_master_noint.h"
#include "mpu6050.h"
#include "ssd1306.h"
#include "font.h"
#include <stdio.h>

void blink(int, int); // blink the LEDs function

void drawChar(char, char, char); // blink the LEDs function

void drawString(char *, char, char);

int main(void) {
    char message[100];
    
    NU32DIP_Startup();
    
    TRISBbits.TRISB9 = 1;  // Set pin B9 (SDA1) as an input
    TRISBbits.TRISB8 = 1;  // Set pin B8 (SCL1) as an input
    RPB9Rbits.RPB9R = 0b0110;  // Assign SDA1 functionality to pin B9
    RPB8Rbits.RPB8R = 0b0110;  // Assign SCL1 functionality to pin B8
    
    i2c_master_setup();
    ssd1306_setup();
    
    blink(2, 500);
    
    ssd1306_drawPixel(0, 0, 0xff);
    
    ssd1306_update();
    
    ssd1306_clear();
    while(1){
        NU32DIP_ReadUART1(message, 100); // wait here until get message from computer
        ssd1306_clear();
        drawString(message, 0, 0);
        NU32DIP_WriteUART1(message);
        ssd1306_update();
    }
}

// blink the LEDs
void drawChar(char letter, char x, char y){
    int j = 0;
    int i = 0;
    char col;
    for(j = 0; j < 5; j++){
        col = ASCII[letter - 0x20][j];
        for(i = 0; i < 8; i++){
            ssd1306_drawPixel(x + j, y + i, (col >> i)&0b1);
        }
    }
}

void drawString(char * m, char x, char y){
    int k = 0;
    int col = 0;
    while(m[k] != 0){
        col = k / 25;
        drawChar(m[k], x + (5 * (k % 25)), y + (8 * col));
        k++;
    }
}

// blink the LEDs
void blink(int iterations, int time_ms) {
    int i;
    unsigned int t;
    for (i = 0; i < iterations; i++) {
        NU32DIP_GREEN = 0; // on
        NU32DIP_YELLOW = 1; // off
        t = _CP0_GET_COUNT(); // should really check for overflow here
        // the core timer ticks at half the SYSCLK, so 24000000 times per second
        // so each millisecond is 24000 ticks
        // wait half in each delay
        while (_CP0_GET_COUNT() < t + 12000 * time_ms) {
        }

        NU32DIP_GREEN = 1; // off
        NU32DIP_YELLOW = 0; // on
        t = _CP0_GET_COUNT(); // should really check for overflow here
        while (_CP0_GET_COUNT() < t + 12000 * time_ms) {
        }
    }
}
