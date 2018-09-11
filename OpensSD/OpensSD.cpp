#include "OpensSD.h"

OpensSD::OpensSD( int CS )
{
	chipSelect = CS;
	for(uint8_t i = 0; i < bufferSize; i++ )
	{
		buffer[i] = 0;
	}
	for( uint8_t i = 0; i < bufferBSize; i++)
	{
		bufferB[i] = 0;
	}
	firstCycle = true;
}

int8_t OpensSD::begin()
{
	//	Hardware Chip Select needs to be output and high for SD chip select to work
	pinMode( 8, OUTPUT );
  	digitalWrite( 8, HIGH );
	SD.begin( chipSelect );

	// check for "Data.txt"
	//	clear the buffer and then copy over the settings filename.
	memset(buffer, 0, sizeof(buffer));
	strncpy_P(buffer, STRING_TABLE[0], sizeof( buffer ) - 1);
	//	if the file doesn't exist, make it
	if( !SD.exists( buffer ) )
	{
		File f = SD.open( buffer, FILE_WRITE );
		Serial.print("isDir: ");Serial.println( f.isDirectory() );
		Serial.print(buffer);Serial.print(" Opened: "); Serial.println( f );
		f.close();
	}

	//	check for "Settings.txt"
	//	clear the buffer and then copy over the settings filename.
	memset(buffer, 0, sizeof(buffer));
	strcpy_P(buffer, STRING_TABLE[1] );

	//	if the file doesn't exist, make it
	if( !SD.exists( buffer ) )
	{
		File f = SD.open( buffer, FILE_WRITE );
		Serial.print(buffer);Serial.print(" Opened: "); Serial.println( f );
		f.close();
	}

	return checkSettingsFile();
}


/*
Mark New Date

Create a date marker on the data file. This function should
be called every time the date changes. The order of day, month, and year
are determined by DATE_MARKER, defined in the header.

Parameters:
- year: two digit year
- month: two digit month
- date: two digit date representing the day of the month (1-31)
*/
int8_t OpensSD::markNewDate(uint8_t year, uint8_t month, uint8_t date)
{
	//	clear the buffer and then copy over the settings filename.
	memset(buffer, 0, sizeof(buffer));
	strcpy_P(buffer, STRING_TABLE[0] );
	
	File f = SD.open( buffer, FILE_WRITE);	//	close requires the file object f

	if( f == false )
	{	//	file not opened
		return 1;
	}

	//	clear the buffer and prepare the date string based on the format
	//	defined by DATE_MARKER
	memset(buffer, 0, sizeof(buffer));
	switch( DATE_MARKER )
	{
		case DAY_MONTH_YEAR:
		//	delimiters are used because this will be formatted like any other keyvalue.
		//	to find certain dates in the file, the DATE key can be searched for.
			sprintf_P(	buffer,
						STRING_TABLE[5],
						delimiter1,
						date, month, year,
						delimiter2 );
			break;

		case YEAR_MONTH_DAY:
			sprintf_P(	buffer,
						STRING_TABLE[5],
						delimiter1,
						year, month, date,
						delimiter2 );
			break;

		case MONTH_DAY_YEAR:
			sprintf_P(	buffer,
						STRING_TABLE[5],
						delimiter1,
						month, date, year,
						delimiter2 );
			break;
	}

	//	write the string to the file, then close it.
	f.print(buffer);
	f.close();

	return 0;
}


