#include<lpc213x.h>
#include<stdlib.h>
#include<stdint.h>
#include<stdio.h>

void delay_ms(int j);
void LCD_CMD(char command);
void LCD_INIT(void);
void LCD_CHAR(char msg);
void LCD_STRING(char* msg);

int main(void)
{
	uint8_t j;
	j=0;
	char val_j[3];
	LCD_INIT();
	
	LCD_STRING("GOD LOVES U");
	LCD_CMD(0xC0);
	LCD_STRING("time remaining:");
	for(j=0;j<10;j++)
	{
		
		sprintf(val_j,"%d",j);
		LCD_STRING(val_j);
		delay_ms(100);
		LCD_CMD(0xCC);
	}
	return 0;
}


void delay_ms(int j)
{
	int i,x;
	for(i=0;i<j;i++)
	{
		for(x=0;x<3000;x++);
	}
}

// Initializing the LCD
void LCD_INIT(void)
{
	IO0DIR = 0x000007FF;//P0.0-P0.12 to LCD
	LCD_CMD(0x30);
	LCD_CMD(0x0C);
	LCD_CMD(0x06);
	LCD_CMD(0x01);
	LCD_CMD(0x80);

}
//Command Write Function
void LCD_CMD(char command)
{
	IO0PIN = ( (IO0PIN & 0xFFFFFF00) | (command<<8));
	IO0SET = 0x00000040;
	IO0CLR = 0x00000030;
	delay_ms(2);
	IO0CLR = 0x00000040;
	delay_ms(5);

}

//DATA write function(single character)
void LCD_CHAR(char msg)
{
	IO0PIN = ( ( IO0PIN & 0xFFFFFF00)|(msg<<8));
	IO0SET = 0x00000050;
	IO0CLR = 0x00000040;
	delay_ms(2);
	IO0CLR = 0x00000040;
	delay_ms(5);
}

//DATA write for multiple characters
void LCD_STRING(char* msg)
{
	uint8_t i=0;
	while(msg[i]!=0)
	{
		LCD_CHAR(msg[i]);
		i++;
	}
}	

