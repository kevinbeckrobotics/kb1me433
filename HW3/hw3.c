#include "nu32dip.h" // constants, functions for startup and UART
#include <stdio.h>
#include <math.h>

void blink(int, int); // blink the LEDs function

int main(void) {
  char message[100];
  
  char active_text[100];
  
  char active_int = 0;
  
  NU32DIP_Startup(); // cache on, interrupts on, LED/button init, UART init
  NU32DIP_WriteUART1("Enter 'e' if you want to encode and 'd' if you want to decode.\r\n\0");
  NU32DIP_WriteUART1("Press the USER button to send a sine wave.\r\n\0");
  NU32DIP_ReadUART1(message, 100); // wait here until get message from computer
  if(!NU32DIP_USER){
      int i = 0;
      float sine_val = 0;
      for(i = 0; i < 100; i++){
          sine_val = 1.65 * sin(i * 6.283/100) + 1.65;
          NU32DIP_WriteUART1("%f\r\n", sine_val);
      }
  }
  else{
      if(message[0] == 'd'){
    while(1){
        int i = 0;
        for(i = 0; i < 100; i++){
          NU32DIP_ReadUART1(message, 100); // wait here until get message from computer
          sscanf(message, "%d", &active_int);
          sprintf(message, "%c", active_int);
          if(active_int == '\0'){
                NU32DIP_WriteUART1("\r\n"); // carriage return and newline
                break;
            }
          NU32DIP_WriteUART1(message); // send message back
        }
        _CP0_SET_COUNT(0);
      }
  }
  else if (message[0] == 'e'){
      while(1){
        int i = 0;
        NU32DIP_ReadUART1(message, 100); // wait here until get message from computer
        for(i = 0; i < 100; i++){
            if(message[i] != '\0'){
                sprintf(message, "%d\r\n", message[i]);
                NU32DIP_WriteUART1(message);
            }
            else{
                break;
            }
        }
        sprintf(message, "%d\r\n", active_int);
        NU32DIP_WriteUART1(message); // send message back
        _CP0_SET_COUNT(0);
      }
  }
  else{
      NU32DIP_WriteUART1("Invalid input.\r\n");
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
		
