#include <reg52.h>
#include "def52.h"

void Light(unsigned char key){
	unsigned int num;
	switch(key){
		case 0x77: num=0; break;
		case 0xb7: num=1; break;
		case 0xd7: num=2; break;
		case 0xe7: num=3; break;
		case 0x7b: num=4; break;
		case 0xbb: num=5; break;
		case 0xdb: num=6; break;
		case 0xeb: num=7; break;
		case 0x7d: num=8; break;
		case 0xbd: num=9; break;
		case 0xdd: num=10; break;
		case 0xed: num=11; break;
		case 0x7e: num=12; break;
		case 0xbe: num=13; break;
		case 0xde: num=14; break;
		case 0xee: num=15; break;
	}
	P0 = ~num;
}
