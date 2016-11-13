/*
	LCD.C
	128×64 LCD驱动程序
*/


#include <INTRINS.H>
#include <ABSACC.H>
#include "LCD.H"


//定义屏幕光标（取值0～63，光标本身不可见）
unsigned char LcdCursor;


/*
函数：LcdLightOn()
功能：点亮背光灯
*/
void LcdLightOn()
{
	LCD_BL = 1;
}


/*
函数：LcdLightOff()
功能：熄灭背光灯
*/
void LcdLightOff()
{
	LCD_BL = 0;
}


/*
函数：LcdGetBF()
功能：读出状态位BF
返回：
	BF=1，表示忙，不可进行任何操作
	BF=0，表示不忙，可以进行正常操作
*/
bit LcdGetBF()
{
	unsigned char dat;
	dat = XBYTE[0xD002];	//XBYTE的定义见<ABSACC.H>
	return (bit)(dat & 0x80);
}


/*
函数：LcdWriteCmd()
功能：向LCD发送命令
参数：
	cmd：命令字，详见器件的数据手册
*/
void LcdWriteCmd(unsigned char cmd)
{
	while ( LcdGetBF() );
	XBYTE[0xD000] = cmd;
}


/*
函数：LcdWriteDat()
功能：向LCD写入数据
参数：dat，要写入的数据
说明：目标地址由地址计数器AC隐含指定，写完后AC自动加1
*/
void LcdWriteDat(unsigned char dat)
{
	while ( LcdGetBF() );
	XBYTE[0xD001] = dat;
}


/*
函数：LcdReadDat()
功能：从LCD读出数据
返回：读出的数据
*/
/*
unsigned char LcdReadDat()
{
	volatile unsigned char dat;
	while ( LcdGetBF() );
	dat = XBYTE[0xD003];
	dat = XBYTE[0xD003];	//需要连续执行两次才能够读出真正的数据
	return dat;
}
*/


/*
函数：LcdSetAC()
功能：设置DDRAM（显示数据RAM）的AC（地址计数器）值
参数：
	ac：地址计数器值，范围0～63
*/
void LcdSetAC(unsigned char ac)
{
	ac &= 0x3F;
	ac |= 0x80;
	LcdWriteCmd(ac);
}


/*
函数：LcdClear()
功能：LCD清屏，并使光标回到0
*/
void LcdClear()
{
	LcdWriteCmd(0x01);	//清屏命令
	LcdCursor = 0;
}


/*
函数：LcdDelay()
功能：延时(t*100)个机器周期
*/
void LcdDelay(unsigned char t)
{
	unsigned char n;
	do
	{
		n = 49;
		while ( --n != 0 );
	} while ( --t != 0 );
}


/*
函数：LcdInit()
功能：LCD初始化
*/
void LcdInit()
{
	LcdWriteCmd(0x30);	//设置基本指令集
	LcdDelay(3);
	LcdWriteCmd(0x30);	//设置基本指令集（需要再执行一次）
	LcdDelay(1);
	LcdWriteCmd(0x0C);	//开启显示
	LcdDelay(3);
	LcdClear();			//清屏
	LcdDelay(250);
	LcdWriteCmd(0x06);	//设置进入点
	LcdDelay(10);
}


/*
函数：LcdCheckAC()
功能：根据光标位置调整AC
*/
void LcdCheckAC()
{
	switch ( LcdCursor )
	{
	case 16:
		LcdSetAC(16);
		break;
	case 32:
		LcdSetAC(8);
		break;
	case 48:
		LcdSetAC(24);
		break;
	case 64:
		LcdCursor = 0;
		LcdSetAC(0);
		break;
	default:
		break;
	}
}


/*
函数：LcdPutChar()
功能：显示ASCII码
参数：
	c为可显示的ASCII码（0x20～0x7F）
*/
void LcdPutChar(unsigned char c)
{
	LcdWriteDat(c);
	LcdCursor++;
	LcdCheckAC();
}


/*
函数：LcdPutHZ()
功能：显示汉字
参数：
	ch,cl：汉字编码
*/
void LcdPutHZ(unsigned char ch, unsigned char cl)
{
	if ( LcdCursor & 0x01 )
	{//显示汉字时，必须偶地址对准，即光标位置不能是奇数
		LcdPutChar(' ');	//额外输出一个空格
	}
	LcdWriteDat(ch);
	LcdWriteDat(cl);
	LcdCursor += 2;
	LcdCheckAC();
}


/*
函数：LcdPuts()
功能：显示字符串
参数：
	*s：要显示的字符串（可同时包含ASCII码和汉字）
*/
void LcdPuts(unsigned char *s)
{
	unsigned char ch, cl;
	for (;;)
	{
		ch = *s++;
		if ( ch == '\0' ) break;
		if ( ch < 0x80 )
		{
			LcdPutChar(ch);
		}
		else
		{
			cl = *s++;
			LcdPutHZ(ch,cl);
		}
	}
}

