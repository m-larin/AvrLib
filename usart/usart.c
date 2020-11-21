#include <avr/io.h>
#include "usart.h"

void usart_init (unsigned int speed)
{
	// ������������� �������� Baud Rate: 9600
	UBRRH=(unsigned char)(speed>>8);
	UBRRL=(unsigned char) speed;
	UCSRA=0x00;
	// ���������� ������ �����������
	UCSRB=(1<<TXEN);
	//��������� ������� �������: 8 ��� ������, 1 ����-���
	UCSRC=(1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0);
}

void usart_send(unsigned char c)//	�������� �����
{
	while(!(UCSRA&(1<<UDRE)))	//	���������������, ����� ������� ��������
	{}
	UDR = c;
}

void usart_send_str(const char *s)//	�������� ������
{
	while (*s != 0) usart_send(*s++);
}

void usart_send_int(unsigned int c)//	�������� ����� �� 0000 �� 9999
{
	unsigned char temp;
	c=c%10000;
	temp=c/100;
	usart_send(temp/10+'0');
	usart_send(temp%10+'0');
	temp=c%100;
	usart_send(temp/10+'0');
	usart_send(temp%10+'0');
}
