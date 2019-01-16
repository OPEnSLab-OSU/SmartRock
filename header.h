#pragma once

#include <ms5803.h>
#include <OpensSD.h>
#include <Adafruit_BluefruitLE_SPI.h>
#include <Adafruit_BluefruitLE_UART.h>
#include <OpensPower.h>

void ble_Setup();
void ble_Connect(uint16_t connect_timeout);
uint8_t ble_ReceiveCommand();
void ble_PrintHelp();
void ble_streamData( uint8_t, uint8_t, uint8_t, uint8_t, uint8_t );
bool ble_sendByte( char );
void ble_PrintLocalData();
bool ble_GetUserDate(uint8_t []);
int8_t ble_GetCommand( uint16_t );
void ble_ParseCommand( uint8_t );
void ble_PrintCommands();

bool printData( char );
void debug_msg( char* );

extern Adafruit_BluefruitLE_SPI ble;
extern MS5803 sensor;
extern OpensSD mySD;
extern OpensPower myPower;

// my name is mitch

/*-------------------------------------------------------------------------------------

Constant Settings and Definitions

-------------------------------------------------------------------------------------*/

//  Debug Mode:
//  0 = no printout
//  1 = Serial printout
//  2 = BLE printout
//  3 = both
#define DEBUG_MODE                    1

const char COMPILE_DATE [] PROGMEM = __DATE__ " " __TIME__;

//  command strings

const char COMMAND0 [] PROGMEM = "GETDAY";
const char COMMAND1 [] PROGMEM = "GETBETWEEN";
const char COMMAND2 [] PROGMEM = "MEASURE";
const char COMMAND3 [] PROGMEM = "SETTINGS";
const char COMMAND4 [] PROGMEM = "TIME";
const char COMMAND5 [] PROGMEM = "ALL_DATA";
const char COMMAND6 [] PROGMEM = "DEFAULT";
const char COMMAND7 [] PROGMEM = "Q";
const char COMMAND8 [] PROGMEM = "q";

#define NUMCOMMANDS                   9

//  command indices
#define CMD_GETDAY                    0
#define CMD_GETBETWEEN                1
#define CMD_MEASURE                   2
#define CMD_SETTINGS                  3
#define CMD_TIME                      4
#define CMD_ALL_DATA                  5
#define CMD_DEFAULT                   6
#define CMD_QUIT                      7
#define CMD_QUIT2                     8

//  command table
const char* const COMMAND_TABLE [] PROGMEM = 
{
  COMMAND0,
  COMMAND1,
  COMMAND2,
  COMMAND3,
  COMMAND4,
  COMMAND5,
  COMMAND6,
  COMMAND7,
  COMMAND8
};

/********************************************
 *  MESSAGE TABLE
 ********************************************/

const char MESSAGE0 [] PROGMEM = "ENTER YEAR: ";
const char MESSAGE1 [] PROGMEM = "ENTER MONTH: ";
const char MESSAGE2 [] PROGMEM = "ENTER DAY OF MONTH: ";
const char MESSAGE3 [] PROGMEM = "ENTER HOUR: ";
const char MESSAGE4 [] PROGMEM = "ENTER MINUTE: ";
const char MESSAGE5 [] PROGMEM = "ENTER SECOND: ";
const char MESSAGE6 [] PROGMEM = "ENTERED VALUES SHOULD BE TWO DIGITS ('01', '11','99').\n";

const char* const MSG_TABLE [] PROGMEM = 
{
  MESSAGE0,
  MESSAGE1,
  MESSAGE2,
  MESSAGE3,
  MESSAGE4,
  MESSAGE5,
  MESSAGE6
};

//  SETTINGS:

extern uint16_t intervalTime;         //  time between wakeups in seconds
extern uint8_t ble_waitConnect_time;  //  time to wait for ble to connect before shutting off during broadcasting hours
extern uint8_t ble_broadcast_start;   //  hour of the day the ble device starts broadcasting every sample for waitConnect_time
extern uint8_t ble_broadcast_end;     //  hour of the day the ble device ends broadcasting every sample for waitConnect_time
extern bool ble_broadcast;

 
//  BLE pins
#define BLE_TIMEOUT                    30000
#define BLUEFRUIT_SPI_CS               8
#define BLUEFRUIT_SPI_IRQ              7
#define BLUEFRUIT_SPI_RST              4 

//  SD CONSTANTS
#define SD_CHIPSELECT                  10
