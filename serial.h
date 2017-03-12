#ifndef SERIAL_H
#define SERIAL_H


//UART1 ���ʹ�������
void UART1_SendData(char dat){
    ES=0;           //�ش����ж�
    SBUF=dat;
    while(!TI);   //�ȴ����ͳɹ�
    TI=0;           //��������жϱ�־
    ES=1;           //�������ж�
}

//UART1 �����ַ���
void UART1_SendString(char *s){
    while(*s)//����ַ���������
    {
        UART1_SendData(*s++);//���͵�ǰ�ַ�
    }
}

//��дputchar����
char putchar(char c){
    UART1_SendData(c);
    return c;
}

void serial_init();
void serial_shutdown();

void print(char select) {
  switch (select) {
    case 'a':
    printf("hello world\n");
    break;

    default:
    break;
  }
}

#endif