/*
Check Settings File

Scans the settings file on the SD card for keyvalue settings. Every setting
that is found is added to the local settings list. If no file exists, this function
creates one.

Returns:
0: no settings found, file was empty or was created.
Positive Integer: number of settings added
-1: timeout reached

*/
int8_t OpensSD::checkSettingsFile()
{
	//	only call in the main program's setup.
	//	copy over "Settings.txt" to the buffer
	memset( buffer, 0, sizeof( buffer ) );
	strncpy_P( buffer, STRING_TABLE[1],  sizeof(buffer) );
	Serial.print("[CSF] Settings.txt: ");Serial.println( buffer );

	//	if the settings file doesn't exist, create it and return 0
	//	since there aren't any settings to be found.
	if( !SD.exists( buffer ) )
	{
		Serial.print("[CSF] buffer: "); Serial.println( buffer );
		Serial.println( "[CSF] Settings not found." );
		File f = SD.open( buffer, FILE_READ);
		Serial.print("[CSF] Open settings file: "); Serial.println( f );
		f.close();
		firstCycle = true;

		#if SD_DEBUG == 1
			memset(error_buffer, 0, sizeof(error_buffer) );
			strcpy_P( error_buffer, ERROR_TBL[0] );
			Serial.println( error_buffer );

		#endif
		return 0;
	}
	Serial.println( "[CSF] Settings file found.");
	File f = SD.open( buffer, FILE_READ );
	Serial.print( "[CSF] File Open: "); Serial.println( f );
	Serial.print( "[CSF] Size: "); Serial.println( f.size() );
	Serial.println( "[CSF] SETTINGS FILE: ");
	Serial.println( "***********************************************************" );
	while( f.available() )
	{
		Serial.print( uint8_t ( f.read() ) );
		Serial.print( ' ' );
	}

	Serial.println();
	Serial.println( "***********************************************************" );

	f.seek(0);
	
	//	create a new blank setting at the end of the list
	//	and keep track of the current setting with kv_ptr
	OpensSD::KeyValue* kv_ptr = settings.add();

	uint8_t maxSize = (settings.head)->max_size;
	uint8_t numSettings = 0;
	uint8_t index = 0;
	uint32_t timeout = millis();
	while( f.available() )	//	read the whole file
	{
		if( ( millis() - timeout ) > SD_TIMEOUT )
		{

			#if SD_DEBUG == 1
				memset(error_buffer, 0, sizeof(error_buffer) );
				strcpy_P( error_buffer, ERROR_TBL[1] );
				Serial.println( error_buffer );
			#endif

			return -1;	//	timeout error
		}

		//	read the next character
		char c = f.read();

		switch( c )
		{
			case delimiter1:

			//	the read char is separating a key and its value
				(kv_ptr->key)[index] = 0;	//	terminate the string
				Serial.print("[CSF] Key: ");Serial.println( kv_ptr->key );
				index = maxSize;
				break;

			case delimiter2:
			//	the read char is marking the end of a keyvalue pair.
			//	Add a blank keyvalue object to the settings array, reset the
			//	current setting object and index, and continue.
				(kv_ptr->val)[index - maxSize] = 0;
				Serial.print("[CSF] Val: ");Serial.println( kv_ptr->val );
				Serial.print("Key first char: "); Serial.println((uint8_t)( kv_ptr->key[0] ) );
				if( kv_ptr->key[0] != 0 && kv_ptr->key[0] != 13 )
				{
					Serial.println("[CSF] added.");
					kv_ptr = settings.add();	//	this will move 'last' as well
					numSettings++;
				}
				index = 0;			
				break;

			default:
				if( c == '\n' )
				{
					break;
				}
			//	the character is part of a setting member and the index
			//	will not overflow the alotted size of keyval members.
				if( index < maxSize-1 )	//	space for a terminator
				{	//	key
					kv_ptr->key[index] = c;

					//	the next char is always a terminator
					kv_ptr->key[index+1] = 0;
				}
				else if( maxSize < index < 2*maxSize - 1 )	//	space for a terminator
				{	//	value
					kv_ptr->val[index - maxSize] = c;

					//	the next char is always a terminator
					kv_ptr->val[index - maxSize + 1] = 0;	
				}
				index++;
				break;
		}
	}

	f.close();	//	close the file

	if( numSettings > 0 )
	{
		firstCycle = false;
	}

	#if SD_DEBUG == 1
		memset(error_buffer, 0, sizeof(error_buffer) );
		sprintf_P( error_buffer, ERROR_TBL[2], numSettings );
		Serial.println( error_buffer );
	#endif
	Serial.println("Local Settings: ");
	printLocalSettings();
	printSavedSettings();

	return numSettings;	//	return the number of settings that were added

}


/*
Add A KeyValue to a List
Possible parameters:
- void to add a blank keyvalue
- key to add a keyvalue with a key but no value
- key and val to add a keyvalue with both

Returns:
A pointer to the last KeyValue object in the list, even if a keyvalue
matching the user defined key was found elsewhere in the list.
*/

