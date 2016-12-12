#include <reg52.h>
#include "def.h"

unsigned char KeyScan(){		//键盘扫描函数，使用行列反转扫描法
	unsigned char col,row;		//行列值中间变量
	KEYS = 0x0f;				//行线输出全为0
	col=KEYS&0x0f;				//读入列线值
	if(col!=0x0f){				//先检测有无按键按下
  		Delay(20);				//延时去抖
  		if(col!=0x0f){
			col=KEYS&0x0f;		//读入列线值
			KEYS=col|0xf0;		//输出当前列线值
			row=KEYS&0xf0;		//读入行线值
   		}
  	}
  	KEYS = 0x0f;
  	while((KEYS&0x0f)!=0x0f){	//等待键释放
		Delay(20);
   	}
	return col+row;
}
