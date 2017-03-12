#include<reg52.h>
#include"intrins.h"
sbit trig = P2^0;
sbit echo = P2^1;

unsigned long time;
unsigned long distance;
extern bit error_measure;//��������ʱ���λ
void ultrasonic_init(){
	TMOD &= 0Xf0;
	TMOD |= 0X01;
  	TL0 = 0;	//����������λ����
	TH0 = 0;	//����������λ����
	TR0 = 0;	//ֹͣ����
	ET0 = 1;

}

long ultrasonic_count(){
	trig = 1;
	_nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_();
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_();
	trig = 0;
  	while(echo == 0);
			TR0 = 1;
	while(echo == 1&&TR0 == 1); //�ȴ����ջز��������رն�ʱ��1
	        TR0 = 0;
			time = TH0 * 256 + TL0;
			TH0 = 0;         //��ն�ʱ��1
			TL0 = 0;
			distance=time/58;
		   if(error_measure == 1 || distance >= 700){
		   error_measure = 0;
	       return 99999;
		   }
		   else{
		     
		   	 return distance;
		   }
}

void ultrasonic_shutdown() {
  ET0 = 0;
  //�رն�ʱ��0�ж�
  TR0 = 0;
  //�رն�ʱ��0
}






