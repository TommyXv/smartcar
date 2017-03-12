#define N 12
#include <reg52.h>
#include<stdio.h>
#include"Boebot.h"
#include "motor.h"


sbit L_F1 = P0^6;
sbit L_F2 = P0^7;
sbit L_F3 = P0^3;
sbit L_B1 = P0^1;
sbit R_F1 = P0^5;
sbit R_F2 = P0^4;
sbit R_F3 = P0^2;
sbit R_B1 = P0^0;


unsigned char value1 = 0;
unsigned char value2 = 0;
unsigned char value3 = 0;
unsigned char value4 = 0;


/*int	get_L_F1(){//测qti状态函数
   return (P0 & 0X40);
}

int get_R_F1(){
   return (P0 & 0X20);
}*/

int filter_L_B1(){//消抖滤波函数
    char count=0;
	char new_value;
	new_value = L_B1;
	while (value4 !=new_value){
	count++;
	if (count>=N)
	  return new_value;
	delay_nus(100);
	new_value = L_B1;
   }
   return value4;
}

int filter_R_B1()
{//右后qti消抖滤波函数
   unsigned char count=0;
   unsigned	char new_value;
	new_value = R_B1;
	while (value1 !=new_value){
	count++;
	if (count>=N)
	  return new_value;
	delay_nus(50);
	new_value = R_B1;
   }
   return value1;
   }
int filter_L_F3(){//左上qti消抖滤波函数
   unsigned char count=0;
   unsigned	char new_value;
	new_value = L_F3;
	while (value2 !=new_value){
	count++;
	if (count>=N)
	  return new_value;
	delay_nus(100);
	new_value = L_F3;
   }
   return value2;
   }

int filter_R_F3(){//右上qti消抖滤波函数
   unsigned char count=0;
   unsigned	char new_value;
	new_value = R_F3;
	while (value3 !=new_value){
	count++;
	if (count>=N)
	  return new_value;
	delay_nus(100);
	new_value = R_F3;
   }
   return value3;
   }

/*void route_track_turn(){//普通循迹函数，已不用
	if(P0 & 0X60){
	  motor_forward();
	}//向前

	else if(P0 & 0X30){
	  motor_right();
	}//向右转弯

	else if(P0 & 0XC0){
	  motor_left();
	}//向左转弯

	else if(P0 & 0x20){
	  motor_cw();
	}//顺时针微调车身

	else if(P0 & 0x40){
	 motor_ccw ();
	}
	//逆时针微调车身

  else{
    motor_forward();
  }
}*/

void route_track(){//循迹函数
	if((L_F1 == 1) && (R_F1 == 1)){
	   	 motor_forward();
	   }
	   else if((L_F1 == 1) && (R_F1 == 0)){
	   	 motor_cw();
	   }
	   else if((L_F1 == 0) && (R_F1 == 1)){
	   	   motor_ccw();
	   }
	   else{
	   	   motor_forward();
	   }
}

void route_track_back(){
if((L_F1 == 1) && (R_F1 == 1)){
	   	 motor_backward();
	   }
	   else if((L_F1 == 1) && (R_F1 == 0)){
	   	 motor_ccw();
	   }
	   else if((L_F1 == 0) && (R_F1 == 1)){
	   	   motor_cw();
	   }
	   else{
	   	   motor_backward();
	   }
} 

void route_ccw(){ //左转
	static int value = 0;
	static int check_black = 0;
	value = filter_R_F3();
	while(1){
	     motor_ccw();
		 motor_speed(1);
		 if(value != filter_R_F3()){
		   value = filter_R_F3();
		   check_black++; 
		 }
		 if(check_black == 2){
		   check_black = 0;
		   break;
		 }
	}
}

void route_cw(){	//右转
    static int value = 0;
	static int check_black = 0;
	value = filter_L_F3();
	while(1){
	     motor_cw();
		 motor_speed(1);
		 if(value != filter_L_F3()){
		   value = filter_L_F3();
		   check_black++; 
		 }
		 if(check_black == 2){
		   check_black = 0;
		   break;
		 }
	}
}



void place_wedges(){ //放物块
	while(1){
		 motor_speed(1);
		 if(L_F3 == 1 || R_F3 == 1){
		   delay_nms(1);
		   if(L_F3 == 1 || R_F3 == 1)
		     break;
		 }
		 route_track();
	}
}


void car_go(){	//出发
	static int value = 0;
	static int check_black = 0;
	value = filter_R_B1();
	while(1){
	     route_track();
		 motor_speed(2);
		 if(value != filter_R_B1()){
		   value = filter_R_B1();
		   check_black++; 
		 }
		 if(check_black == 4){
		   check_black = 0;
		   break;
		 }
	}
	value = filter_R_F3();
	while(1){
		 route_track();
		 motor_speed(2);
		 if(value != filter_R_F3()){
		   value = filter_R_F3();
		   check_black++;
		   if(check_black == 3){
		   	 check_black = 0;
			 break;
		   }
		 }
	}
}

void car_stop(unsigned int i){//微停_毫秒
	while(1){
		 motor_stop();
		 delay_nms(i);
		 break;
	}
}

void car_adjustR(){ //调整车身
	while(1){
		 motor_speed(1);
		 motor_cw();
		 if(L_B1 == 1){
		   delay_nms(20);
		   if(L_B1 == 1){
		   	 break;
			 } 
		 }
	}
}

