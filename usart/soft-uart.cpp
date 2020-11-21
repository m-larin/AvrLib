/*
//програмный uart
#define BAUD_C 52 //Вычислено эксперементально lkz 4,8 MGh
#define TxD PORTB3
#define T_START TCCR0B = (1 << CS01) // F_CPU/8
#define T_STOP TCCR0B = 0
#define T_RESET TCNT0 = 0
*/

/*
//Переменные для програмного uart
uint8_t temp, count, start;
volatile uint8_t c;
*/

/*
//Отправка бита
void send(uint8_t data) {
	if (count >= 8) {
		PORTB |= (1<<TxD);
		start = 0; temp = 0; c = 0; count = 0;
		T_STOP;
		OCR0A = 0;
		return;
	}
	if(c == 1) {
		if (start == 0) {
			temp = 0x80;
			start = 1;
			count--;
		}
		else {
			temp = data;
			temp = temp >> count;
			temp = temp << 7;
		}
		switch(temp) {
			case 0x80 : PORTB &= ~(1 << TxD);	break;
			case 0 : PORTB |= (1 << TxD);	break;
		}
		count++;
		c = 0;
	}
}

//Отправка байта
void send_ch(uint8_t data){
	uint8_t f;
	data = ~data;
	T_START;
	for(f = 0; f < 10; f++){
		while(c == 0);
		send(data);
	}
}

//Отправка строки
void send_str(char *text){
	while(*text) {
		send_ch(*text++);
	}
}

//	Отправка числа от 000 до 255
void send_num(unsigned char num)
{
	send_ch(num/100 + '0');
	send_ch((num%100) / 10 + '0');
	send_ch(num%10 + '0');
}
*/

/* Прерывание
ISR(TIM0_COMPA_vect){
	OCR0A = BAUD_C;
	c = 1;
	T_RESET;
}
*/

 /*
    //INIT UART	
	DDRB |= (1 << TxD);
	TIMSK0 = (1 << OCIE0A);
*/
	