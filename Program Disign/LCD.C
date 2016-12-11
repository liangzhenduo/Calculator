#include <reg52.h>
#include <string.h>
#include "def.h"

unsigned char x = 0xb8;	
unsigned char y = 0x40;

unsigned char reserve(unsigned char dat)
{
	unsigned char dat1 = 0;
	unsigned char x = 128;
	int i;
	for(i = 0; i < 8; i ++ ) {
		dat1 += (dat % 2) * x;
		x /= 2;
 	    dat /= 2;
	}
	return dat1;
}

void LcdWriteCmd(unsigned char cmd)
{
	EN = 0;
	RS = 0;
	RW = 0;
	EN = 1;
	DATA = reserve(cmd);
	EN = 0;
}

void LcdWriteDat(unsigned char dat)
{
	EN = 0;
	RS = 1;
	RW = 0;
	EN = 1;
	DATA = reserve(dat);
	EN = 0;
}

void clear()
{
	int i, j, k;
	for(k = 0; k < 8; k ++) {
		for(j = 0; j < 8; j ++) {
			for(i = 0; i < 8; i ++) {
				LcdWriteDat(0x00);
				if(y == 0x7f) {
					x = x + 1;
					LcdWriteCmd(x);
					y = 0x40;
					LcdWriteCmd(y);
				}
				y += 1;
			}
		}
	}
	x = 0xb8;
	LcdWriteCmd(x);
	y = 0x40;
	LcdWriteCmd(y);

}

void LcdInit()
{
	CS1 = 0;
	CS2 = 1;
	LIGHT = 1;
	
	LcdWriteCmd(0x3f);
	LcdWriteCmd(0xc0);
	LcdWriteCmd(0xb8);
	LcdWriteCmd(0x40);
	clear();
}

void LcdPutChar(unsigned int k)
{
	int i;
	for(i = 0; i < 8; i ++) {
		LcdWriteDat(Symbol[k][i]);
		if(y == 0x7f) {
			x = x + 1;
			LcdWriteCmd(x);
			y = 0x40;
			LcdWriteCmd(y);	
		}
		else
			y += 1;	
	}
}

void Output(unsigned char *num){
	unsigned int i;
	for(i=0;i<strlen(num);i++){
		switch(num[i]){
			case '0': LcdPutChar(0);  break;
			case '1': LcdPutChar(1);  break;
			case '2': LcdPutChar(2);  break;
			case '3': LcdPutChar(3);  break;
			case '4': LcdPutChar(4);  break;
			case '5': LcdPutChar(5);  break;
			case '6': LcdPutChar(6);  break;
			case '7': LcdPutChar(7);  break;
			case '8': LcdPutChar(8);  break;
			case '9': LcdPutChar(9);  break;
			case '.': LcdPutChar(10); break;
			case '=': LcdPutChar(11); break;
			case '+': LcdPutChar(12); break;
			case '-': LcdPutChar(13); break;
			case '*': LcdPutChar(14); break;
			case '/': LcdPutChar(15); break;
		}
	}
}

unsigned char code Symbol[][8]={
	0x00, 0x00, 0x3e, 0x51, 0x49, 0x45, 0x3e, 0x00, /*"0",0*/
	0x00, 0x00, 0x00, 0x42, 0x7f, 0x40, 0x00, 0x00, /*"1",1*/
	0x00, 0x00, 0x42, 0x61, 0x51, 0x49, 0x46, 0x00, /*"2",2*/
	0x00, 0x00, 0x21, 0x41, 0x45, 0x4b, 0x32, 0x00, /*"3",3*/
	0x00, 0x00, 0x18, 0x14, 0x12, 0x7f, 0x10, 0x00, /*"4",4*/
	0x00, 0x00, 0x27, 0x45, 0x45, 0x45, 0x39, 0x00, /*"5",5*/
	0x00, 0x00, 0x3c, 0x4a, 0x49, 0x49, 0x30, 0x00, /*"6",6*/
	0x00, 0x00, 0x01, 0x01, 0x71, 0x0d, 0x03, 0x00, /*"7",7*/
	0x00, 0x00, 0x36, 0x49, 0x49, 0x49, 0x36, 0x00, /*"8",8*/
	0x00, 0x00, 0x06, 0x49, 0x49, 0x29, 0x1e, 0x00, /*"9",9*/
	0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, /*".",a*/
	0x00, 0x00, 0x14, 0x14, 0x14, 0x14, 0x14, 0x00, /*"=",b*/
  	0x00, 0x00, 0x08, 0x08, 0x3e, 0x08, 0x08, 0x00, /*"+",c*/
  	0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, /*"-",d*/
  	0x00, 0x00, 0x22, 0x14, 0x08, 0x14, 0x22, 0x00, /*"*",e*/
  	0x00, 0x00, 0x08, 0x08, 0x2a, 0x08, 0x08, 0x00, /*"/",f*/
};

