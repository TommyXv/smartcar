#include <reg52.h>
#include "motor.h"
#include "route_track.h"

/*void A_route(unsigned char color){
	switch (color){
		  case 1:
		      A_A_route();
			  break;
		  case 2:
		      A_B_route();
			  break;
		  case 3:
		      A_C_route();
			  break;
		  case 4:
		      A_D_route();
			  break;
		  case 5:
		      A_E_route();
			  break;
	}
}

void A_A_route(){
	while(1){
		 motor_speed(1);
		 place_wedges();
		 route_backward();
		 break;
	}
}

void A_B_route(){
	while(1){
		 route_cw();
		 car_crossL();
		 car_adjust();
		 place_wedges();
		 car_backlittle();
		 car_circle(1,180);
		 car_circle(1,45);
		 car_crossR();
		 car_adjust();
		 car_backmid();//ดýต๗สิ
		 break;
	}
}

void A_C_route(){
	while(1){
		 car_circle(1,180);
		 car_backmid();//ดýต๗สิ
		 car_circle(1,90);
		 car_adjust();
		 place_wedges();
		 route_back();
		 break;
	}
}

void A_D_route(){
	while(1){
		 car_circle(1,180);
		 car_backmid();//ดýต๗สิ
		 car_circle(1,45);
		 car_adjust();
		 place_wedges();
		 route_back();
		 break;
	}
}

void A_E_route(){
	while(1){
		 car_circle(1,180);
		 car_backmid();//ดýต๗สิ
		 while(1){
		 	  route_track();
			  delay_nms(1000);
			  break:
		 }
		 place_wedges();
		 route_back();
		 break;
	}
}

void B_route(unsigned char color){
	switch (color){
		  case 1:
		      B_A_route();
			  break;
		  case 2:
		      B_B_route();
			  break;
		  case 3:
		      B_C_route();
			  break;
		  case 4:
		      B_D_route();
			  break;
		  case 5:
		      B_E_route();
			  break;
	}
}

void B_A_route(){
	while(1){
		 route_ccw();
		 car_crossL();
		 car_adjust();
		 place_wedges();
		 car_backlittle();
		 car_circle(1,180);
		 car_circle(2,45);
		 car_crossR();
		 car_adjust();
		 car_backmid();//ดýต๗สิ
		 break;
	}
}

void B_B_route(){
	while(1){
		 motor_speed(1);
		 place_wedges();
		 route_backward();
		 break;
	}
}

void B_C_route(){
	while(1){
		 route_cw();
		 car_crossL();
		 car_adjust();
		 place_wedges();
		 car_backlittle();
		 car_circle(1,180);
		 car_circle(1,45);
		 car_crossR();
		 car_adjust();
		 car_backmid();//ดýต๗สิ
		 break;
	}
}

void B_D_route(){
	while(1){
		 car_circle(1,180);
		 car_backmid();//ดýต๗สิ
		 car_circle(1,90);
		 car_adjust();
		 place_wedges();
		 route_back();
		 break;
	}
}

void B_E_route(){
	while(1){
		 car_circle(1,180);
		 car_backmid();//ดýต๗สิ
		 car_circle(1,45);
		 car_adjust();
		 place_wedges();
		 route_back();
		 break;
	}
}
void C_route(unsigned char color){
	switch (color){
		  case 1:
		      C_A_route();
			  break;
		  case 2:
		      C_B_route();
			  break;
		  case 3:
		      C_C_route();
			  break;
		  case 4:
		      C_D_route();
			  break;
		  case 5:
		      C_E_route();
			  break;
	}
}

void C_A_route(){
	while(1){
		 car_circle(1,180);
		 car_backmid();//ดýต๗สิ
		 car_circle(2,90);
		 car_adjust();
		 place_wedges();
		 route_back();
		 break;
	}
}

void C_B_route(){
	while(1){
		 route_ccw();
		 car_crossL();
		 car_adjust();
		 place_wedges();
		 car_backlittle();
		 car_circle(1,180);
		 car_circle(2,45);
		 car_crossR();
		 car_adjust();
		 car_backmid();//ดýต๗สิ
		 break;
	}
}

void C_C_route(){
	while(1){
		 motor_speed(1);
		 place_wedges();
		 route_backward();
		 break;
	}
}

void C_D_route(){
	while(1){
		 route_cw();
		 car_crossL();
		 car_adjust();
		 place_wedges();
		 car_backlittle();
		 car_circle(1,180);
		 car_circle(1,45);
		 car_crossR();
		 car_adjust();
		 car_backmid();//ดýต๗สิ
		 break;
	}
}

void C_E_route(){
	while(1){
		 car_circle(1,180);
		 car_backmid();//ดýต๗สิ
		 car_circle(1,90);
		 car_adjust();
		 place_wedges();
		 route_back();
		 break;
	}
}*/

void L_R_MID(){
	 check_white();
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
	   car_stop(500);
	   car_backmidL();  
}





