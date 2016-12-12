#include <reg52.h>
#include "key.h"
#include "led.h"
#include "lcd.h"
#include "cal.h"

void main(){
	unsigned char key;
	unsigned int i;
	unsigned char str[20];
	unsigned int *res;
	LcdInit();
	LedInit();
	for(str[0]='0', i=1;;){
		key = KeyScan();
		switch(key){
			case 0x77: LcdDisplay(0);  LedLight(0);  str[i++]='0'; break;
			case 0xb7: LcdDisplay(1);  LedLight(1);  str[i++]='1'; break;
			case 0xd7: LcdDisplay(2);  LedLight(2);  str[i++]='2'; break;
			case 0xe7: LcdDisplay(3);  LedLight(3);  str[i++]='3'; break;
			case 0x7b: LcdDisplay(4);  LedLight(4);  str[i++]='4'; break;
			case 0xbb: LcdDisplay(5);  LedLight(5);  str[i++]='5'; break;
			case 0xdb: LcdDisplay(6);  LedLight(6);  str[i++]='6'; break;
			case 0xeb: LcdDisplay(7);  LedLight(7);  str[i++]='7'; break;
			case 0x7d: LcdDisplay(8);  LedLight(8);  str[i++]='8'; break;
			case 0xbd: LcdDisplay(9);  LedLight(9);  str[i++]='9'; break;
			case 0xdd: LcdDisplay(10); LedLight(10); str[i++]='.'; break;
			case 0xed: LcdDisplay(11); LedLight(11); str[i++]='*', str[i++]='1'; res=Calc(str); Output(res); str[0]='0', i=1; break;
			case 0x7e: LcdDisplay(12); LedLight(12); str[i++]='+'; break;
			case 0xbe: LcdDisplay(13); LedLight(13); str[i++]='-'; break;
			case 0xde: LcdDisplay(14); LedLight(14); str[i++]='*'; break;
			case 0xee: LcdDisplay(15); LedLight(15); str[i++]='/'; break;
		}
	}
}

void Delay(unsigned int t){
	do{
		TH0 = 0xFC;
		TL0 = 0x66;
		TR0 = 1;
		while ( !TF0 );
		TR0 = 0;
		TF0 = 0;
	} while ( --t != 0 );
}

