//Armstrong number check : Display result on Keil UART terminal.

#include<lpc214x.h>
#include<stdlib.h>

void initPLL(){
	PLL0CON=0x01;
	PLL0CFG=0x24;
	PLL0FEED=0xAA;
	PLL0FEED=0x55;
	while(!(PLL0STAT & (1<<10)));
	PLL0CON=0x3;
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

void send(unsigned char ch){
	while((U0LSR & (1<<5))==0);
	U0THR=ch;
	
}
char get(){
	unsigned char c;
	while((U0LSR & (0x01<<0))==0);
	c=U0RBR;
	return c;
}

int Arms(int a){
	int r,sum,t=a;
	while(t!=0){
		r=t%10;
		sum+=(r*r*r);
		t=t/10;
	}
	if(sum==a){
		t=1;
	}
	else{
		t=0;
	}
	return t;
}

int main(){
	initPLL();
	initUART();
	int a;
	char strT[]="ARMSTRONG\n";
	char strF[]="NOT ARMSTRONG\n";
	char num[3],i=0;
	
	while(i!=3){
		num[i++]=get();
	}
	
	int y=0;
	while(num[y]!='\0'){
		send(num[y++]);
	}
	send('\n');
	
	a=atoi(num);
	
	int check=Arms(a);
	int l=0;
	if(check==1){
		while(strF[l]!='\0'){
		send(strT[l]);
			l++;
	}
}
	else{
		while(strF[l]!='\0'){
			send(strF[l]);
			l++;
	}
	}
	return 0;
}
	
