#include<reg52.h>
#include"intrins.h"
sbit trig = P2^0;
sbit echo = P2^1;

unsigned long time;
unsigned long distance;
extern bit error_measure;//超声波计时溢出位
void ultrasonic_init(){
	TMOD &= 0Xf0;
	TMOD |= 0X01;
  	TL0 = 0;	//计数器低四位至零
	TH0 = 0;	//计数器高四位至零
	TR0 = 0;	//停止计数
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
	while(echo == 1&&TR0 == 1); //等待接收回波结束，关闭定时器1
	        TR0 = 0;
			time = TH0 * 256 + TL0;
			TH0 = 0;         //清空定时器1
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
  //关闭定时器0中断
  TR0 = 0;
  //关闭定时器0
}






