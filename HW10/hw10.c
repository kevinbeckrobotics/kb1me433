#include "nu32dip.h" // constants, functions for startup and UART
#include "ws2812b.h"
#include <math.h>

//void generateRainbow(int);

void blink(int, int);

int main(void) {
    NU32DIP_Startup();
    
    //blink(5, 500);
    
    ws2812b_setup();
    
    wsColor active = HSBtoRGB(120, 1, 1);
    
    wsColor col_arr[5];
    
    col_arr[0] = active;
    
    col_arr[1] = active;
    
    col_arr[2] = active;
    
    col_arr[3] = active;
    
    col_arr[4] = active;
    
    unsigned int t;
    
    int i = 0; int j = 0;
    
    char message[100];
    
    int hue4 = 0;
    
    for(i = 0; i < 14400; i++){
        hue4 = i % 1440;
        active = HSBtoRGB(0.25 * (double)hue4, 1, 1);
        for(j = 0; j < 5; j++){
            col_arr[j] = active;
        }
        ws2812b_setColor(col_arr, 5);
        sprintf(message, "%f\r\n", 0.5 * i);
        NU32DIP_WriteUART1(message);
        t = _CP0_GET_COUNT(); // should really check for overflow here
        while (_CP0_GET_COUNT() < t + 1200000) {
        }
    }
}

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
