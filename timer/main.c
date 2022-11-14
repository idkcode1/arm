#include "pll.h"
#include "timer0.h"
#include <LPC214x.h>
int main(){
	IO0DIR = 0xFFFFFFFF;
	init_pll();
	IO0SET = 0xFFFFFFFF;
	delay_milliseconds(1000);
	IO0CLR = 0xFFFFFFFF;
	delay_milliseconds(1000);
}