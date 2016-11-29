#ifndef __DEF52_H__
#define __DEF52_H__

#define DATA P1
#define KEYS P2
sbit LED1 = P0^0;
sbit LED2 = P0^1;
sbit LED3 = P0^2;
sbit LED4 = P0^3;

sbit CS1 = P3^5;
sbit CS2 = P3^4;
sbit RS = P0^6;
sbit RW = P0^5;
sbit EN = P0^4;
sbit LIGHT = P0^7;

extern unsigned char code Symbol[][8];

void Delay(unsigned int t);
void init();

#endif

