#include <reg52.h>
#include "def.h"

void LedLight(unsigned int num){
	switch(num){
		case 0x0: LED1=1,LED2=1,LED3=1,LED4=1; break;
		case 0x1: LED1=1,LED2=1,LED3=1,LED4=0; break;
		case 0x2: LED1=1,LED2=1,LED3=0,LED4=1; break;
		case 0x3: LED1=1,LED2=1,LED3=0,LED4=0; break;
		case 0x4: LED1=1,LED2=0,LED3=1,LED4=1; break;
		case 0x5: LED1=1,LED2=0,LED3=1,LED4=0; break;
		case 0x6: LED1=1,LED2=0,LED3=0,LED4=1; break;
		case 0x7: LED1=1,LED2=0,LED3=0,LED4=0; break;
		case 0x8: LED1=0,LED2=1,LED3=1,LED4=1; break;
		case 0x9: LED1=0,LED2=1,LED3=1,LED4=0; break;
		case 0xa: LED1=0,LED2=1,LED3=0,LED4=1; break;
		case 0xb: LED1=0,LED2=1,LED3=0,LED4=0; break;
		case 0xc: LED1=0,LED2=0,LED3=1,LED4=1; break;
		case 0xd: LED1=0,LED2=0,LED3=1,LED4=0; break;
		case 0xe: LED1=0,LED2=0,LED3=0,LED4=1; break;
		case 0xf: LED1=0,LED2=0,LED3=0,LED4=0; break;
	}
}

void LedInit(){
	LED1 = 0;
	Delay(200);
	LED2 = 0;
	LED1 = 1;
	Delay(200);
	LED3 = 0;
	LED2 = 1;
	Delay(200);
	LED4 = 0;
	LED3 = 1;
	Delay(200);
	LED4 = 1;
}
