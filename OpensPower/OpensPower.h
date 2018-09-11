#pragma once

/*

OPEnS Power Header File
Author: mitch nelke
Date:	August 24, 2018
Version: 1.0

This is the first draft of the OpensPower library written for the OPEnS Lab
at OSU. The library is essentially just an RTC library, meant to interface with
the DS3231 real time clock (most often on the Adafruit breakout board). The class
also allows the use of powerDown(), which shuts off the device when interfaced with
the Opens Power board. The board also allows the user to enable interrupts based on
either alarm. Either alarm can be used to wake the device up, but only the shutoff pin
can be used to turn the device off. It's therefore important to NOT use the shutoff pin
for any other function.

*/

#include <Arduino.h>
#include <Wire.h>


//	definitions for alarm masks
#define EVERY_SECOND		0	//	once per second
#define EVERY_MINUTE		0	//	first second of every minute
#define MATCH_SECONDS		1	//	only second needs to match
#define MATCH_MINUTES		2	//	minute and second match
#define MATCH_HOURS			3	//	hour, minute, second match
#define MATCH_DATE			4	//	date, hour, minute, second match


//	squarewave frequencies
#define SQW_1HZ				0
#define SQW_1KHZ			1
#define SQW_4KHZ			2
#define SQW_8KHZ			3


class OpensPower
{
private:
	//	input pin for reading alarm interrupt when device is on.
	//	can be reused for other purposes.
	int interruptPin;

	//	output pin for shutting device off. This pin will shut off
	//	the power supply until the device is awoken by the RTC alarm.
	//	Don't reuse for any other functionality, only use through
	//	OpensPower object (checks for alarms being set).
	int shutoffPin;

	uint8_t control;				//	control byte for RTC
	uint8_t status;				//	status byte for RTC
	const uint8_t address = 0x68;	//	RTC's I2C address


	//	write the currently saved status byte to the RTC
	void setStatus();

	//	write the currently saved control byte to the RTC
	void setControl();

public:
	bool lostPower;

	uint8_t century;		//	current century	(0,1)
	uint8_t year;			//	two-digit year	(0-99)
	uint8_t month;
	uint8_t date;			//	day of the month (1-31)
	uint8_t day;			//	day of the week	(1-7)
	uint8_t hour;
	uint8_t minute;
	uint8_t second;


	OpensPower(int offPin);
	OpensPower(int offPin, int intPin);

	void begin();

	void powerDown();

	void getTime();
	void setTime(	uint8_t yr,
					uint8_t mo,
					uint8_t dy,
					uint8_t	hr,
					uint8_t	mt,
					uint8_t	sc);

	void getStatus();
	void getControl();
	

/********** Alarm 1 Functions *********/

	bool alarm1_state;		//	enabled or disabled
	bool alarm1_flag;		//	flag indicating alarm has triggered
	uint8_t alarm1_date;	//	day of the month
	uint8_t alarm1_hour;
	uint8_t alarm1_minute;
	uint8_t alarm1_second;
	void alarm1_getTime();	//	gets the time from the RTC and stores in alarm1 variable

	// the following set alarm1's time to trigger.

	//	set based on an offset of the current time in seconds
	void alarm1_SetTime_Offset(uint32_t);

	//	set just the minute and second, using the current date and hour
	void alarm1_setTime(uint8_t m,
						uint8_t s);

	//	set just the hour, minute, second, using the current date
	void alarm1_setTime(uint8_t h,
						uint8_t m,
						uint8_t s);

	//	set everything
	void alarm1_setTime(uint8_t d,	//	day of the month (date)
						uint8_t h,	//	hour
						uint8_t m,	//	minute
						uint8_t s);	//	second

	//	enables alarm1. Types of alarms:
	//	EVERY_SECOND
	//	MATCH_SECONDS
	//	MATCH_MINUTES
	//	MATCH_HOURS
	//	MATCH_DATE
	void alarm1_enable(uint8_t alarmType);


/********** Alarm 2 Functions *********/

//	same as alarm1 except it doesn't count seconds

	bool alarm2_state;		//	enabled or disabled
	bool alarm2_flag;		//	flag indicating alarm has triggered
	uint8_t alarm2_date;	//	day of the month
	uint8_t alarm2_hour;
	uint8_t alarm2_minute;

	void alarm2_getTime();

	void alarm2_setTime(uint8_t m);

	void alarm2_setTime(uint8_t h,
						uint8_t m);

	void alarm2_setTime(uint8_t d,
						uint8_t h,
						uint8_t m);

	//	same as alarm1_enable but uses EVERY_MINUTE in place of
	//	EVERY_SECOND
	void alarm2_enable(uint8_t alarmType);

	void alarm2_disable();


	//	enables the squarewave on INT_SQW at a specified frequency
	void squarewave(uint8_t);

	bool interrupted = false;

	//	straightforward functions.
	void setInterrupt(void (*userFunction)(void));
	void defaultISR(void);
	void clearAlarms();
	uint8_t checkAlarmFlags();
	void clearAlarmFlags();

};




