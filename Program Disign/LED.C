#include <reg52.h>
#include "def.h"

unsigned char Light(unsigned int num){
	switch(num){
		case 0x0: LED1=1,LED2=1,LED3=1,LED4=1; return '0';
		case 0x1: LED1=1,LED2=1,LED3=1,LED4=0; return '1';
		case 0x2: LED1=1,LED2=1,LED3=0,LED4=1; return '2';
		case 0x3: LED1=1,LED2=1,LED3=0,LED4=0; return '3';
		case 0x4: LED1=1,LED2=0,LED3=1,LED4=1; return '4';
		case 0x5: LED1=1,LED2=0,LED3=1,LED4=0; return '5';
		case 0x6: LED1=1,LED2=0,LED3=0,LED4=1; return '6';
		case 0x7: LED1=1,LED2=0,LED3=0,LED4=0; return '7';
		case 0x8: LED1=0,LED2=1,LED3=1,LED4=1; return '8';
		case 0x9: LED1=0,LED2=1,LED3=1,LED4=0; return '9';
		case 0xa: LED1=0,LED2=1,LED3=0,LED4=1; return '.';
		case 0xb: LED1=0,LED2=1,LED3=0,LED4=0; return '=';
		case 0xc: LED1=0,LED2=0,LED3=1,LED4=1; return '+';
		case 0xd: LED1=0,LED2=0,LED3=1,LED4=0; return '-';
		case 0xe: LED1=0,LED2=0,LED3=0,LED4=1; return '*';
		case 0xf: LED1=0,LED2=0,LED3=0,LED4=0; return '/';
	}
}
