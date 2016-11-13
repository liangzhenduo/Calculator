/*
	LCD.H
	128×64液晶屏驱动程序头文件
*/


#ifndef LCD_H_
#define LCD_H_


#include <REG51.H>


//定义背光控制信号
sbit LCD_BL = P1^4;


//点亮背光灯
void LcdLightOn();


//熄灭背光灯
void LcdLightOff();


//清屏
void LcdClear();


//初始化
void LcdInit();


//显示ASCII码（范围：0x20～0x7F）
void LcdPutChar(unsigned char c);


//显示字符串（可以同时包含ASCII码和汉字）
void LcdPuts(unsigned char *s);


#endif	//LCD_H_

