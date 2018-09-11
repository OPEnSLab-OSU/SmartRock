
#include "OpensPower.h"


OpensPower::OpensPower(int offPin)
{
	shutoffPin = offPin;

	interruptPin = -1;
}

/*
Constructor
Parameters:
- offPin: the output pin to use to shut down the device
- intPin: the input pin to use for alarm interrupts when the device
		is already on.
*/
OpensPower::OpensPower(int offPin, int intPin)
{
	//	shutoffPin is used EXCLUSIVELY for turning the device off.
	//	do not repurpose it.
	shutoffPin = offPin;
	
	
	//	input pin for alarm interrupts while the device is on
	interruptPin = intPin;	

}

void OpensPower::begin()
{
	Wire.begin();
	pinMode(shutoffPin, OUTPUT);
	digitalWrite(shutoffPin, LOW);
	getTime();
	Serial.print("Time:\t");	Serial.print(date);Serial.print(':');
								Serial.print(hour);Serial.print(':');
								Serial.print(minute);Serial.print(':');
								Serial.println(second);
	//	initialize and write the status byte 
	getStatus();
	status &= 0B10000100;
	setStatus();

	//	initialize and write the control byte
	getControl();
	control = 0B01000100;
	setControl();

	//	update real time, alarm times
	
	alarm1_getTime();
	alarm2_getTime();

	getTime();
	Serial.print("Time:\t");	Serial.print(date);Serial.print(':');
								Serial.print(hour);Serial.print(':');
								Serial.print(minute);Serial.print(':');
								Serial.println(second);
}

/*

PowerDown
Power down the device by writing shutoffPin HIGH. If the shutoffpin is
not defined, do nothing. If no alarms are activated, turn on alarm1
using the current alarm1 times and set it to trigger when everything
matches.

*/

void OpensPower::powerDown()
{
	if ( shutoffPin < 1 )	//	if the shutoff pin is not defined
	{	Serial.println( "powerdown failed" );
		return;	}

	getControl();			//	get the current control byte

	//	if no alarm is activated, activate alarm1
	if( ( alarm1_state | alarm2_state ) == 0 )
	{
		alarm1_enable(MATCH_DATE);	//	match date, hour, minute, second
	}
	alarm1_getTime();
	Serial.print("Alarm1:\t");	Serial.print(alarm1_date);Serial.print(':');
								Serial.print(alarm1_hour);Serial.print(':');
								Serial.print(alarm1_minute);Serial.print(':');
								Serial.println(alarm1_second);

	clearAlarmFlags();
	Serial.print("Control:\t");	Serial.println(control);
	Serial.print("Status: \t");	Serial.println(status);
	Serial.println("writing shutoffPin HIGH\n\n");
	digitalWrite(shutoffPin, HIGH);	//	turn the device off

}


/*
getTime
Retrieves the current time from the RTC. Century is marked on the MSB
of the month byte.

*/

void OpensPower::getTime()
{
	uint8_t temp_byte = 0;

	Wire.beginTransmission(address);
	Wire.write(0x00);
	Wire.endTransmission();
	Wire.requestFrom( address, 7 );
	second = Wire.read();
	minute = Wire.read();
	hour = Wire.read();
	day = Wire.read();
	date = Wire.read();
	month = Wire.read();
	year = Wire.read();
	Wire.endTransmission();

	century = month & 	0B10000000;	//	marked as the MSB of the month byte
	month = month & 	0B01111111;	//	get rid of the century bit

	second = (second & 15 ) + ( second >> 4 ) * 10;
	minute = (minute & 15 ) + ( minute >> 4 ) * 10;
	hour = (hour & 15 ) + ( hour >> 4 ) * 10;
	date = (date & 15 ) + ( date >> 4 ) * 10;
	month = (month & 15 ) + ( month >> 4 ) * 10;
	year = (year & 15 ) + ( year >> 4 ) * 10;

	

}

/*
getStatus
gets the status byte from the RTC. Status stores conditions such as
the lostPower flag, the busy flag, the enable32kHz bit, and the alarm
flags.
*/
void OpensPower::getStatus()
{

	//get the raw status byte
	Wire.beginTransmission(address);
	Wire.write(0x0F);
	Wire.endTransmission();
	Wire.requestFrom( address, 1 );
	status = Wire.read();
	Wire.endTransmission();

	//	we only use these conditions
	alarm1_flag = ( status>>1 ) & 1;
	alarm2_flag = ( status ) & 1;

	//	and this setting
	lostPower = (status >> 7 ) & 1;
}