OpensSD::KeyValue* OpensSD::KeyValueList::add( char* key, char* value)
{
	Serial.print("[KV ADD] Key: "); Serial.print( key ); Serial.print("\t Val: "); Serial.println( value );

	if( head == nullptr )
	{
		Serial.println("[KV ADD] Head is nullptr, creating new keyvalue.\n");
		head = new KeyValue( key, value );
		last = head;
		Serial.print("[KV ADD] Head's next key: "); Serial.println( (head->next)->key );
		return last;
	}
	else
	{
		KeyValue* kv_ptr = get( key );
		if( kv_ptr == nullptr )
		{
			kv_ptr = get( "" );
			if( kv_ptr == head )
			{
				Serial.println("[KV ADD] Head is empty, inserting keyvalue.");
				//	head is empty and no matching key was found, add kv to head
				memset( head->key, 0, head->max_size );
				memset( head->val, 0, head->max_size );
				strncpy( head->key, key, head->max_size );
				strncpy( head->val, value, head->max_size );
				return last;
			}
			else if( kv_ptr == nullptr )
			{	//	no blank kvs
				Serial.println("[KV ADD] appending new keyvalue.");
				last->next = new KeyValue( key, value );
				Serial.print("[KV Add] Previous Last Key: ");Serial.println( last->key );
				last = last->next;
				if( last == nullptr )
				{
					Serial.println( "last is nullptr!!");
				}
				Serial.print("[KV Add] New Last Key: "); Serial.println( last->key );Serial.println();
				return last;
			}
			else if( kv_ptr != nullptr )
			{
				Serial.println("[KV ADD] Found blank key. Overwriting.");
				memset( kv_ptr->key, 0, kv_ptr->max_size );
				memset( kv_ptr->val, 0, kv_ptr->max_size );
				strncpy( kv_ptr->key, key, kv_ptr->max_size );
				strncpy( kv_ptr->val, value, kv_ptr->max_size );
				return last;

			}
		}
		else
		{
			Serial.println("[KV ADD] key already exists. Overwriting value.\n");
			memset( kv_ptr->val, 0, kv_ptr->max_size );
			strncpy( kv_ptr->val, value, kv_ptr->max_size );
			return last;
		}
		
	}
}

/*
Get a KeyValue from a List
Parameters:
- key string to look for
Returns:
- KeyValue pointer to object that was found
- Nullptr if not found
*/
OpensSD::KeyValue* OpensSD::KeyValueList::get( char* key )
{
	OpensSD::KeyValue* kv_ptr = head;
	while( kv_ptr != nullptr )
	{
		if( strlen( key ) == strlen(kv_ptr->key) )
		{
			uint8_t minLen = min( strlen(key), kv_ptr->max_size );
			if( strncmp( key, kv_ptr->key, minLen ) == 0 )
			{
				return kv_ptr;
			}
		}
		kv_ptr = kv_ptr->next;
	}
	return nullptr;
}

/*
Destructor
Usually not used since the OpensSD object should be initialized outside
the main loop and when the device turns off it clears its SRAM. This is
just here in case someone wants to modify the library to use KeyValueLists
elsewhere.
*/

OpensSD::KeyValueList::~KeyValueList()
{
	OpensSD::KeyValue* ptr = head;
	while( ptr != nullptr )
	{
		OpensSD::KeyValue* trash = ptr;
		ptr = ptr->next;
		delete trash;
	}
}

/*
Save Local Settings to the SD Card

Stores the objects from the settings KeyValueList in Settings.txt
on the SD card.

*/

uint8_t OpensSD::saveSettings()
{
	//	clear the buffer and then copy over the settings filename.
	memset(buffer, 0, sizeof(buffer));
	strcpy_P(buffer, STRING_TABLE[1] );


	//	if the file has already been made, delete it so we can write a new one
	if( SD.exists( buffer ) )
	{
		SD.remove( buffer );
	}
	Serial.print("[SS] Buffer: "); Serial.println( buffer );
	//	make the new file and open it
	File f = SD.open( buffer, FILE_WRITE );
	if( f == false )
	{
		#if SD_DEBUG == 1
			memset(error_buffer, 0, sizeof(error_buffer) );
			strcpy_P( error_buffer, ERROR_TBL[6], value );
			Serial.println( error_buffer );
		#endif

		return 1;	//	file failed to open
	}

	//	cycle through all the keyvalues in the settings list and print them
	//	to the file, separated by delimiter1 and delimiter2.
	OpensSD::KeyValue* kv_ptr = settings.head;
	while( kv_ptr != nullptr )
	{
		Serial.print("[SS] Adding key: "); Serial.println( kv_ptr->key );
		//	write the key
		f.write(kv_ptr->key, strlen( kv_ptr->key ) );
		//	write the key and value separator
		f.write(delimiter1);

		Serial.print("[SS] Adding Val: "); Serial.println( kv_ptr->val );
		//	write the value
		f.write(kv_ptr->val, strlen( kv_ptr->val ) );
		//	write the KeyValue separator
		f.write(delimiter2);
		//	get the next KeyValue object
		kv_ptr = kv_ptr->next;	
	}
	#if SD_DEBUG == 1
		memset(error_buffer, 0, sizeof(error_buffer) );
		strcpy_P( error_buffer, ERROR_TBL[7], value );
		Serial.println( error_buffer );
	#endif
	f.println();

	f.close();	//	close the file

	Serial.println("[SS] FILE CONTENTS: ");
	f = SD.open( buffer, FILE_READ );
	while( f.available() )
	{
		Serial.print( (uint8_t) f.read() );
		Serial.print(' ');
	}
	Serial.println();



	return 0;
}


