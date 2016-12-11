#include <reg52.h>
#include "def.h"
#include "key.h"
#include "led.h"
#include "lcd.h"
#include "cal.h"

void main(){
	unsigned char key, chr;
	unsigned int num, i;
	unsigned char str[16];
	unsigned char *res;
	Init();
	for(i=0;;){
		key = KeyScan();
		switch(key){
			case 0x77: LcdPutChar(0);  Light(0);  str[i++]='0'; break;
			case 0xb7: LcdPutChar(1);  Light(1);  str[i++]='1'; break;
			case 0xd7: LcdPutChar(2);  Light(2);  str[i++]='2'; break;
			case 0xe7: LcdPutChar(3);  Light(3);  str[i++]='3'; break;
			case 0x7b: LcdPutChar(4);  Light(4);  str[i++]='4'; break;
			case 0xbb: LcdPutChar(5);  Light(5);  str[i++]='5'; break;
			case 0xdb: LcdPutChar(6);  Light(6);  str[i++]='6'; break;
			case 0xeb: LcdPutChar(7);  Light(7);  str[i++]='7'; break;
			case 0x7d: LcdPutChar(8);  Light(8);  str[i++]='8'; break;
			case 0xbd: LcdPutChar(9);  Light(9);  str[i++]='9'; break;
			case 0xdd: LcdPutChar(10); Light(10); str[i++]='.'; break;
			case 0xed: LcdPutChar(11); Light(11); res=calc(str); Output(res); break;
			case 0x7e: LcdPutChar(12); Light(12); str[i++]='+'; break;
			case 0xbe: LcdPutChar(13); Light(13); str[i++]='-'; break;
			case 0xde: LcdPutChar(14); Light(14); str[i++]='*'; break;
			case 0xee: LcdPutChar(15); Light(15); str[i++]='/'; break;
		}
		//if(str[i]=='=') break;
		/*num = Display(key);
		chr = Light(num);
		if(chr == '=')
			break;*/
	}
	//str = "1+1";
	//res = calc(str);
	
	//Output(str);
	//for(;;);
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

void Init(){
	LcdInit();
	LED1 = 0;
	Delay(1000);
	LED2 = 0;
	LED1 = 1;
	Delay(1000);
	LED3 = 0;
	LED2 = 1;
	Delay(1000);
	LED4 = 0;
	LED3 = 1;
	Delay(1000);
	LED4 = 1;
	Delay(1000);
}