void OpensPower::setStatus()
{
	Wire.beginTransmission( address );
	Wire.write( 0x0F );
	Wire.write( status );
	Wire.endTransmission();
}

/*
getControl
Same as getStatus but the control byte stores settings.
*/

void OpensPower::getControl()
{
	//	get the raw control byte
	Wire.beginTransmission(address);
	Wire.write(0x0E);
	Wire.endTransmission();
	Wire.requestFrom( address, 1 );
	control = Wire.read();
	Wire.endTransmission();

	//	only these need to be updated
	alarm1_state = ( control ) & 1;
	alarm2_state = ( control >> 1 ) & 1;
}

void OpensPower::setControl()
{
	Wire.beginTransmission( address );
	Wire.write( 0x0E );
	Wire.write( control );
	Wire.endTransmission();
}


/*
Alarm1 getTime
Gets the date, hour, minute, second that alarm1 will trigger. Updates
the variables that hold this information.
*/
void OpensPower::alarm1_getTime()
{
	Wire.beginTransmission(address);
	Wire.write(0x07);
	Wire.endTransmission();

	Wire.requestFrom( address, 4 );
	alarm1_second = Wire.read();
	alarm1_minute = Wire.read();
	alarm1_hour = Wire.read();
	alarm1_date = Wire.read();
	Wire.endTransmission();

	alarm1_second &= 0B01111111;
	alarm1_minute &= 0B01111111;
	alarm1_hour &= 0B01111111;
	alarm1_date &= 0B01111111;

	alarm1_second = (alarm1_second & 15 ) + ( alarm1_second >> 4 ) * 10;
	alarm1_minute = (alarm1_minute & 15 ) + ( alarm1_minute >> 4 ) * 10;
	alarm1_hour = (alarm1_hour & 15 ) + ( alarm1_hour >> 4 ) * 10;
	alarm1_date = (alarm1_date & 15 ) + ( alarm1_date >> 4 ) * 10;
	
}


/*
Alarm1 setTime
Sets the Alarm1 time using provided values.
*/


//	Use new minute and second times, but use the current date and hour.
void OpensPower::alarm1_setTime(uint8_t m,
								uint8_t s)
{
	alarm1_setTime(alarm1_date, alarm1_hour, m, s);
}

//	Use new hour, minute, second times, but current date
void OpensPower::alarm1_setTime(uint8_t h,
								uint8_t m,
								uint8_t s)
{
	alarm1_setTime(alarm1_date,h,m,s);
}

//	Use new date, hour, minute, second
void OpensPower::alarm1_setTime(uint8_t d,
								uint8_t h,
								uint8_t m,
								uint8_t s)
{

	//	update the values
	alarm1_date = d;
	alarm1_hour = h;
	alarm1_minute = m;
	alarm1_second = s;

	uint8_t temp_byte = 0;
	// seconds is split like:
	//	bit 4,5,6 = 10 seconds
	//	bit 0,1,2,3 = seconds
	temp_byte = s % 10; // get the first three bits
	//	the remaining amount of seconds are divisible by 10 if we subtract temp_byte from them
	//	so do that, divide by 10 for the 10's place, and shift over to bit 4.
	temp_byte += (( s - temp_byte ) / 10 ) << 4;
	s = temp_byte;

	// now repeat for minutes, hours, date
	temp_byte = m % 10;
	temp_byte += (( m - temp_byte ) / 10 ) << 4;
	m = temp_byte;

	temp_byte = h % 10;
	temp_byte += (( h - temp_byte ) / 10 ) << 4;
	h = temp_byte;

	temp_byte = d % 10;
	temp_byte += (( d - temp_byte ) / 10 ) << 4;
	d = temp_byte;


	//	send the values to the RTC
	Wire.beginTransmission(address);
	Wire.write(0x07);
	Wire.write(s);
	Wire.write(m);
	Wire.write(h);
	Wire.write(d);
	Wire.endTransmission();


}


