#include <reg52.h>
#include <def52.h>

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

unsigned char KeyScan(void){  //键盘扫描函数，使用行列反转扫描法
	unsigned char cord_h,cord_l;//行列值中间变量
	KEYS = 0x0f;            //行线输出全为0
	cord_h=KEYS&0x0f;     //读入列线值
	if(cord_h!=0x0f){    //先检测有无按键按下
  		Delay(20);        //延时去抖
  		if(cord_h!=0x0f){
    		cord_h=KEYS&0x0f;  //读入列线值
    		KEYS=cord_h|0xf0;  //输出当前列线值
    		cord_l=KEYS&0xf0;  //读入行线值
   		}
  	}
  	KEYS = 0x0f;
  	while((KEYS&0x0f)!=0x0f){ //等待键释放
     	Delay(20);
   	}
	return cord_h+cord_l;
}

