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
	
	//LcdWriteCmd(0xfc);
	LcdWriteCmd(0x3f);
	LcdWriteCmd(0xc0);
	LcdWriteCmd(0xb8);
	LcdWriteCmd(0x40);
	clear();
	//LcdWriteCmd(0xff);
}

void LcdPutChar(unsigned char *dat)
{
	int i;
	for(i = 0; i < 8; i ++) {
		LcdWriteDat(dat[i]);
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

unsigned int Display(unsigned char key){
	switch(key){
		case 0x77: LcdPutChar(Symbol[0]);  return 0;
		case 0xb7: LcdPutChar(Symbol[1]);  return 1;
		case 0xd7: LcdPutChar(Symbol[2]);  return 2;
		case 0xe7: LcdPutChar(Symbol[3]);  return 3;
		case 0x7b: LcdPutChar(Symbol[4]);  return 4;
		case 0xbb: LcdPutChar(Symbol[5]);  return 5;
		case 0xdb: LcdPutChar(Symbol[6]);  return 6;
		case 0xeb: LcdPutChar(Symbol[7]);  return 7;
		case 0x7d: LcdPutChar(Symbol[8]);  return 8;
		case 0xbd: LcdPutChar(Symbol[9]);  return 9;
		case 0xdd: LcdPutChar(Symbol[10]); return 10;
		case 0xed: LcdPutChar(Symbol[11]); return 11;
		case 0x7e: LcdPutChar(Symbol[12]); return 12;
		case 0xbe: LcdPutChar(Symbol[13]); return 13;
		case 0xde: LcdPutChar(Symbol[14]); return 14;
		case 0xee: LcdPutChar(Symbol[15]); return 15;
	}
}

void Output(unsigned char *num){
	unsigned int i;
	for(i=0;i<strlen(num);i++){
		switch(num[i]){
			case '0': LcdPutChar(Symbol[0]);  break;
			case '1': LcdPutChar(Symbol[1]);  break;
			case '2': LcdPutChar(Symbol[2]);  break;
			case '3': LcdPutChar(Symbol[3]);  break;
			case '4': LcdPutChar(Symbol[4]);  break;
			case '5': LcdPutChar(Symbol[5]);  break;
			case '6': LcdPutChar(Symbol[6]);  break;
			case '7': LcdPutChar(Symbol[7]);  break;
			case '8': LcdPutChar(Symbol[8]);  break;
			case '9': LcdPutChar(Symbol[9]);  break;
			case '.': LcdPutChar(Symbol[10]); break;
			case '=': LcdPutChar(Symbol[11]); break;
			case '+': LcdPutChar(Symbol[12]); break;
			case '-': LcdPutChar(Symbol[13]); break;
			case '*': LcdPutChar(Symbol[14]); break;
			case '/': LcdPutChar(Symbol[15]); break;
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
	0x00, 0x00, 0x28, 0x28, 0x28, 0x28, 0x28, 0x00, /*"=",b*/
	0x00, 0x00, 0x10, 0x10, 0x7c, 0x10, 0x10, 0x00, /*"+",c*/
	0x00, 0x00, 0x10, 0x10, 0x10, 0x10, 0x10, 0x00, /*"-",d*/
	0x00, 0x00, 0x44, 0x28, 0x10, 0x28, 0x44, 0x00, /*"*",e*/
	0x00, 0x00, 0x10, 0x10, 0x54, 0x10, 0x10, 0x00, /*"/",f*/
};