/*
Alarm1 Enable
Parameters:
- alarmType: choose what needs to match in order to trigger the alarm.
			valid types are:
			EVERY_SECOND
			MATCH_SECONDS
			MATCH_MINUTES
			MATCH_HOURS
			MATCH_DATE

Enables Alarm1 and sets the mask that determines how often to trigger
the alarm.
*/
void OpensPower::alarm1_enable(uint8_t alarmType)
{
	//	get the current alarm time just to be sure. The alarm type
	//	is masked over the alarm times, so we are careful not to
	//	overwrite the desired alarm times.
	alarm1_getTime();

	//	set the correct alarm masks based on the alarm type
	switch( alarmType )
	{
		case EVERY_SECOND:					//	1,1,1,1
			alarm1_second |= 0B10000000;	
			alarm1_minute |= 0B10000000;
			alarm1_hour |= 0B10000000;
			alarm1_date |= 0B10000000;
			break;

		case MATCH_SECONDS:					//	0,1,1,1
			alarm1_second &= 0B01111111;	
			alarm1_minute |= 0B10000000;
			alarm1_hour |= 0B10000000;
			alarm1_date |= 0b10000000;
			break;

		case MATCH_MINUTES:					//	0,0,1,1
			alarm1_second &= 0B01111111;
			alarm1_minute &= 0B01111111;
			alarm1_hour |= 0B10000000;
			alarm1_date |= 0B10000000;
			break;

		case MATCH_HOURS:					//	0,0,0,1
			alarm1_second &= 0B01111111;
			alarm1_minute &= 0B01111111;
			alarm1_hour &= 0B01111111;
			alarm1_date |= 0B10000000;
			break;

		case MATCH_DATE:					//	0,0,0,0
			alarm1_second &= 0B01111111;
			alarm1_minute &= 0B01111111;
			alarm1_hour &= 0B01111111;
			alarm1_date &= 0B01111111;
			break;

		default:
			break;
	}

	//	write the masks to the RTC
	alarm1_setTime( alarm1_date, alarm1_hour, alarm1_minute, alarm1_second );
	
	//	get the control byte and make sure only alarm1 is enabled
	//	and the alarm flags are transparent to the INT/SQW pin.
	getControl();
	control |= 1;
	control &= (~2);
	control |= 4;

	//	write the correct settings
	setControl();
}

//	same as alarm1_getTime but without seconds.
void OpensPower::alarm2_getTime()
{
	Wire.beginTransmission(address);
	Wire.write(0x0B);
	alarm2_minute = Wire.read();
	alarm2_hour = Wire.read();
	alarm2_date = Wire.read();
	Wire.endTransmission();
}

void OpensPower::alarm2_setTime(uint8_t h,
								uint8_t m)
{
	alarm2_setTime(alarm2_date, h, m);
}

void OpensPower::alarm2_setTime(uint8_t m)
{
	alarm2_setTime(alarm2_date, alarm2_hour, m);
}

void OpensPower::alarm2_setTime(uint8_t d,
								uint8_t h,
								uint8_t m)
{
	Wire.beginTransmission(address);
	Wire.write(0x0B);
	Wire.write(m);
	Wire.write(h);
	Wire.write(d);
	Wire.endTransmission();

	alarm2_minute = m;
	alarm2_hour = h;
	alarm2_date = d;
}

void OpensPower::alarm2_enable(uint8_t alarmType)
{
	alarm1_getTime();

	switch( alarmType )
	{
		case EVERY_MINUTE:
			alarm2_minute |= 0B10000000;
			alarm2_hour |= 0B10000000;
			alarm2_date |= 0B10000000;
			break;

		case MATCH_MINUTES:
			alarm2_minute &= 0B01111111;
			alarm2_hour |= 0B10000000;
			alarm2_date |= 0b10000000;
			break;

		case MATCH_HOURS:
			alarm2_minute &= 0B01111111;
			alarm2_hour &= 0B01111111;
			alarm2_date |= 0B10000000;
			break;

		case MATCH_DATE:
			alarm2_minute &= 0B01111111;
			alarm2_hour &= 0B01111111;
			alarm2_date &= 0B01111111;
			break;

		default:
			break;
	}
	alarm2_setTime( alarm2_date, alarm2_hour, alarm2_minute );
	
	getStatus();
	status |= 2;
	status &= (!1);
	status |= 4;
	setStatus();
}


/*
Squarewave
Sets the INT/SQW pin to output a squarewave with the designated frequency.
Alarms are not transparent to the INT pin until they are set again.
*/

