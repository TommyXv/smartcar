#ifndef ROUTE_TRACK_H
#define ROUTE_TRACK_H


void route_track();
//void route_track_turn();
int filter_R_B1();
int filter_R_F3();
int filter_L_F3();
int filter_L_B1();
//void car_crossL();
void car_crossR();
void car_adjustR();
void route_ccw_();
void route_cw();
void place_wedges();
void route_backward();
void car_stop(unsigned int i);
void car_go();
void car_circle(unsigned char direction,unsigned char degree);
void route_backward();
void car_backward(unsigned int i);
void car_backmidL();
void check_white();
void car_adjustL();
void route_cw_180();
//void route_track_back();
//void car_back();

#endif