
#include "header.h"

Adafruit_BluefruitLE_SPI ble(BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST);

/*-------------------------------------------------------------------------------------

FUNCTIONS

-------------------------------------------------------------------------------------*/

/*
SETUP

Begins ble communications.
*/

void ble_Setup(){
  
	ble.begin();
  ble.setMode(BLUEFRUIT_MODE_DATA); // set to simple UART back and forth comms
}


/*

Connect

Checks connection to a ble device, if not connected then tries to connect until a timeout
is reached.

*/

void ble_Connect(uint16_t connect_timeout)
{
	uint32_t timeout = millis();

  Serial.print("[BLE_C] timeout: "); Serial.println( timeout );

	while( !ble.isConnected() )
	{
		if( ( millis() - timeout ) > connect_timeout )
		{
      return;
		}
	}
}


/*
Stream Data

Write data between dates to the ble window.

*/

uint8_t ble_StreamData( uint8_t year1 = 0, uint8_t month1 = 0, uint8_t day1 = 0,
					              uint8_t year2 = 0, uint8_t month2 = 0, uint8_t day2 = 0)
{

	if( !ble.isConnected())
	{
		ble_Connect(BLE_TIMEOUT);
	}
	ble.setMode(BLUEFRUIT_MODE_DATA);



	mySD.getBetweenDates(	year1, month1, day1,
							          year2, month2, day2,
							          &ble_sendByte );
}


/*
Send Byte

Sends a byte to the ble window. This is used for any SD function that requires a function to stream
data to.

*/

bool ble_sendByte( char c )
{
	if( ble.isConnected() )
	{
		ble.write( c );
		return true;
	}
	return false;

}

/*
Stream Data From Day

Sends all data from just one day, specified by the user, to the ble window.

*/

int16_t ble_StreamDataFromDay( uint8_t year1, uint8_t month1, uint8_t day1 )
{
	int16_t retVal = mySD.getSingleDate(	year1, month1, day1,
										                    &ble_sendByte );
	return retVal;
}


/*
Get Command

Gets a command from the ble interface, or times out. This is used in combination with
parseCommand if the return value is valid.

Returns:
-1: user never wrote a command, timed out
-2: user entered an invalid command
0 or positive integer: index in COMMAND_TABLE that matches the user-entered command

*/

int8_t ble_GetCommand( uint16_t max_timeout )
{
  ble_PrintCommands();
  ble.println("Enter Command.");
	char cmd_buffer [32] = {0};
	uint32_t timeout = millis();

	while( !ble.available())
	{
		if( millis() - timeout > max_timeout )
		{
      ble.println("timed out");
			return -1;
		}
	}

	uint8_t index = 0;

	timeout = millis();
	while( ble.available() && index < sizeof(cmd_buffer) - 1)
	{
		cmd_buffer[index] = ble.read();
		index++;
	}
	cmd_buffer[index] = 0;
  ble.println( cmd_buffer );
  
	for( int i = 0; i< NUMCOMMANDS; i++)
	{
    int cmp = 0;
		cmp = strncmp_P(  cmd_buffer, (char*)pgm_read_word( &(COMMAND_TABLE[i]) ),
								      strlen(cmd_buffer) - 1 );
		if( cmp == 0 )
		{
      if( i == CMD_QUIT2 )
      {
        i = CMD_QUIT;
      }
			return i;
		}
   
	}
  delay(5000);
	return -2;
}


/*
Parse Command

Takes an integer command and performs an action based on which index it matches in 
the COMMAND_TABLE array.

*/

