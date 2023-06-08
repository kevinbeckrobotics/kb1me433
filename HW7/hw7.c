#include "nu32dip.h" // constants, functions for startup and UART
#include "i2c_master_noint.h"
#include "mpu6050.h"
#include <stdio.h>

void blink(int, int); // blink the LEDs function

int main(void) {
    NU32DIP_Startup(); // cache on, interrupts on, LED/button init, UART init
    
    blink(5, 500);
    
    init_mpu6050();
	
	// char array for the raw data
    char data[7];
	// floats to store the data
    float stored[7];
	
    char message[100]; 
    
	// read whoami
    uint8_t address = whoami();
	// print whoami
    
	// if whoami is not 0x68, stuck in loop with LEDs on
    if(address != 0x68){
        blink(1, 5);
    }
    
	// wait to print until you get a newline
    char m_in[100];
    sprintf(m_in, "%x\r\n", address);
    NU32DIP_WriteUART1(m_in);

    while (1) {
		// use core timer for exactly 100Hz loop
        _CP0_SET_COUNT(0);
        //blink(1, 5);

        // read IMU
        burst_read_mpu6050(data);
		// convert data
        
        stored[0] = conv_xXL(data);
        stored[1] = conv_yXL(data);
        stored[2] = conv_zXL(data);
        stored[3] = conv_temp(data);
        stored[4] = conv_xG(data);
        stored[5] = conv_yG(data);
        stored[6] = conv_zG(data);

        // print out the data
        
        sprintf(message, "%f %f %f %f %f %f %f\r\n", stored[0], stored[1], stored[2], stored[3], stored[4], stored[5], stored[6]);
        NU32DIP_WriteUART1(message);

        while (_CP0_GET_COUNT() < 48000000 / 2 / 100) {
        }
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
