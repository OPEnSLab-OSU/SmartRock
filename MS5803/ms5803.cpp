#include "ms5803.h"
#include <Arduino.h>


MS5803::MS5803(uint8_t address)
{
	this->address = address;
}

uint8_t MS5803::begin()
{

	Wire.begin();
	
	Wire.beginTransmission( address );
	Wire.write( MS_RESET );
	Wire.endTransmission();
	delay(100);

	Wire.beginTransmission( address );

	for( uint8_t i = 0; i<8; i++ )
	{

		Wire.beginTransmission( address );
		Wire.write( MS_PROMREAD0 + i*2 );
		Wire.endTransmission();

		delay(10);

		Wire.requestFrom( address, 2 );

		uint32_t timeout = millis();

		while( !Wire.available() )
		{

			if(	( millis() - timeout ) > MS5803_TIMEOUT )
			{
				return 1;	//	failed to initialize device
			}
		}

		PROM[i] = Wire.read() << 8;

		if( Wire.available() )
		{
			PROM[i] += Wire.read();
		}
		else
		{
			return 2;
		}
		Serial.print("PROM");Serial.print(i);Serial.print(": ");
		Serial.print(PROM[i]);
		Serial.println();

	}

	return 0;
	
}

uint8_t MS5803::measure()
{
	Wire.beginTransmission( address );
	Wire.write( MS_CONVERTD1_4096 );
	Wire.endTransmission();

	delay( 10 );
	Wire.beginTransmission( address );
	Wire.write( MS_ADCREAD );
	Wire.endTransmission();

	Wire.requestFrom( address , 3 );

	uint32_t timeout = millis();
	while( Wire.available() != 3 )
	{
		if( ( millis() - timeout ) > MS5803_TIMEOUT )
		{
			return 1;	//	failed to initialize device
		}
	}

	pressure_nc = Wire.read() << 16;
	pressure_nc += Wire.read() << 8;
	pressure_nc += Wire.read();

	Wire.endTransmission();


	Wire.beginTransmission( address );
	Wire.write( MS_CONVERTD2_4096 );
	Wire.endTransmission();
	delay( 10 );

	Wire.beginTransmission( address );
	Wire.write( MS_ADCREAD );
	Wire.endTransmission();

	Wire.requestFrom( address , 3);

	timeout = millis();
	while( Wire.available() != 3 )
	{
		if( ( millis() - timeout ) > MS5803_TIMEOUT )
		{
			return 1;	//	failed to initialize device
		}
	}

	temp_nc = Wire.read() << 16;
	temp_nc += Wire.read() << 8;
	temp_nc += Wire.read();

	Wire.endTransmission();

	compensate();
	return 0;
}

void MS5803::compensate()
{

	Serial.print("Temp_nc:\t");Serial.println(temp_nc);
	int64_t dT = 0;
	int64_t TEMP = 0;
	int64_t OFF = 0;
	int64_t SENS = 0;
	int64_t PRESSURE = 0;

	//	Temperature compensation
	dT = int64_t( temp_nc ) - int64_t( int64_t( PROM[5] ) * int32_t( pow(2,8) ) );
	TEMP = int64_t(2000) + int64_t( dT ) * int64_t( PROM[6] ) / int32_t( pow(2,23) );


	//	Pressure Compensation
	OFF = int64_t( PROM[2] ) * int32_t( pow(2,17) )  + int64_t( PROM[4] ) * dT  / int32_t( pow(2,6) );

	SENS = int64_t( PROM[1] ) * int32_t( pow(2,16) )  + int64_t( PROM[3] ) * dT  / int32_t( pow(2,7) );

	PRESSURE = int64_t( pressure_nc * ( SENS / int32_t( pow(2,21) ) ) ) - OFF;

	PRESSURE = PRESSURE / int32_t( pow(2,15) );

	//	convert to float
	pressure_c = float( PRESSURE ) / 1000.00;	//	kPa
	temp_c = float( TEMP ) / 100.00;			//	degrees C

}

float MS5803::getPressure()
{
	return pressure_c;
}

float MS5803::getTemperature()
{
	return temp_c;
}


