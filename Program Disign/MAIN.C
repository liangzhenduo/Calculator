#include <reg52.h>
#include "def.h"
#include "key.h"
#include "led.h"
#include "lcd.h"

void main(){
	unsigned char key;
	init();
	for(;;){
		key = KeyScan();
		
		Show(key);
		Light(key);
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

void init(){
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
}


