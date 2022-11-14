
#include <lpc214x.h>

void init_uart0(void){

	PINSEL0 = 0x5;	//For Tx and Rx 
	U0LCR = 0x83;		//8-data bits 1 stop bit, disable parity enable dlab
	U0DLL = 0x87;		//baud rate of 9600
	U0DLM = 0x1;
	U0LCR = 0x03;		//clear dlab
}

void transmit_char_uart0(unsigned char c){

	while((U0LSR & (1<<5))==0);
	U0THR = c;
}
	
char receive_char_uart0(void){
	
	unsigned char temp_rec_var;
	while((U0LSR & (1<<0))==0);         //Checking RDR bit
  temp_rec_var = U0RBR;
  return temp_rec_var;
}
void init_pll(void)
{
  PLL0CON = 0x01;
  PLL0CFG = 0x24;
  PLL0FEED = 0xAA;
  PLL0FEED = 0x55;
  while(!(PLL0STAT & (1<<10)));
  PLL0CON = 0x03;
  PLL0FEED = 0xAA;
  PLL0FEED = 0x55;
	VPBDIV = 0x01;
}
