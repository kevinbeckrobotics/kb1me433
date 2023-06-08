#include "nu32dip.h" // constants, functions for startup and UART
#include "spi.h"
#include <math.h>

unsigned short sine(int);

unsigned short tri(int);

void blink(int, int);

int main(void) {
    char message[100];
    
    NU32DIP_Startup();
    initSPI();
    //blink(5, 500);
    int i = 0;
    while(1){
        spi_io(sine(i));
        spi_io(tri(i));
        sprintf(message, "%d\r\n", (sine(i) - 0b0111000000000000)/4);
        NU32DIP_WriteUART1(message);
        int t = _CP0_GET_COUNT(); // should really check for overflow here
		// the core timer ticks at half the SYSCLK, so 24000000 times per second
		// so each millisecond is 24000 ticks
		// wait half in each delay
		while(_CP0_GET_COUNT() < t + 24000){}
        i++;
    }
}

unsigned short sine(int i){
    float sine_float = sin(6.283 * (float)i / 150);
    float result_float = (511 * sine_float) + 512;
    unsigned short sine_result = (unsigned short) result_float << 2;
    return sine_result | 0b0111000000000000;
}

unsigned short tri(int i){
    unsigned short index = i % 300;
    float data = 0.0;
    if(index <= 150){
        data = 1023 * index / 150;
    }
    else{
        data = 1023 * (300 - index) / 150;
    }
    return ((unsigned short)data << 2) | 0b1111000000000000;
}

void blink(int iterations, int time_ms){
	int i;
	unsigned int t;
	for (i=0; i< iterations; i++){
		NU32DIP_GREEN = 0; // on
		NU32DIP_YELLOW = 1; // off
		t = _CP0_GET_COUNT(); // should really check for overflow here
		// the core timer ticks at half the SYSCLK, so 24000000 times per second
		// so each millisecond is 24000 ticks
		// wait half in each delay
		while(_CP0_GET_COUNT() < t + 12000*time_ms){}
		
		NU32DIP_GREEN = 1; // off
		NU32DIP_YELLOW = 0; // on
		t = _CP0_GET_COUNT(); // should really check for overflow here
		while(_CP0_GET_COUNT() < t + 12000*time_ms){}
	}
}
