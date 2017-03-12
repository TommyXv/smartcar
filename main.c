#include <reg52.h>
#include <stdio.h>
#include "serial.h"
#include "motor.h"
#include "route_track.h"
#include "ultrasonic.h"
#include "color_detect.h"
#include "route_chose.h"

bit newinfo = 0;

char info;
bit error_measure;//³¬Éù²¨²âÁ¿Òç³öÎ»





void serialdeal(){
switch (info) {
		case 'p':
		//printf("RED:%d\nGREEN:%d\nBLUE:%d\n",color_printf(1),color_printf(2),color_printf(3));
		printf("%d", color_count1());
		break;

		case 'c':
		color_calibrate();
		printf("calibrated\nvalue:\n");
		printf("RED:%d\nGREEN:%d\nBLUE:%d\n",color_printf(1),color_printf(2),color_printf(3));
		
		break;

		case 't':
		printf("loop back test\n");
		break;
		}
} 

/*void serialdeal2(){
  switch(info){
  	case 't':
	printf("loop back test\n");
	break;

	case 'p':
	printf("S is %d\n",ultrasonic_measure());
	break;
  }
} */
int main() {
   //color_init();
   motor_init();
   //serial_init();
    EA = 1;
	while(1){
	/*if(newinfo == 1){	
	 serialdeal();
	 newinfo = 0;
	 }*/
	 
	  //car_go();
	  //car_stop(1000);
	  car_go();
	  //car_circle(1,90);

	   /*check_white();
	   car_circle(2,45);
	   car_crossL();
	   car_stop(500);
	   car_adjustR();
	   car_stop(500);
	   place_wedges();
	   car_stop(500);
	   car_backward(1000);
	   car_stop(500);
	   car_adjustL();
	   car_stop(500);
	   car_circle(2,45);
	   car_stop(500);
	   car_crossL();
	   car_adjustR();	   
	   car_stop(500);*/

	   //car_backmidL();  
	  check_white();
	   car_circle(1,45);
	   car_crossR();
	   car_stop(500);
	   car_adjustL();
	   car_stop(500);
	   place_wedges();
	   car_stop(500);
	   car_backward(1000);
	   car_stop(500);
	   car_stop(500);
	   car_circle(1,45);
	   car_stop(500);
	   car_crossR();
	   car_adjustL();	   
	   car_stop(500);
	   //car_backmidL();  
	while(1){
	   route_track();
	}
    
	 //if(newinfo == 1){
	  //while(1){
	  	   //motor_stop();
	 // }
	 //}
}	
	return 0;
}

void T1interrupt() interrupt 3 {
	EA = 0;
	motor_interrupt();
	EA = 1;
}

void T0interrupt() interrupt 1 {
	EA = 0;	
	 //error_measure = 1;
	color_T0interrupt();
	EA = 1;
} 

void INT0interrupt() interrupt 0 {
	EA = 0;
   color_INT0interrupt();
	EA = 1;
}

void INT1interrupt() interrupt 2{
  EA = 0;
  TR0 = 0;
  EA = 1;
} 


void serial_interrupt() interrupt 4 {
EA = 0;
 	if(RI){
	  RI = 0;
	  info = SBUF;
	  newinfo = 1;
	}
EA = 1;
}


