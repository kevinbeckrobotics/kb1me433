#include "nu32dip.h" // constants, functions for startup and UART
#include "uart2.h"
#include "i2c_master_noint.h"
#include "font.h"
#include "ssd1306.h"
#include "ws2812b.h"
#include "mpu6050.h"

void blink(int, int); // blink the LEDs function

void startKart(void);

void startTimers(void);

void drawChar(char, char, char); // blink the LEDs function

void drawString(char *, char, char);

void moveServo(float);

void changeNeoColor(float, float, float);

void printGyro(void);

float getCom(void);

int main(void) {
  int com = 0;  
  
  char message[100];
    
  char message2[100];
  
  NU32DIP_Startup(); // cache on, interrupts on, LED/button init, UART init
  
  UART2_Startup();
  
  startTimers();
  //changeNeoColor(0, 1, 1);
  while (1) {
   if(get_uart2_flag()){
        set_uart2_flag(0); // set the flag to 0 to be ready for the next message
        com = get_uart2_value();
        sprintf(message2,"%d\r\n",com);
        NU32DIP_WriteUART1(message2);
    OC2RS = 1200 + ((30 - com) * 12) - 1;
    OC2R = 1200 + ((30 - com) * 12) - 1;
    sprintf(message, "%d\r\n", OC2RS);
    NU32DIP_WriteUART1(message);
    OC3RS = 1200 - ((30 - com) * 12) - 1;
    OC3R = 1200 - ((30 - com) * 12) - 1;
    sprintf(message, "%d\r\n", OC3RS);
    NU32DIP_WriteUART1(message);
    
    if(com < 15 || com > 45){
        //changeNeoColor(240, 1, 1);
        moveServo(90);
    }
    else{
        //changeNeoColor(0, 1, 1);
    }
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
		
void startTimers(){
    // Turn on Timer 2 with Output Compare 1
    ANSELB = 0b0000;
    TRISBbits.TRISB15 = 0;
    RPB15Rbits.RPB15R = 5;
    T2CONbits.TCKPS = 2;     // Timer2 prescaler N=4 (1:4)
    PR2 = 1999;              // period = (PR2+1) * N * (1/48000000) = 6 kHz
    TMR2 = 0;                // initial TMR2 count is 0
    OC1CONbits.OCM = 0b110;  // PWM mode without fault pin; other OC1CON bits are defaults
    OC1CONbits.OCTSEL = 0;   // Use timer2
    OC1RS = 0;             // duty cycle = OC1RS/(PR2+1) = 25%
    OC1R = 0;              // initialize before turning OC1 on; afterward it is read-only
    T2CONbits.ON = 1;        // turn on Timer2
    OC1CONbits.ON = 1;       // turn on OC1
    
    // Turn on Timer 3 with Output Compare 2
    TRISBbits.TRISB11 = 0;
    RPB11Rbits.RPB11R = 5;
    T3CONbits.TCKPS = 0;     // Timer2 prescaler N=16 (1:4)
    PR3 = 2399;              // period = (PR2+1) * N * (1/48000000) = 6 kHz
    TMR3 = 0;                // initial TMR3 count is 0
    OC2CONbits.OCM = 0b110;  // PWM mode without fault pin; other OC1CON bits are defaults
    OC2CONbits.OCTSEL = 1;   // Use timer3
    OC2RS = 0;             // duty cycle = OC1RS/(PR2+1) = 25%
    OC2R = 0;              // initialize before turning OC1 on; afterward it is read-only
    T3CONbits.ON = 1;        // turn on Timer2
    OC2CONbits.ON = 1;       // turn on OC1
    // set pin B13 to output
    TRISBbits.TRISB13 = 0;
    LATBbits.LATB13 = 0;
    
    // Turn on Timer 3 with Output Compare 2
    TRISBbits.TRISB10 = 0;
    RPB10Rbits.RPB10R = 5;
    T3CONbits.TCKPS = 0;     // Timer2 prescaler N=16 (1:4)
    PR4 = 2399;              // period = (PR2+1) * N * (1/48000000) = 6 kHz
    TMR4 = 0;                // initial TMR3 count is 0
    OC3CONbits.OCM = 0b110;  // PWM mode without fault pin; other OC1CON bits are defaults
    OC3CONbits.OCTSEL = 0;   // Use timer3
    OC3RS = 0;             // duty cycle = OC1RS/(PR2+1) = 25%
    OC3R = 0;              // initialize before turning OC1 on; afterward it is read-only
    T4CONbits.ON = 1;        // turn on Timer2
    OC3CONbits.ON = 1;       // turn on OC1
    TRISBbits.TRISB12 = 0;
    LATBbits.LATB12 = 1;
}

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

void moveServo(float angle){
    int t;
    float ocrs_float = 250 * angle / 3;
    OC2RS = (int)ocrs_float;
    OC2R = (int)ocrs_float;
    t = _CP0_GET_COUNT();
    while(_CP0_GET_COUNT() < t + 4800000){        
    }
}

void changeNeoColor(float hue, float sat, float bright){
    int t = 0;
    wsColor active = HSBtoRGB(120, 1, 1);
    wsColor col_arr[5];
    int i = 0;
    for(i = 0; i < 5; i++){
        col_arr[i] = active;
    }
    ws2812b_setColor(col_arr, 5);
    t = _CP0_GET_COUNT(); // should really check for overflow here
        while (_CP0_GET_COUNT() < t + 1200000) {
        }
}

void printGyro(){
    char message[100]; 
    
    char data[7];
	// floats to store the data
    float stored[7];
	    
	// read whoami
    uint8_t address = whoami();
	// print whoami
    
	// if whoami is not 0x68, stuck in loop with LEDs on
    if(address != 0x68){
        blink(1, 5);
    }
    
	// wait to print until you get a newline
    char m_in[100];
    //sprintf(m_in, "%x\r\n", address);
    NU32DIP_WriteUART1(m_in);

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
        
        sprintf(message, "%f %f %f %f\r\n", stored[0], stored[1], stored[2], stored[3]);
        drawString(message, 0, 0);

        while (_CP0_GET_COUNT() < 48000000 / 2 / 100) {
        }
}

float getCom(){
   char message2[100];
   float com = 0;
   if(get_uart2_flag()){
        set_uart2_flag(0); // set the flag to 0 to be ready for the next message
        com = get_uart2_value();
        sprintf(message2,"%f\r\n",com);
        NU32DIP_WriteUART1(message2);
    }
   return com;
}

void startKart(){
    NU32DIP_Startup();
    
    TRISBbits.TRISB9 = 1;  // Set pin B9 (SDA1) as an input
    TRISBbits.TRISB8 = 1;  // Set pin B8 (SCL1) as an input
    RPB9Rbits.RPB9R = 0b0110;  // Assign SDA1 functionality to pin B9
    RPB8Rbits.RPB8R = 0b0110;  // Assign SCL1 functionality to pin B8
    
    startTimers();
    
    init_mpu6050();
    
    i2c_master_setup();
    
    ssd1306_setup();
    
    ws2812b_setup();
    
    UART2_Startup();
}
