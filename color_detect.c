#include <reg52.h>
#define COLOR_TIME 19456

unsigned int color_count_store[3] = {0,0,0};
//RGB for color[0-2];
unsigned int color_count = 0;
unsigned char color_stat = 0;
//�����ڼ�λ��ֵ

float pred, pgreen, pblue;
//��ƽ�������ͨ��У׼����

float color_true[3] = {0,0,0};
//ת��Ϊ256^3ɫ�Ľ��

bit color_calibrated = 0;

sbit s0 = P2^3;
sbit s1 = P2^2;
sbit s2 = P2^6;
sbit s3 = P2^7;

void color_init(){
  s0 = 1;
  s1 = 1;
  {
    TMOD &= 0xF0;
    TMOD |= 0x01;
    //����ģʽ
    TH0 = COLOR_TIME >> 8;
    TL0 = COLOR_TIME;
    //���ö�ʱ��ʱ��
    PT0=1;
    //���ȼ�
    ET0=1;
    //����ʱ��0�ж�
    TR0=1;
    //�򿪶�ʱ��0
  }//T0 initate
  {
    PX0 = 0;
    //���ȼ�

    IT0 = 1;
    //�½��ش���

    EX0 = 1;
    //���ⲿ�ж�0
  }//INT0 interrupt init
}

void color_shutdown() {
  ET0 = 0;
  //�رն�ʱ��0�ж�
  TR0 = 0;
  //�رն�ʱ��0

  EX0 = 0;
  //�ر��ⲿ�ж�
}

void color_T0interrupt() {
  TR0 = 0;
  //�ص���ʱ��
  TH0 = COLOR_TIME >> 8;
  TL0 = COLOR_TIME;
  //���ö�ʱ��ʱ��
  ++color_stat;

  switch (color_stat) {
    case 1:
    s2 = 0; s3 = 0; color_count = 0;
    //��һ������ѡ���ɫ�˾����޻�ȡ��ɫֵ������������
    break;

    case 2:
    color_count_store[0] = color_count; s2 = 0; s3 = 1; color_count = 0;
    //��ȡ��ɫ��ֵ��ѡ����ɫ�˾�������������
    break;

    case 3:
    color_count_store[2] = color_count; s2 = 1; s3 = 1; color_count = 0;
    //��ȡ��ɫ��ֵ��ѡ����ɫ�˾�������������
    break;

    case 4:
    color_count_store[1] = color_count; s2 = 1; s3 = 0; color_stat = 0;
    //��ȡ��ɫ��ֵ��ѡ�����˾�������������
    break;

  }

  color_true[0] = (int)(color_count_store[0] * pred);
  color_true[1] = (int)(color_count_store[1] * pgreen);
  color_true[2] = (int)(color_count_store[2] * pblue);

  TR0 = 1;
  //���´򿪶�ʱ��
}

void color_INT0interrupt(){
  ++color_count;
}

void color_calibrate(){
  pred = 255.0 / color_count_store[0];
  pgreen = 255.0 / color_count_store[1];
  pblue = 255.0 / color_count_store[2];
  //У׼256ɫ��
  color_calibrated = 1;
}

int color_printf(char colors){
  if (color_calibrated == 1) {
    switch (colors) {
      case 1:
      return color_true[0];
      break;

      case 2:
      return color_true[1];
      break;

      case 3:
      return color_true[2];
			break;

			default:
			return 9999;
    }
  }
  else{
    switch (colors) {
      case 1:
      return color_count_store[0];
      break;

      case 2:
      return color_count_store[1];
      break;

      case 3:
      return color_count_store[2];
      break;

			default:
				return 9999;
  }
}
}

int color_count1(void){
	if(color_printf(1) > 210){
	  if(color_printf(2) > 220){
	  	return 2;//��ɫ
	  }
	  else{
	  	return 1;//��ɫ
	  }
	}
	else if(color_printf(1) >100 ){
	  return 3;// ��ɫ
	}
	else{
	  if(color_printf(1) < 100){
	    if(color_printf(3) > 60){
	  	return 5;//��ɫ
	  }
	  else{
	  	return 4;//��ɫ
	  }
	}
 }	
}