void car_adjustL(){ //调整车身
	while(1){
		 motor_speed(1);
		 motor_ccw();
		 if(L_B1 == 1){
		   delay_nms(200);
		   if(L_B1 == 1){
		   	 break;
			 } 
		 }
	}
}

void car_circle(unsigned char direction,unsigned char degree){//转角度选择函数

	if(direction == 1){
	  switch(degree){
	  		case 45:
			    route_ccw();
				break;
			case 90:
			    route_ccw();
				route_ccw();
				break;
			case 135:
			    route_ccw();
				route_ccw();
				route_ccw();
				break;
			case 180 :
			    route_cw();
				break;
	  }
	}
	if(direction == 2){
	  switch (degree){
	  		case 45:
			    route_cw();
			    break;
			case 90:
			    route_cw();
				route_cw();
				break;
			case 135:
			    route_cw();
				route_cw();
				route_cw();
				break;
			case 180:
			    route_cw();
				route_cw();
				break;
			    
	  }
	}
}

/*void car_crossL(){
	static int value = 0;
	static int check_black = 0;
	value = filter_R_F3();
	while(1){
		 motor_forward();
		 motor_speed(1);
		 if(value != filter_L_F3()){
		   value = filter_L_F3();
		   check_black++; 
		   }
		   if(check_black == 2){
		        check_black = 0;
		         break;
		 }

	}
	car_stop(1000);
} */


void car_crossR(){//右方越线函数
		 static int value = 0;
	     static int check_black = 0;
	     value = filter_L_F3();
	     while(1){
	          motor_forward();
		      motor_speed(1);
		      if(value != filter_L_F3()){
		      value = filter_L_F3();
		      check_black++; 
		   }
		      if(check_black == 2){
		        check_black = 0;
		         break;
		 }
	}
	car_stop(1000);
}

void route_backward(){//倒退函数
	while(1){
		 motor_speed(1);
		 motor_backward();
		 if(L_F3 == 1 || R_F3 == 1){
		   break;
		 }
	}
}

void car_backward(unsigned int i){//倒退多少毫秒
	while(1){
		 motor_speed(1);
		motor_backward();
		 delay_nms(i);
		 break;
	}
}

void car_backmidL()
{//在左方使用
	static int value = 0;
	static int check_black = 0;
	value = filter_R_F3();
	 while(1){
	          route_track();
		      motor_speed(1);
		      if(value != filter_R_F3()){
		      value = filter_R_F3();
		      check_black++; 
		   }
		      if(check_black == 3){
		        check_black = 0;
		         break;
				 }
			   }
	value = filter_R_F3();
	  while(1){
	          motor_ccw();
		      motor_speed(1);
		      if(value != filter_R_F3()){
		      value = filter_R_F3();
		      check_black++; 
		   }
		      if(check_black == 3){
		        check_black = 0;
		         break;
		 }
	}
}

void check_white(){
	 static int value = 0;
	     static int check_white = 0;
	     value = filter_L_B1();
	     while(1){
	          route_track();
		      motor_speed(1);
		      if(value != filter_L_B1()){
		      value = filter_L_B1();
		      check_white++; 
		   }
		      if(check_white == 2){
		        check_white = 0;
		         break;
		 }
	}
	car_stop(1000);
}

void route_cw_180(){
	while(1){
		 motor_cw();
		 motor_speed(1);
		 if(L_F1 == 0 && R_F1 == 0){
		   delay_nms(1);
		   if(L_F1 == 0 && R_F1 == 0){
		   	 break;
		   }
		 }
	}
	while(1){
		 motor_cw();
		 motor_speed(1);
		 if(L_F1 == 1 && R_F1 == 1){
		   delay_nms(1);
		   if(L_F1 == 1 && R_F1 == 1){
		   	 break;
		   }
		 }
	}
}





/*void car_go(){
	while(1){
		 route_track();
		 motor_speed(2);
		 if(L_B1 == 1){
		   delay_nus(100);
		   if(L_B1 == 1){
		   	 break;
		   }
		 }
	}
	while(1){
		 route_track();
		 motor_speed(2);
		 if(L_B1 == 0){
		   delay_nus(100);
		   if(L_B1 == 0){
		   	 break;
		   }
		 }
	}
	while(1){
		 route_track();
		 motor_speed(2);
		 if(L_B1 == 1){
		   delay_nus(100);
		   if(L_B1 == 1){
		   	 break;
		   }
		 }
	}
	while(1){
		 route_track();
		 motor_speed(2);
		 if(L_B1 == 0){
		   delay_nus(100);
		   if(L_B1 == 0){
		   	 break;
		   }
		 }
	}
	while(1){
		 route_track();
		 motor_speed(2);
		 if(L_B1 == 1){
		   delay_nus(100);
		   if(L_B1 == 1){
		   	 break;
		   }
		 }
	}
}*/

void car_backmidR(){
static int value = 0;
	static int check_black = 0;
	value = filter_R_F3();
	 while(1){
	          route_track();
		      motor_speed(1);
		      if(value != filter_R_F3()){
		      value = filter_R_F3();
		      check_black++; 
		   }
		      if(check_black == 3){
		        check_black = 0;
		         break;
				 }
			   }
	value = filter_R_F3();
	  while(1){
	          motor_ccw();
		      motor_speed(1);
		      if(value != filter_R_F3()){
		      value = filter_R_F3();
		      check_black++; 
		   }
		      if(check_black == 4){
		        check_black = 0;
		         break;
		 }
	}
}