OpensSD::KeyValue* OpensSD::getKVListValue( char* key, char** value, KeyValueList* kvList)
{
	//	iterator
	OpensSD::KeyValue* kv_ptr = kvList->head;

	//	cycle through the settings list, checking the given key string
	while(kv_ptr != nullptr )
	{
		//	in case the setting key is not terminated, check for the minimum between
		//	the string size and the max member size
		uint8_t min_size = min( kv_ptr->max_size , strlen(key) );
		int cmp = strncmp( kv_ptr->key, key, min_size );

		//	if the setting was found, store its value as a string in the passed
		//	character pointer 'value'
		if( cmp == 0 )
		{
			
			#if SD_DEBUG == 1
				memset(error_buffer, 0, sizeof(error_buffer) );
				snprintf_P( error_buffer, ERROR_TBL[8],
							kv_ptr->key,
							delimiter1,
							kv_ptr->val,
							delimiter2 );
				Serial.println( error_buffer );
			#endif

			*value = kv_ptr->val;

			return kv_ptr;
		}
		kv_ptr = kv_ptr->next;
	}

	#if SD_DEBUG == 1
		memset( error_buffer, 0, sizeof( error_buffer ) );
		strcpy_P( error_buffer, ERROR_TBL[9] );
		Serial.println( error_buffer );
	#endif

	return nullptr;	//	failed
}


void OpensSD::addSetting( char* k)
{
	addSetting( k, "" );
}

void OpensSD::addSetting( char* key, char* value )
{
	settings.add( key, value );
}

void OpensSD::addDataPoint( char* key, char* value )
{
	variables.add( key, value );
}

uint8_t OpensSD::getSetting(char* key, char* value)
{
	char* val;
	if( getKVListValue( key, &val, &settings ) == nullptr )
	{
		#if SD_DEBUG == 1
			memset( error_buffer, 0, sizeof( error_buffer ) );
			strcpy_P( error_buffer, ERROR_TBL[9] );
			Serial.println( error_buffer );
		#endif
		return 1;
	}
	strcpy( value, val );
	Serial.print("[GS] TEMPVAL: "); Serial.println( val );
	Serial.print("[GS] USERVAL: "); Serial.println( value );
	return 0;

}

void OpensSD::printLocalSettings()
{
	settings.print();
}

void OpensSD::printSavedSettings()
{
	//	clear the buffer and then copy over the settings filename.
	memset(buffer, 0, sizeof(buffer));
	strcpy_P(buffer, STRING_TABLE[1] );
	Serial.print("[save] buffer: "); Serial.println( buffer );

	//	make the new file and open it
	File f = SD.open( buffer, FILE_READ );
	Serial.println("FILE CONTENTS:");
	
	while( f.available() > 0 )
	{
		Serial.print( char( f.read() ) );
	}
	Serial.println();
	f.close();

}

uint8_t OpensSD::saveData()
{
	//	clear the buffer and then copy over the settings filename.
	memset(buffer, 0, sizeof(buffer));
	strcpy_P(buffer, STRING_TABLE[0] );

	Serial.print("[SAVEDATA] BUFFER: "); Serial.println( buffer );
	File f = SD.open( buffer, FILE_WRITE );	//	close requires the file object f

	if( f == false )
	{	//	file not opened
		#if SD_DEBUG == 1
			memset( error_buffer, 0, sizeof( error_buffer ) );
			strcpy_P( error_buffer, ERROR_TBL[6] );
			Serial.println( error_buffer );
		#endif
		return 1;
	}
	//	cycle through all the keyvalues in the settings list and print them
	//	to the file, separated by delimiter1 and delimiter2.
	OpensSD::KeyValue* kv_ptr = variables.head;
	while( kv_ptr != nullptr )
	{
		f.write(kv_ptr->key, min( strlen(kv_ptr->key), kv_ptr->max_size));
		f.write(delimiter1);
		f.write(kv_ptr->val, min( strlen(kv_ptr->val), kv_ptr->max_size));
		f.write(delimiter2);

		kv_ptr = kv_ptr->next;	
	}
	f.write('\n');
	f.close();	//	close the file

	Serial.println("DATA CONTENTS: ");
	Serial.println("**********************************");
	f = SD.open( buffer, FILE_READ );
	while( f.available() )
	{
		Serial.print( (char) f.read() );
	}
	Serial.println();
	Serial.println("**********************************");
	return 0;
}

