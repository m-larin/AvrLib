#ifndef _USART_H_
#define _USART_H_ 1

void usart_init (unsigned int speed);

void usart_send(unsigned char c);

void usart_send_str(const char *s);

void usart_send_int(unsigned int c);

#endif /* _USART_H_ */
