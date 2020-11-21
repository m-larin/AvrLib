#ifndef AM2320_H
#define AM2320_H

class Am2320
{
	public:
		Am2320(volatile uint8_t * sensorPort, volatile uint8_t * sensorPin, volatile uint8_t * sensorDdr, unsigned char sensorBit);
		unsigned char read(unsigned char * data);

	private:
		uint8_t _sensorPort;
		uint8_t _sensorPin;
		uint8_t _sensorDdr;
		unsigned char _sensorBit;	
};

#endif