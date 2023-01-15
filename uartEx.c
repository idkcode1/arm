// UART Communication Example
#include<LPC214x.h>

void delay(int a){
	for(int i=0;i<a;i++);
	}

void initPLL(){
	PLL0CON=0x01;
	PLL0CFG=0x24;
	PLL0FEED=0xAA;
	PLL0FEED=0x55;
	while(!(PLL0STAT&(1<<10)));
	PLL0CON=0x03;
	PLL0FEED=0xAA;
	PLL0FEED=0x55;
	VPBDIV=0x01;
	}
	
void initUART(){
	PINSEL0=0x5;
	U0LCR=0x83;
	U0DLL=0x87;
	U0DLM=0x01;
	U0LCR=0x03;
}

/*void send_UART(unsigned char mydata){
	U0THR=mydata;
	while((U0LSR & (1<<5))==0);
}*/
void send_UART(char ch){
	while((U0LSR & (1<<5))==0);
	U0THR=ch;
}

char rev_UART(){
	unsigned char mydata;
	while((U0LSR&(1<<0))==0);
	mydata=	U0RBR;
	return mydata;
}
	
int main(){
		char ch[]="Hi, whats your name?\n";
		char ch1[]="Hello,\n";
		char str[10];
		char k=0;
		initPLL();
		initUART();
		do{
			send_UART(ch[k++]);
		}while(ch[k]!='\0');
		k=0;
		while(k<10 && str[k]!=13){
			str[k++]=rev_UART();
		}
		k=0;
		while(ch1[k]!='\0'){
			send_UART(ch1[k++]);
		}
		k=0;
		do{
			send_UART(str[k++]);
		}while(k<10);
		send_UART('\n');
	return 0;
		
}