void OpensPower::squarewave(uint8_t frequency = SQW_1HZ)
{
	control = 0B01000000;

	switch(frequency)
	{
		case SQW_1KHZ:
			control ^= 0B00001000;
			break;

		case SQW_4KHZ:
			control ^= 0B00010000;
			break;

		case SQW_8KHZ:
			control ^= 0B00011000;
			break;

		default:
			break;
	}

	setControl();
}

//	Attaches an intterupt to the input pin. The user can link a custom ISR
//	by passing a function pointer to the ISR to setInterrupt. The interrupt will
//	trigger when interruptPin falls LOW, so don't mess with the interruptPin until
//	detachInterrupt() is called.
void OpensPower::setInterrupt(void (*userFunction)(void) )
{
	interrupted = false;
	pinMode(interruptPin,INPUT_PULLUP);
	attachInterrupt(interruptPin, *userFunction, FALLING );
}

//	Just a simple ISR that sets a member variable flag to 'true' after detaching
//	interrupts, then exits.
void OpensPower::defaultISR(void)
{
	detachInterrupt( interruptPin );
	interrupted = true;
}


//	disable both alarms. 
void OpensPower::clearAlarms()
{
	control &= 0B11111100;
	setControl();
}

//	check which alarms have been triggered. Useful if you aren't using interrupts.
//	Returns:
//	0: no alarms have triggered
//	1: alarm 1 triggered
//	2: alarm 2 triggered
//	3: both alarms triggered
uint8_t OpensPower::checkAlarmFlags()
{
	getStatus();
	return ( status & 3 );
}

//	clear the alarm flag bits in the status register
void OpensPower::clearAlarmFlags()
{
	getStatus();
	status &= 0B11111100;
	setStatus();
}

void OpensPower::setTime(	uint8_t yr,
							uint8_t mo,
							uint8_t dy,
							uint8_t	hr,
							uint8_t	mi,
							uint8_t	sc)
{

	uint8_t temp_byte = 0;
	// seconds is split like:
	//	bit 4,5,6 = 10 seconds
	//	bit 0,1,2,3 = seconds
	temp_byte = sc % 10; // get the first three bits
	//	the remaining amount of seconds are divisible by 10 if we subtract temp_byte from them
	//	so do that, divide by 10 for the 10's place, and shift over to bit 4.
	temp_byte += (( sc - temp_byte ) / 10 ) << 4;
	sc = temp_byte;

	// now repeat for minutes, hours, date
	temp_byte = mi % 10;
	temp_byte += (( mi - temp_byte ) / 10 ) << 4;
	mi = temp_byte;

	temp_byte = hr % 10;
	temp_byte += (( hr - temp_byte ) / 10 ) << 4;
	hr = temp_byte;

	temp_byte = dy % 10;
	temp_byte += (( dy - temp_byte ) / 10 ) << 4;
	dy = temp_byte;

	temp_byte = mo % 10;
	temp_byte += (( mo - temp_byte ) / 10 ) << 4;
	mo = temp_byte;

	temp_byte = yr % 10;
	temp_byte += (( yr - temp_byte ) / 10 ) << 4;
	yr = temp_byte;


	Wire.beginTransmission( address );
	Wire.write( 0x00 );		//	seconds address
	Wire.write( sc );		//	seconds
	Wire.write( mi );		//	minutes
	Wire.write( hr );		//	hours
	Wire.write( 0 );		//	weekday
	Wire.write( dy );		//	day of month
	Wire.write( mo | ( century << 7 ) );		//	month with century mask
	Wire.write( yr );		//	year
	Wire.endTransmission();

	getTime();
}

void OpensPower::alarm1_SetTime_Offset( uint32_t alm_offset )
{
	getTime();

	alm_offset = 	alm_offset +
					second +
					minute * 60 +
					hour * 3600 +
					date * 86400;

	alarm1_second = alm_offset % 60;
	alm_offset -= alarm1_second;

	alarm1_minute = ( alm_offset % 3600 ) / 60;
	alm_offset -= alarm1_minute * 60;

	alarm1_hour = ( alm_offset % 86400 ) / 3600;
	alm_offset -= alarm1_hour * 3600;

	alarm1_date = alm_offset / 86400;



	alarm1_setTime( alarm1_date, alarm1_hour, alarm1_minute, alarm1_second );

}
