uint8_t OpensSD::saveData( char* dataString)
{
	// clear the buffer and then copy over the settings filename.
	memset(buffer, 0, sizeof(buffer));
	strcpy_P(buffer, STRING_TABLE[0] );

	File f = SD.open( buffer, FILE_WRITE );

	if( f == false )
	{
		#if SD_DEBUG == 1
			memset( error_buffer, 0, sizeof( error_buffer ) );
			strcpy_P( error_buffer, ERROR_TBL[6] );
			Serial.println( error_buffer );
		#endif
		return 1;
	}

	f.print( dataString );
	f.print('\n');

	f.close();
	return 0;
}

/*
Get the position in the sd file of the start of the line AFTER a matching key
AND value are found. This is most useful for getting the data after a specific
timestamp, such as the OpensSD's date stamp. For getting more granular data,
getValueAfter() could be called using the index of getPosition.
*/


int32_t OpensSD::getPosition( char* key, char* value , uint32_t startPosition)
{

	Serial.print("[GP] KEY: "); Serial.println( key );
	Serial.print("[GP] VAL: "); Serial.println( value );
	// clear the buffer and then copy over the settings filename.
	memset(buffer, 0, sizeof(buffer));
	strcpy_P(buffer, STRING_TABLE[0] );

	//	if the file doesn't exist, return -1
	if( !SD.exists( buffer ) )
	{
		#if SD_DEBUG == 1
			memset( error_buffer, 0, sizeof( error_buffer ) );
			strcpy_P( error_buffer, ERROR_TBL[11] );
			Serial.println( error_buffer );
		#endif
		return -1;
	}

	File f = SD.open( buffer, FILE_READ );

	if( f == false )
	{	//	if the file wasn't opened, return -2
		#if SD_DEBUG == 1
			memset( error_buffer, 0, sizeof( error_buffer ) );
			strcpy_P( error_buffer, ERROR_TBL[6] );
			Serial.println( error_buffer );
		#endif
		return -2;
	}

	f.seek(startPosition);
	uint32_t position = startPosition;
	uint32_t timeout = millis();
	Serial.println("[GP] PARSING FILE...");

	while( f.available() )
	{
		//	first timeout check so we don't get stuck in while loop
		if( (millis() - timeout ) > SD_TIMEOUT )
		{
			#if SD_DEBUG == 1
				memset( error_buffer, 0, sizeof( error_buffer ) );
				strcpy_P( error_buffer, ERROR_TBL[1] );
				Serial.println( error_buffer );
			#endif
			return 1;
		}

		//	read in the first character
		char c = f.read();
		

		if( c == 10 || f.position() == 0 )
		{	//	we're only interested in the start of a key

			//	comparison is used to compare the desired key and the key that is read in
			bool comparison = true;
			position = f.position();


			//	since we've started a key, read until they don't compare or we've
			//	reached the end of the desired key
			for( int i=0; i < strlen(key); i++ )
			{
				//	read in the next character
				c = f.read();
				while( c == 10 )
				{
					c = f.read();
				}
				Serial.print("[GP] File Char: ");Serial.print( (uint8_t) c );
				Serial.print("\t[GP] Key Char: "); Serial.println( (uint8_t) key[i] );

				Serial.print("[GP] pos: ");Serial.println( f.position() );

				//	if the key character doesn't compare true, set comparison to false
				//	and go back to checking for another KeyValue separator.
				if ( ((char) key[i]) != c )
				{
					Serial.println("[GP] false");
					comparison = false;
					break;
				}
			}
			Serial.println( f.read() );	//	skip the delimiter between the key and value
			
			//	if comparison is still true then continue.
			if( comparison == true )
			{
				if( value[0] == 0 || value[0] == 255 )
				{
					return position;
				}
				Serial.println("[GP] true!");

				//	check if the values match. They won't match if we had querried, for example,
				//	"temp" but both "temp" and "temp2" exist, because we'll read in a character from
				//	the name or a delimiter here rather than the value string.
				for( int i=0; i < strlen( value ); i++ )
				{
					c = f.read();

					Serial.print("[GP] File Char: ");Serial.print( (uint8_t) c );
					Serial.print("\t[GP] Val Char: "); Serial.println( (uint8_t) value[i] );

					//	if the values don't match, go back to checking for a KeyValue delimiter.
					if( (char)(value[i]) != c )
					{
						Serial.println("[GP] false");
						comparison = false;
						break;
					}
				}	
			}
			
			if( comparison == true )
			{
				Serial.println("[GP] TRUE!");
				//	skip to the newline separating the datestamp from the
				//	start of the day's data
				while( 	c != '\n' &&
						f.available() > 0)
				{
					c = f.read();
				}
				if( c == '\n' )
				{
					return position;	//return the position of the day's data
				}
			}
		}
	}

	return 0;
}

