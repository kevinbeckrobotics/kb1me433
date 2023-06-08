#include "nu32dip.h" // constants, functions for startup and UART
#include "uart2.h"

void blink(int, int); // blink the LEDs function

int main(void) {
  char message2[100];
  
  NU32DIP_Startup(); // cache on, interrupts on, LED/button init, UART init
  
  UART2_Startup();
  
  float com = 0;
  while (1) {
   if(get_uart2_flag()){
        set_uart2_flag(0); // set the flag to 0 to be ready for the next message
        com = get_uart2_value();
        sprintf(message2,"%f\r\n",com);
        NU32DIP_WriteUART1(message2);
    }
  }
}

// blink the LEDs
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
		
