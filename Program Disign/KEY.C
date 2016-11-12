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

unsigned char KeyScan(void){  //����ɨ�躯����ʹ�����з�תɨ�跨
	unsigned char cord_h,cord_l;//����ֵ�м����
	KEYS = 0x0f;            //�������ȫΪ0
	cord_h=KEYS&0x0f;     //��������ֵ
	if(cord_h!=0x0f){    //�ȼ�����ް�������
  		Delay(20);        //��ʱȥ��
  		if(cord_h!=0x0f){
    		cord_h=KEYS&0x0f;  //��������ֵ
    		KEYS=cord_h|0xf0;  //�����ǰ����ֵ
    		cord_l=KEYS&0xf0;  //��������ֵ
   		}
  	}
  	KEYS = 0x0f;
  	while((KEYS&0x0f)!=0x0f){ //�ȴ����ͷ�
     	Delay(20);
   	}
	return cord_h+cord_l;
}