void ble_ParseCommand( uint8_t commandIndex)
{
  char msg_buffer [32];
  
  ble.println( commandIndex );
	uint8_t userDate [3] = {0};
	uint32_t fileIndex = 0;

  uint8_t buff_idx = 0;
  char userKey_buffer[16] = {0};
  char userVal_buffer[16] = {0};
  char lgBuffer[32] = {0};
  uint8_t userTime [6] = {0};
  char shortBuffer [3] = {0};
  bool failed = false;
  
	switch( commandIndex )
	{
		case CMD_GETDAY:
			
			if( ble_GetUserDate(userDate) == false)
			{
        ble.println("invalid date.");
        delay(5000);
				break;
			}
			mySD.getSingleDate( userDate[0], userDate[1], userDate[2], &ble_sendByte );
			break;

		case CMD_GETBETWEEN:
			ble.print("Enter Start Date.");
			if( ble_GetUserDate(userDate) == false)
			{
				ble.println("invalid date.");
				break;
			}
			else 
			{
				ble.println("Start Date (y-m-d):");
				ble.print(userDate[0]); ble.print(" - ");
				ble.print(userDate[1]); ble.print(" - ");
				ble.print(userDate[2]);
			}

			memset(userDate, 0, sizeof(userDate));
			ble.println("Enter End Date.");
			if( ble_GetUserDate(userDate) == false)
			{
				ble.println("invalid date.");
				break;
			}
			else 
			{
				ble.println("End Date (y-m-d): ");
				ble.print(userDate[0]); ble.print(" - ");
				ble.print(userDate[1]); ble.print(" - ");
				ble.print(userDate[2]);
			}
     break;

     case CMD_MEASURE:
      ble.print("Measuring pressure and temperature...");
      sensor.measure();
      memset( userVal_buffer, 0, sizeof( userVal_buffer ) );
      String( sensor.getTemperature() ).toCharArray( userVal_buffer, 16 );
      mySD.addDataPoint( "Temperature", userVal_buffer );

      memset( userVal_buffer, 0, sizeof( userVal_buffer ) );
      String( sensor.getPressure() ).toCharArray( userVal_buffer, 16 );
      mySD.addDataPoint( "Pressure", userVal_buffer );
      
      mySD.streamLocalData( &ble_sendByte );
      break;

     case CMD_SETTINGS:
      mySD.streamLocalSettings( &ble_sendByte );
      ble.println("Enter Mode (0=nothing, 1=write).");
      if ( ble_WaitForBytes( 1, BLE_TIMEOUT) < 1 )
      {
        ble.println("Invalid command or timeout.");
        break;
      }
      switch( ble.read() )
      {
        case '0':
          ble.flush();
          break;

        case '1':
          ble.flush();
          
          ble.println("Enter Key:");
          ble.print("Key:\t");
          if( ble_WaitForBytes(1, BLE_TIMEOUT) >= 1 )
          {
            buff_idx = 0;
            
            char userChar = ble.read();
            
            while( ble.available() && buff_idx < 15 && userChar != 13 )
            {
              userKey_buffer[buff_idx] = userChar;
              buff_idx++;
              userChar = ble.read();
            }
            for( int i=0; i< buff_idx; i++ )
            {
              ble.print( uint8_t (userKey_buffer[i] ) );
            }
            ble.println("----");
            userKey_buffer[buff_idx] = 0;
          }
          
          ble.println("Enter Value:");
          if( ble_WaitForBytes(1, BLE_TIMEOUT) >= 1 )
          {
            buff_idx = 0;
            char userChar = ble.read();
            while( ble.available() && buff_idx < 15 && userChar != 13)
            {
              userVal_buffer[buff_idx] = userChar;
              buff_idx++;
              userChar = ble.read();
            }
            userVal_buffer[buff_idx] = 0;
          }

          mySD.addSetting(userKey_buffer, userVal_buffer);
          mySD.streamLocalSettings( &ble_sendByte );
          break;
      }
      break;

      case CMD_TIME:
        ble.print("Current Time (yy:mm:dd:hh:mm:ss): ");
        snprintf(lgBuffer, 32, "%.2u:%.2u:%.2u:%.2u:%.2u:%.2u",
                 myPower.year,
                 myPower.month,
                 myPower.date,
                 myPower.hour,
                 myPower.minute,
                 myPower.second );

        ble.println(lgBuffer);
        ble.print("Change time? (Y/N):");
        ble.flush();
        if( ble_WaitForBytes(1, BLE_TIMEOUT) >= 1 )
        {
          if( toupper( (char) ble.read() ) == 'Y' )
          {
            memset( msg_buffer, 0, sizeof(msg_buffer) );
            strcpy_P( msg_buffer, (char*) pgm_read_word( &( MSG_TABLE[6] ) ) );
            ble.print( msg_buffer );
            
            for(uint8_t i = 0; i < 6; i++ )
            {
              memset( msg_buffer, 0, sizeof(msg_buffer) );
              strcpy( msg_buffer, (char*) pgm_read_word( &( MSG_TABLE[i] ) ) );
              ble.print( msg_buffer );

              if( ble_WaitForBytes(3, BLE_TIMEOUT) >= 3 )
              {
                shortBuffer[0] = ble.read();
                shortBuffer[1] = ble.read();
                shortBuffer[2] = 0;
                if( isDigit(shortBuffer[0]) && isDigit(shortBuffer[1]) )
                {
                  userTime[i] = String( shortBuffer ).toInt();
                  ble.println( userTime[i] );
                }
                else
                {
                  failed = true;
                  ble.println("failed.");
                  delay(5000);
                  break;
                }
              }
              
            }

            if( failed == false )
            {
              myPower.setTime(  userTime[0], userTime[1], userTime[2], userTime[3], userTime[4], userTime[5] );
              ble.println("New Time Set.");
              memset( lgBuffer, 0, sizeof(lgBuffer) );
              snprintf(lgBuffer, 32, "%.2u:%.2u:%.2u:%.2u:%.2u:%.2u",
                       myPower.year,
                       myPower.month,
                       myPower.date,
                       myPower.hour,
                       myPower.minute,
                       myPower.second );
              ble.println(lgBuffer);
              delay(5000);
            }
          }
          else
          {
            ble.print("No more actions.");
            delay(5000);
          }
        }
        else
        {
          ble.print("invalid.");
          delay(5000);
        }
        break;

      case -2:
        ble.println("invalid command.");
        break;

      case CMD_QUIT:
        ble.println("quitting...");
        delay(2000);
        ble_broadcast = false;
        break;

      case CMD_DEFAULT:
        mySD.clearSavedSettings();
        break;

      case CMD_ALL_DATA:
        mySD.streamDataBetween( 0, 10000, &ble_sendByte );
        ble.println();
        break;
	}
}

