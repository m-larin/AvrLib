#include <avr/io.h>
#include <util/delay.h>
#include "am2320.h"


Am2320::Am2320(volatile uint8_t * sensorPort, volatile uint8_t * sensorPin, volatile uint8_t * sensorDdr, unsigned char sensorBit){
	_sensorPort = *sensorPort;
	_sensorPin = *sensorPin;
	_sensorDdr = *sensorDdr;
	_sensorBit = sensorBit;
}

/*************************************************************************
1. ���������� ��������� ���� ��� � ����� ������ - ��� ������� �� 800 ����������� ��������� ��� � LOW, ����� ������������� �� ����;
2. ����� 30 ��� AM2320 �������� ��������������, ����� ������� �������� ���� � LOW �� 80 ���, � ����� � HIGH �� 80 ���;
3. DHT11 �������� �������� �������� ����������, ������ ��� ���������� � ������ LOW � ������� 50 ���, � ����� HIGH ������ �����������������: ���� 26-28 ���, �� ��� ����, ���� �� 70 ��� - �������;
4. �� ��������� �������� 40 ��� ���������� DHT11 "�� ��������" ��� ��� ��������� ���� � LOW �� 50 ��� � ����������� ��.
���� � ��������� ������� ����������,�� �� ��������� �� �������� ����� ������� �������     */
/************************************************************************/
unsigned char Am2320::read(unsigned char * data)
{
	data[0] = data[1] = data[2] = data[3] = data[4] = 0;

	_sensorDdr |=_BV(_sensorBit); //��� �� �����
	_sensorPort &= ~(_BV(_sensorBit)); //�� ������ 0
	_delay_ms(1); //���� 1 ��
	_sensorPort |= (_BV(_sensorBit)); //��������� �����
	_sensorDdr &= ~(_BV(_sensorBit));  //���� �� ����

	//���� ������ ���+���� - 0 �� ����
	unsigned char count = 0;
	while (_sensorPin & (_BV(_sensorBit))){
		//������ ������ �������� ����� 20-40 ���, �� �� ���� 200 ���, ��� ����������
		//���� �� ���� 1 �������� � �����, �� �� ����� 200 ���, ���� ����� �� 200 ��� �� ������ ��� �� �������
		_delay_us(5);
		count++;
		if (count > 40){
			return 0;
		}
	}
	
	//������ �������, ������ ���� ���� �� ��������� ���� ����� 80 ���
	//�������� � ����� ���� �� ���� 0
	while (!(_sensorPin&(_BV(_sensorBit))));

	//������ ���� ���� �������� �������� ������
	//�������� � ����� ���� �� ���� 1
	while (_sensorPin&(_BV(_sensorBit)));
	
	//������ ��������, ��������� 40 ��� - 5 ����
	//i-����� �����
	for(int i=0; i<5; i++){
		//j-����� ����, ��� ��� ���� ���� ����� ������� �� �������� ������� � �������� ���� ������ �� ���������� j �� 7 �� 0
		for(int j=7; j>=0; j--){
			//�������� �� ������� ������ ������ ���� � �����, ������ �� 50 ��� �� � �������� ��� ������ �� ����� �������� �� �����
			//�������� ���������� ������ �� 1 ���, ��� ����������� �������� 0 ����� ������ � ��� �������� 1 ������ ���� ������
			//��� ��� ������ ����� ��������� ������� ����������� �� ������� ����������� ��� ������
			int preDataCount = 0;
			while (!(_sensorPin&(_BV(_sensorBit)))){
				_delay_us(1);
				preDataCount++;
			}
			
			//������� ��� ������
			int dataCount = 0;
			while (_sensorPin&(_BV(_sensorBit))){
				_delay_us(1);
				dataCount++;
			}
			
			//� ����� ����������, ���� ���������� ���� �� ���� ��� ������ ��� ���������� ������� �� ������� ���� = 1 ����� 0
			//����� ������ �������, ��� ��� � ������ ������� �� ��� ����� ������ ��������� ����
			if (preDataCount < dataCount){
				//������� 1
				data[i] |= _BV(j);
			}
		}
	}
	
	//��������� ����������� ����� � ��� ��� �� �������
	unsigned char checkSumm = data[0] + data[1] + data[2] + data[3];
	if (checkSumm == data[4] && data[4]>0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
