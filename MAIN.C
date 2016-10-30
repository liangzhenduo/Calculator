#include <reg52.h>
#include <def52.h>
#include <key.h>
#include <led.h>

void main(){
	unsigned char key;
	LED = 0;
	for(;;){
		key = KeyScan();
		Light(key);
		switch(key){
			case 0x77: key='0'; break;
			case 0xb7: key='1'; break;
			case 0xd7: key='2'; break;
			case 0xe7: key='3'; break;
			case 0x7b: key='4'; break;
			case 0xbb: key='5'; break;
			case 0xdb: key='6'; break;
			case 0xeb: key='7'; break;
			case 0x7d: key='8'; break;
			case 0xbd: key='9'; break;
			case 0xdd: key='.'; break;
			case 0xed: key='='; break;
			case 0x7e: key='+'; break;
			case 0xbe: key='-'; break;
			case 0xde: key='*'; break;
			case 0xee: key='/'; break;
		}
		/*if(key == '1') LED1=~LED1;
		else if(key == '2') LED2=~LED2;
		else if(key == '3') LED3=~LED3;
		else if(key == '4') LED4=~LED4;*/
	}
}

