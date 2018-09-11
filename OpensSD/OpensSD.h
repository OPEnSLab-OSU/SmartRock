#pragma once
#include <avr/pgmspace.h>
/*
NOT RECOMMENDED FOR USE WITH ARDUINO UNO
This library is large and it can very quickly fill up the SRAM of
the microcontroller.
*/
#include <SPI.h>
#include <SD.h>

#define DATE_MARKER		DAY_MONTH_YEAR
#define DAY_MONTH_YEAR	0
#define YEAR_MONTH_DAY	1
#define MONTH_DAY_YEAR	2

#define SD_TIMEOUT		30000
//	filename stuff
//	prefix goes before the date of the file.
const char FILENAME_DATA [] PROGMEM =			"Data.txt";
const char FILENAME_SETTINGS [] PROGMEM =		"Settings.txt";
const char DATE_STAMP [] PROGMEM = 				"%.2u:%.2u:%.2u";
const char DATE_FORMAT [] PROGMEM =				"%.2u:%.2u:%.2u";
const char KV_FORMAT [] PROGMEM = 				"%S%c%S%c";
const char DATE_PRINT [] PROGMEM =				"\nDATE%c%.2u:%.2u:%.2u%c\n";

//	storing strings that should never change. These include filenames,
//	error messages, and command strings.
const char* const STRING_TABLE [] PROGMEM = 
{
	FILENAME_DATA,				//	0
	FILENAME_SETTINGS,			//	1
	DATE_STAMP,					//	2
	DATE_FORMAT,				//	3
	KV_FORMAT,					//	4
	DATE_PRINT					//	5
};

/********************************************
 *  ERROR MESSAGE TABLE
 ********************************************/
// OpensSD error messages
const char ERROR_MSG_0 [] PROGMEM =   	"FIRST CYCLE -- SETTINGS FILE NOT FOUND.";
const char ERROR_MSG_1 [] PROGMEM =   	"SD TIMEOUT.";
const char ERROR_MSG_2 [] PROGMEM =		"%u SETTINGS FOUND.";
const char ERROR_MSG_3 [] PROGMEM =		"KEY FOUND. REPLACING VALUE WITH %S.";
const char ERROR_MSG_4 [] PROGMEM =		"EMPTY LIST. CREATING NEW KEYVALUE.";
const char ERROR_MSG_5 [] PROGMEM =		"KEYVALUE NOT FOUND. CREATING NEW KEYVALUE.";
const char ERROR_MSG_6 [] PROGMEM =		"FAILED TO OPEN FILE.";
const char ERROR_MSG_7 [] PROGMEM =		"OK";
const char ERROR_MSG_8 [] PROGMEM =		"FOUND:\t%S%c%S%c";
const char ERROR_MSG_9 [] PROGMEM =		"KEY NOT FOUND.";
const char ERROR_MSG_10 [] PROGMEM =	"KEY ALREADY EXISTS.";
const char ERROR_MSG_11 [] PROGMEM =	"FILE DOESN'T EXIST.";






class OpensSD
{
private:

	/*

	KEYVALUE STRUCTURE
	It is a separate member from the keyvaluelist class so that
	other functions can use keyvalue objects.
	
	*/

	struct KeyValue
	{
		const static uint8_t max_size = 16;
		char key [max_size] = {0};
		char val [max_size] = {0};
		KeyValue* next;

		KeyValue( char* k, char* v, KeyValue* nextKV = nullptr )
		{
			memset(key, 0, max_size);
			memset(val, 0, max_size);
			strncpy( key, k, max_size -1 );
			strncpy( val, v, max_size -1 );
			next = nextKV;
		}
	};


	/*
	KEYVALUELIST CLASS

	Allows simple manipulation and storage of keyvalues in a linked list.
	Keyvalue lists use dynamic memory allocation. While this can be dangerous
	for small amounts of memory, most of the microcontrollers we use now have
	plenty of space for this.
	*/

	class KeyValueList
	{
	public:
		KeyValue* head;
		KeyValue* last;
		KeyValueList(){ head = nullptr; last = head;}
		~KeyValueList();

		void clear();
		KeyValue* add( char* key = "", char* value = "" );
		KeyValue* get( char* );
		int16_t streamList( bool (*userFunction)(char));
		void print();
	};

	KeyValueList variables;		//	place to store current data
	KeyValueList settings;		//	place to store current settings

	int chipSelect;		//	chip select pin for the SD card
	static const char delimiter1 = '=';			//	char that separates keys and values
	static const char delimiter2 = ';';			//	char that separates keyvalues


	//	Functions only to be used internally
	uint8_t addSetting(KeyValue*);						//	add a setting by passing a keyvalue object
	int32_t getPosition(char*, char*, uint32_t startPosition = 0);//	get the position of a key and matching value
	uint32_t getPositionFromDate( uint8_t, uint8_t, uint8_t);
	int16_t getBlockAfter( char*, uint16_t, uint32_t );	//	get a number of bytes after a point in the file

	//	Finds a key in the given list, stores its value, and returns a pointer to the whole keyvalue
	KeyValue* getKVListValue( char*, char**, KeyValueList* );	

	//	to keep it clear that super functions are called from the base class that
	//	OpensSD inherits from.

	static const uint8_t bufferSize = 64;
	static const uint8_t bufferBSize = 32;

	char error_buffer [bufferSize];

public:

	//	marks whether this is the first cycle or not based on a check.
	//	this is public so that user functions can make use of this
	//	fact.
	bool firstCycle;	

	//	a character array to store whatever the current function needs to.
	//	This is usually used for messages, filenames, and frequently used formats.
	char buffer [bufferSize];

	//	anonther, smaller buffer.
	char bufferB [bufferBSize];

	OpensSD( int chipSelect );	//	constructor

	//	initialize the sd, check for settings, make setting/datafiles if necessary,
	//	and update the firstCycle flag
	int8_t begin();	

	int8_t markNewDate(uint8_t, uint8_t, uint8_t);			//	marks a new date if one isn't found.

	void addDataPoint(char*, char*);
	uint8_t saveData(char*);	//	all one string
	uint8_t saveData();
	int32_t streamLocalData( bool(*userFunction)(char));
	uint8_t getAllAfterDate(uint8_t year, uint8_t month, uint8_t date);
	int32_t getBetweenDates(uint8_t year1, uint8_t month1, uint8_t date1,
							uint8_t year2, uint8_t month2, uint8_t date2,
							bool (*userFunction) (char) );
	uint8_t getSingleDate(uint8_t year, uint8_t month, uint8_t date,
							bool (*userFunction) (char) );
	int32_t streamDataBetween( uint32_t start, uint32_t stop, bool (*userFunction)(char));
	int32_t getAfterDate(uint8_t, uint8_t, uint8_t, bool (*userFunction)(char));
	void printLocalData();
	void printSavedData();

	void clearLocalData();
	
	int16_t get16_After( char [16], uint32_t);
	int16_t get64_After( char [64], uint32_t);
	int16_t get128_After( char [128], uint32_t);
	int16_t get256_After( char [256], uint32_t);
	int16_t get512_After( char [512], uint32_t);

	uint8_t saveSettings();
	int8_t checkSettingsFile();
	uint8_t getSetting(char*, char*);
	void addSetting(char*);
	void addSetting(char*, char*);
	int16_t streamLocalSettings( bool(*userFunction)(char));
	void clearLocalSettings();
	void printLocalSettings();
	void printSavedSettings();
	void clearSavedSettings();

};


