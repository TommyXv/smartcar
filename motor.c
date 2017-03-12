/*
tested version.
it works now.
renember to rezero the motor when it
doesn't stop while using stop function
Author: Martin.Wang
GDUT.ROBOT
*/

//#define CYCLE 0xdc00
#define CYCLE 0xdcea
//#define MID_POINT 0xfa9a
#define MID_POINT 0XFACa
#include <AT89X52.H>
#include "motor.h"

sbit Lmotor = P1^1;
sbit Rmotor = P1^0;

//int CYCLE = 0xdc00;
//���ڣ�10ms

unsigned int pwm_motorL = MID_POINT;
unsigned int pwm_motorR = MID_POINT;

//����������ֱ�ӿ������ҵ��pwmֵ
unsigned int stepR = 25;
unsigned int stepL = 20;
//100us�Ĳ�����Ĭ��ֵ

bit stat_motor = 1;
//״̬�������ҵ����flag

bit pwm_high = 0;
//�ߵ�ƽָʾ

bit run_motor = 0;
//�������״̬����������shutdownʱ�ܹ�˳����ֹͣ���


void motor_init(){
  TMOD &= 0X0F;
  TMOD |= 0x10;
  //��ʱ��ѡ��

  TR1 = 1;
  ET1 = 1;
  //��ʱ����ʼ�������ж�
  //ʹ�ö�ʱ��

  Lmotor = 0;
  Rmotor = 0;
  //�����ʼ����������������ź�����


}
//��ʼ��

void motor_shutdown() {
  motor_stop();
  run_motor = 1;

  while(run_motor != 0);
  //��ִ��һ���ж����ں���ֹͣ��ʱ��

  TR0 = 0;
  ET0 = 0;
  Lmotor = 0;
  Rmotor = 0;
}
//ֹͣ��ʱ����أ��������

void motor_speed(char speed) {
  switch (speed) {
    case 0:
    stepR = 10;
	stepL = 7;
    break;

    case 1:
    stepR = 35;
	stepL = 30;
    break;

    case 2:
    stepR = 50;
	stepL = 45;
    break;

    case 3:
    stepR = 100;
	stepL = 90;

    break;

	case 4:
	stepR = 150;
	stepL = 135;
	break;

    default:
    stepR = 35;
	stepL = 30;
    }
}
//�ٶ�ѡ����

void motor_stop(){
  pwm_motorL = MID_POINT;
  pwm_motorR = MID_POINT;
}
//���ֹͣ

void motor_ccw() {
  pwm_motorL = MID_POINT + stepL;
  pwm_motorR = MID_POINT + stepR;
}
//�����ʱ��

void motor_left() {
  pwm_motorL = MID_POINT;
  pwm_motorR = MID_POINT + stepR;
}
//��ת�䣬�����ֹͣ���Ҳ�����ԭ���ٶ�ת��

void motor_right() {
  pwm_motorL = MID_POINT - stepL;
  pwm_motorR = MID_POINT;
}
//��ת�䣬�Ҳ���ֹͣ���������ԭ���ٶ�ת��

void motor_cw() {
  pwm_motorL = MID_POINT - stepL;
  pwm_motorR = MID_POINT - stepR;
}
//˳ʱ��

void motor_backward(){
  pwm_motorL = MID_POINT + stepL;
  pwm_motorR = MID_POINT - stepR;
}
//���ת

void motor_forward () {
  pwm_motorL = MID_POINT - stepL;
  pwm_motorR = MID_POINT + stepR;
}
//ǰ��

void motor_interrupt(){
  if (stat_motor == 1) {

    if (pwm_high == 0) {
      pwm_high = 1;
      Lmotor = 1;
      TH1 = pwm_motorL >> 8;
      TL1 = pwm_motorL;
    } else {
      pwm_high = 0;
      Lmotor = 0;
      TH1 = (65536 - pwm_motorL + CYCLE) >> 8;
      TL1 = 65536 - pwm_motorL + CYCLE;
      Lmotor = 0;
      stat_motor = 0;

      run_motor = 1;
    }

  } else {
    if (pwm_high == 0) {
      pwm_high = 1;
      Rmotor = 1;
      TH1 = pwm_motorR >> 8;
      TL1 = pwm_motorR;
    } else {
      pwm_high = 0;
      Rmotor = 0;
      TH1 = (65536 - pwm_motorR + CYCLE) >> 8;
      TL1 = 65536 - pwm_motorR + CYCLE;
      stat_motor = 1;

      run_motor = 0;
    }
  }
}
//�����жϺ������棬�����ú���ָ��