int32_t OpensSD::getAfterDate(	uint8_t year, uint8_t month, uint8_t date,
								bool (*userFunction)(char) )
{
	return getBetweenDates(year, month, date, 0,0,0, userFunction);
}

/*
Get Between Dates

Parameters:
- year1/month1/date1: year, month, and day of the month to start
- year2/...: year, month, day of the month to end
- *userFunction: pointer to function that accepts a character and returns a boolean

This function takes a date to start and end, then passes each individual byte from the data
file between these dates to a user defined function, userFunction. This allows each project
using this library to pass however much data they want using whatever protocol they desire. The
Smart Rock, for example, will use bluetooth to send data but also can pass data through
Serial Comms to debug.

Example userFunction using
getBetweenDates(y1,m1,d1,y2,m2,d2, &myFunction )

bool myFunction(char c)
{
	if(Serial)
	{
		print( c );
		return true;
	}
	return false;
}'

Returns:
positive integer: number of bytes that were passed to userFunction
-1:	data file doesn't exist
-2: data file couldn't be opened

negative integer < -10: -10 minus number of bytes that were passed to userfunction before it
				stopped accepting bytes.

*/
int32_t OpensSD::getBetweenDates(	uint8_t year1, uint8_t month1, uint8_t date1,
									uint8_t year2, uint8_t month2, uint8_t date2,
									bool (*userFunction)(char) )
{
	memset(bufferB, 0, sizeof(bufferB));	//	clear the buffer


	//	based on DATE_MARKER, we'll change the format of the date stamp we are looking for
	//	it's formatted as "var1:var2:var3"
	switch( DATE_MARKER )
	{
		default: //DAY_MONTH_YEAR
			snprintf_P(	bufferB,
						sizeof(bufferB),
						STRING_TABLE[3],
						date1, month1, year1 );
			break;

		case YEAR_MONTH_DAY:
			snprintf_P(	bufferB,
						sizeof(bufferB),
						STRING_TABLE[3],
						year1, month1, date1 );
			break;

		case MONTH_DAY_YEAR:
			snprintf_P(	bufferB,
						sizeof(bufferB),
						STRING_TABLE[3],
						month1, date1, year1 );
			break;
	}

	//	get the starting index where a match between the DATE flag's value
	//	and the provided date is found
	int32_t indexStart = getPosition( "DATE", bufferB );

	memset(bufferB, 0, sizeof(bufferB));	//	clear the buffer

	int32_t indexEnd = 0;
	if( month2 != 0 && date2 != 0 ) 
	{
		//	do the same thing but for the end date, if it is provided.
		//	Year can be equal to 0 so we don't check that looking for
		//	if the user specified an end date.
		switch( DATE_MARKER )
		{
			default: //DAY_MONTH_YEAR
				snprintf_P(	bufferB,
							sizeof(bufferB),
							STRING_TABLE[3],
							date2, month2, year2 );
				break;

			case YEAR_MONTH_DAY:
				snprintf_P(	bufferB,
							sizeof(bufferB),
							STRING_TABLE[3],
							year2, month2, date2 );
				break;

			case MONTH_DAY_YEAR:
				snprintf_P(	bufferB,
							sizeof(bufferB),
							STRING_TABLE[3],
							month2, date2, year2 );
				break;
		}

		indexEnd = getPosition( "DATE", bufferB );
	}

	//	get the data file name
	memset( buffer, 0, sizeof(buffer) );
	strncpy_P( buffer, STRING_TABLE[0], sizeof(buffer) );

	//	if the file doesn't exist, return -1
	if( !SD.exists( buffer ) )
	{
		return -1;
	}

	File f = SD.open( buffer );

	if( f == false )
	{	//	if the file wasn't opened, return -2
		return -2;
	}
	if( indexEnd == 0 )
	{
		indexEnd = f.size();
	}

	//	skip to the start date
	f.seek( indexStart );

	uint32_t timeout = millis();


	//	if userfunction returns false, that means there is no point in passing
	//	more data because it doesn't want any more.
	bool stopSending = false;

	//	counter for number of characters we've read
	uint32_t numChars = 0;

	while( 	f.available() &&				//	bytes are available to read from the file
			stopSending == false &&				//	stopSending hasn't been flagged
			indexEnd - f.position() > 0)	//	the end index hasn't been reached
	{
		//	first timeout check so we don't get stuck in while loop
		if( (millis() - timeout ) > SD_TIMEOUT )
		{
			return 1;
		}

		//	to speed things up, only check f.position() once every hundred
		//	reads until we are closer to the end index
		if( indexEnd - f.position() > 100 )
		{
			for( int i=0; i < 100; i++ )
			{
				//	read a character 100 times or until userFunction returns false
				if( (*userFunction)( f.read() ) == false )
				{
					stopSending = true;
					numChars++;	//	we've read a character regardless of userFunction's return
					break;
				}
			}
		}
		else
		{
			// close to the end index. Read one byte at a time and check the return.
			if( (*userFunction)( f.read() ) == false )
			{
				stopSending = true;
				
			}
			numChars++;	//	we've read a character regardless of userFunction's return
		}
	}


	//	if the userfunction ever returned false, return -numChars.
	//	this will return a useless value (possibly a different error code)
	//	if in32t overflows but would require passing 2GB of data within SD_TIMEOUT's duration.
	//	the -10 offset is there to allow room for more error codes.
	if( stopSending == true )
	{
		return ( int32_t(numChars) * -1 ) - 10;
	}

	return numChars;	//	

}


