#pragma once

#include <Wire.h>

#define MS5803_TIMEOUT			5000
#define MS_RESET             	0x1E
#define MS_CONVERTD1_256     	0x40
#define MS_CONVERTD1_512     	0x42
#define MS_CONVERTD1_1024    	0x44
#define MS_CONVERTD1_2048    	0x46
#define MS_CONVERTD1_4096    	0x48
#define MS_CONVERTD2_256     	0x50
#define MS_CONVERTD2_512     	0x52
#define MS_CONVERTD2_1024    	0x54
#define MS_CONVERTD2_2048    	0x56
#define MS_CONVERTD2_4096    	0x58
#define MS_ADCREAD           	0x00
#define MS_PROMREAD0        	0xA0

#define MS_ADDRESS				0x77

class MS5803 {
private:
	uint16_t PROM[8];
	float temp_c = 0;
	float pressure_c = 0;
	int32_t temp_nc = 0;
	int32_t pressure_nc = 0;
	uint8_t address;

	void compensate();

public:
	MS5803(uint8_t);
	uint8_t begin();
	uint8_t measure();
	float getPressure();
	float getTemperature();
};