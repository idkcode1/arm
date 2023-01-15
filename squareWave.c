 #include<LPC214x.h>
 
 void delay(int a){
 while(--a);
 }
 
 int main(){
	
	//square wave
	while(1){
	  
    IO1DIR=0x00000000;
	  IO0DIR=0xfffF0000;
	  
    if((IOPIN1 & (1<<16))==0){
		  IOSET0=0xFFFF0000;
		  delay(10);
		  IOCLR0=0xFFFFFFFF;
		  delay(10);		
	  }
	  
    else{
		
      IOCLR0=0xFFFFFFFF;
		  delay(5);
		}
	}
}