int16_t OpensSD::getBlockAfter( char* storage, uint16_t size , uint32_t index )
{
	memset( storage, 0, size);
	
	if( !SD.exists( buffer ) )
	{
		return -1;
	}

	File f = SD.open( buffer );

	if( f == false )
	{	//	if the file wasn't opened, return -2
		return -2;
	}

	f.seek(index);

	uint16_t i = 0;
	while( 	f.available() == true &&
			i < size )
	{
		storage[i] = f.read();
		i++;
	}

	f.close();

	return i;

}

int16_t OpensSD::get16_After( char storage[16], uint32_t index )
{
	return getBlockAfter( storage, 16, index );
}

int16_t OpensSD::get64_After( char storage[64], uint32_t index )
{
	return getBlockAfter( storage, 64, index );
}

int16_t OpensSD::get128_After( char storage[128], uint32_t index )
{
	return getBlockAfter( storage, 128, index );
}

int16_t OpensSD::get256_After( char storage[256], uint32_t index )
{
	return getBlockAfter( storage, 256, index );
}

int16_t OpensSD::get512_After( char storage[512], uint32_t index )
{
	return getBlockAfter( storage, 512, index );
}

void OpensSD::printLocalData()
{
	variables.print();
}

int32_t OpensSD::streamLocalData( bool (*userFunction) (char) )
{
	return variables.streamList( userFunction );
}

int16_t OpensSD::streamLocalSettings( bool (*userFunction) (char) )
{
	return settings.streamList( userFunction );
}


/*
Stream A KeyValue List
Passes each character in a keyvalue list to a user defined function, checking that the
function is still accepting characters.

Parameters:
- userFunction Pointer: pointer to user defined function that accepts a character and returns
						a boolean representing its ability to accept another character.

Returns:
Positive Integer: number of characters (numChars) that were passed to userFunction.
Negative Integer < -10: number of characters that were passed to userFunction before it returned
						false, offset by -10.
*/

int16_t OpensSD::KeyValueList::streamList( bool (*userFunction) (char) )
{
	OpensSD::KeyValue* kv_ptr = head;

	int32_t numChars = 0;
	while( kv_ptr != nullptr )	//	while there are more keyvalue objects
	{

		//	for each character in the keyvalue object's key string,
		//	pass it to userFunction.
		for(uint8_t i = 0;
			i < strnlen( kv_ptr->key, kv_ptr->max_size );
			i++ )
		{

			//	if userFunction returns false, it has stopped accepting
			//	characters. Return -numCharacters offset by -10 to allow
			//	for error codes.
			if( (*userFunction)( kv_ptr->key[i] ) == false )
			{
				return -10 - numChars;
			}
			numChars++;
		}

		//	pass it the delimiter so it can understand a transition from
		//	key to value
		if( (*userFunction)( delimiter1 ) == false )
		{
			return -10 - numChars;
		}
		numChars++;

		//	for each character in the keyvalue object's value string,
		//	pass it to userFunction and check that it is still accepting
		//	characters.
		for( uint8_t i = 0;
			i < strnlen( kv_ptr->val, kv_ptr->max_size );
			i++ )
		{
			if( (*userFunction)( kv_ptr->val[i] ) == false )
			{
				return -10 - numChars;
			}
			numChars++;
		}

		//	pass it the keyvalue delimiter
		if( (*userFunction)( delimiter2 ) == false )
		{
			return -10 - numChars;
		}

		//	increment number of characters again, then
		//	get the next keyvalue in the list
		numChars ++;
		kv_ptr = kv_ptr->next;
	}

	//	return the number of characters we successfully passed to the
	//	userFunction as a positive integer.
	return numChars;
}

