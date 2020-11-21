#include <avr/io.h>
#include "usart.h"

void usart_init (unsigned int speed)
{
	// устанавливаем скорость Baud Rate: 9600
	UBRRH=(unsigned char)(speed>>8);
	UBRRL=(unsigned char) speed;
	UCSRA=0x00;
	// Разрешение работы передатчика
	UCSRB=(1<<TXEN);
	//Установка формата посылки: 8 бит данных, 1 стоп-бит
	UCSRC=(1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0);
}

void usart_send(unsigned char c)//	Отправка байта
{
	while(!(UCSRA&(1<<UDRE)))	//	Устанавливается, когда регистр свободен
	{}
	UDR = c;
}

void usart_send_str(const char *s)//	Отправка строки
{
	while (*s != 0) usart_send(*s++);
}

void usart_send_int(unsigned int c)//	Отправка числа от 0000 до 9999
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