/*
Wait For Bytes

Simple macro that waits until the user enters the correct number of bytes, or it times out.

Returns:
0: timeout or user entered too few bytes
Available bytes: number of bytes user entered if greater than or equal to the requested
				amount.

*/

uint8_t ble_WaitForBytes( uint8_t numBytes, uint16_t max_timeout )
{
	uint32_t timeout = millis();

	while( !ble.available() )
	{
		if( millis() - timeout > max_timeout )
		{
			return 0;
		}
	}
 if( ble.available() < numBytes )
 {
  return 0;
 }
	return ble.available();
}

/*
GetUserDate

Requests a date from the user and stores it in a size-3 uint8_t array "date", in the
form of year, month, date.

Returns:
true: a valid date was stored in the array
false: an invalid date was entered or the request timed out

*/

bool ble_GetUserDate( uint8_t date [3])
{
	char year1 [3] = {0};
	char month1 [3] = {0};
	char day1 [3] = {0};

	ble.print("Enter two-digit year: ");

	if( !ble_WaitForBytes( 2, BLE_TIMEOUT ) )
	{
		return false;
	}

	year1[0] = ble.read();
	year1[1] = ble.read();
	year1[2] = 0;

	ble.print("Enter two-digit month: ");

	if( !ble_WaitForBytes( 2, BLE_TIMEOUT ) )
	{
		return false;
	}

	month1[0] = ble.read();
	month1[1] = ble.read();
	month1[2] = 0;

	ble.println(month1);

	ble.print("Enter two-digit day: ");

	if( !ble_WaitForBytes( 2, BLE_TIMEOUT ) )
	{
		return false;
	}

	day1[0] = ble.read();
	day1[1] = ble.read();
	day1[2] = 0;

	date[0] = String(year1).toInt();
	date[1] = String(month1).toInt();
	date[2] = String(day1).toInt();

	if( date[1] == 0 || date[2] == 0 )
	{
		return false;
	}

	return true;
}

void ble_PrintLocalData()
{
  mySD.streamLocalData( &ble_sendByte );
}

void ble_PrintCommands()
{
  ble.println("POSSIBLE COMMANDS:");
  char tempMessage [32] = {0};
  for( uint8_t i = 0; i < NUMCOMMANDS; i++ )
  {
    memset( tempMessage, 0, sizeof( tempMessage ) );
    strcpy_P( tempMessage, COMMAND_TABLE[i] );
    ble.print(i);ble.print(": ");ble.println( tempMessage );
  }
  ble.println();
}