uint8_t OpensSD::getSingleDate( uint8_t year, uint8_t month, uint8_t date,
								bool (*userFunction) (char) )
{

	int32_t start = getPositionFromDate(year, month, date);
	Serial.print("[GSD] START POSITION: ");Serial.println(start);
	int32_t stop = getPosition( "DATE", "", start + 5 );

	Serial.print("[GSD] STOP POSITION: ");Serial.println(stop);

	streamDataBetween( start, stop, userFunction );

	return 0;
}


uint32_t OpensSD::getPositionFromDate( uint8_t year, uint8_t month, uint8_t date )
{

	char userDate [16] = {0};

	switch( DATE_MARKER )
	{
		case DAY_MONTH_YEAR:
		//	delimiters are used because this will be formatted like any other keyvalue.
		//	to find certain dates in the file, the DATE key can be searched for.
			sprintf_P(	userDate,
						STRING_TABLE[2],
						date, month, year);
			break;

		case YEAR_MONTH_DAY:
			sprintf_P(	userDate,
						STRING_TABLE[2],
						year, month, date);
			break;

		case MONTH_DAY_YEAR:
			sprintf_P(	userDate,
						STRING_TABLE[2],
						month, date, year);
			break;
	}
	Serial.print("[GPD] Date: "); Serial.println( userDate );
	return getPosition("DATE",userDate);
}

int32_t OpensSD::streamDataBetween( uint32_t start, uint32_t stop,
									bool (*userFunction)(char) )
{
	//	get the data file name
	memset( buffer, 0, sizeof(buffer) );
	strncpy_P( buffer, STRING_TABLE[0], sizeof(buffer) );

	//	if the file doesn't exist, return -1

	File f = SD.open( buffer, FILE_READ );
	if( f == false )
	{	//	if the file wasn't opened, return -2
		return -2;
	}

	//	skip to the start date
	f.seek( start );
	if( stop == 0 )
	{
		stop = f.size();
	}

	uint32_t timeout = millis();
	int32_t numBytes = 0;

	while( 	f.available() &&
			f.position() < stop )
	{
		if( millis() - timeout > SD_TIMEOUT )
		{
			return -3;
		}

		char c = f.read();

		if( (*userFunction)( c ) == false )
		{
			return -10 - numBytes;
		}
		numBytes ++;
	}
	return numBytes;
}

void OpensSD::KeyValueList::print()
{
	OpensSD::KeyValue* kv_ptr = head;

	while( kv_ptr != nullptr && Serial)
	{
		Serial.print(kv_ptr->key);
		Serial.print(delimiter1);
		Serial.print(kv_ptr->val);
		Serial.print(delimiter2);
		kv_ptr = kv_ptr->next;
	}
	Serial.println();
}

void OpensSD::clearLocalSettings()
{

	OpensSD::KeyValue* ptr = settings.head;

	while( ptr != nullptr )
	{
		memset( ptr->key, 0, ptr->max_size );
		memset( ptr->val, 0, ptr->max_size );
		ptr = ptr->next;
	}
	if( settings.head == nullptr )
	{
		settings.add();
	}
	
}

void OpensSD::clearSavedSettings()
{
	//	check for "Settings.txt"
	//	clear the buffer and then copy over the settings filename.
	memset(buffer, 0, sizeof(buffer));
	strcpy_P(buffer, STRING_TABLE[1] );

	if( SD.exists( buffer ) )
	{
		SD.remove( buffer );
	}
	File f = SD.open( buffer, FILE_WRITE );
	f.close();
}

void OpensSD::printSavedData()
{
	//	get the data file name
	memset( buffer, 0, sizeof(buffer) );
	strncpy_P( buffer, STRING_TABLE[0], sizeof(buffer) );

	File f = SD.open( buffer, FILE_READ );
	f.seek( 0 );

	if( f == false )
	{
		return;
	}

	Serial.println("DATA FILE: ");
	Serial.println("****************************");

	while( f.available() )
	{
		Serial.print( (char) f.read() );
	}
	Serial.println();

	f.close();

}






