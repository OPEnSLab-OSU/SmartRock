#include "header.h"

MS5803 sensor( 0x77 );
OpensSD mySD( 10 );
OpensPower myPower( 6 );

uint8_t ble_broadcast_start = 0;
uint8_t ble_broadcast_end = 24;
uint8_t ble_broadcast_time = 10;
uint8_t lastDate = 0;
uint16_t intervalTime = 60;
bool ble_broadcast = false;
char tempSettingKey [16] = {0};

void setup() {

  //  begin serial at 57600 BAUD rate
  Serial.begin(57600);

  //  delay to give time to open serial window and to program
  delay(4000);

  //  turn on the onboard LED
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  
  // GET SETTINGS from SD File, initialing the SD class
  int8_t numSettings = mySD.begin();   //  checks for settings

  //  print out the number of settings followed by a list of the settings
  Serial.print("numSettings: ");Serial.println( numSettings );
  mySD.printLocalSettings();

  //  if mySD setup found valid settings in the file, transfer the settings to their global
  //  variables so that they are usable
  if( numSettings > 0 )
  {
    //  get the broadcasting starting hour
    memset( tempSettingKey, 0, sizeof( tempSettingKey ) );
    mySD.getSetting( "BC_START", tempSettingKey );
    Serial.print("BC_START: ");Serial.print(tempSettingKey);Serial.println();
    //  even if the string is invalid (corrupt data?), the start time
    //  can be 0 so we won't check if it is a valid number.
    ble_broadcast_start = String( tempSettingKey ).toInt();
    

    //  get the broadcasting ending hour
    memset( tempSettingKey, 0, sizeof( tempSettingKey ) );
    mySD.getSetting( "BC_END", tempSettingKey );
    Serial.print("BC_END: ");Serial.print(tempSettingKey);Serial.println();
    //  this one we have to check if it isn't 0
    if( String( tempSettingKey ).toInt() != 0 )
    {
      ble_broadcast_end = String( tempSettingKey ).toInt();
    }


    //  get the broadcasting duration
    memset( tempSettingKey, 0, sizeof( tempSettingKey ) );
    mySD.getSetting( "BC_TIME", tempSettingKey );
    if( String( tempSettingKey ).toInt() != 0 )
    {
      ble_broadcast_time = String( tempSettingKey ).toInt();
    }


    //  get the sleep time duration
    memset( tempSettingKey, 0, sizeof( tempSettingKey ) );
    mySD.getSetting( "SLEEP_TIME", tempSettingKey );
    if( String( tempSettingKey ).toInt() != 0 )
    {
      intervalTime = String( tempSettingKey ).toInt();
    }

    //  get the previously recorded day of the month
    memset( tempSettingKey, 0, sizeof( tempSettingKey ) );
    mySD.getSetting( "LASTDATE", tempSettingKey );

    Serial.println("----------------------------------------------------------------");
    if( String( tempSettingKey ).toInt() != 0 )
    {
      lastDate = String( tempSettingKey ).toInt();
      Serial.print("[MAIN] LAST DATE: ");Serial.println( lastDate );
    }
    else
    {
      Serial.println("[MAIN] Last Date String: ");
      for( int i=0; i < sizeof(tempSettingKey); i++)
      {
        Serial.print( (uint8_t) tempSettingKey[i] );
        Serial.print(' ');
      }
      Serial.println();
    }
        
  }
  mySD.printLocalSettings();
  
  myPower.begin();  //  inits RTC, gets RTC settings
  if( lastDate != myPower.date || mySD.firstCycle )
  {
    Serial.println("[MAIN] MARKING NEW DATE");
    mySD.markNewDate( myPower.year, myPower.month, myPower.date );
    lastDate = myPower.date;
  }
  Serial.println("&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&");
  Serial.print("[MAIN] HOUR: ");Serial.println( myPower.hour );
  if( myPower.hour >= ble_broadcast_start && myPower.hour < ble_broadcast_end )
  {
    Serial.println( ble_broadcast_start); Serial.println(ble_broadcast_end );
    ble_Setup();         
    ble_broadcast = true;
  }
  sensor.begin();
}

void loop() {
  char sensorBuffer [16] = {0};

  //  measure sensor
  sensor.measure();

  //  update sensor data on mySD Data list
  String( sensor.getTemperature() ).toCharArray( sensorBuffer, sizeof( sensorBuffer ) );
  mySD.addDataPoint( "Temperature", sensorBuffer );
  memset( sensorBuffer, 0, sizeof( sensorBuffer ) );
  String( sensor.getPressure() ).toCharArray( sensorBuffer, sizeof( sensorBuffer ) );
  mySD.addDataPoint( "Pressure", sensorBuffer );

  uint16_t timestamp_seconds = myPower.hour*3600 + myPower.minute*60 + myPower.second;
  memset( sensorBuffer, 0, sizeof( sensorBuffer ) );
  String( timestamp_seconds ).toCharArray( sensorBuffer, sizeof( sensorBuffer ) );
  mySD.addDataPoint( "Time", sensorBuffer );
  
  //  save data to the SD
  mySD.saveData();

  //  print data to serial
  mySD.printLocalData();
  mySD.clearLocalSettings();
  mySD.printLocalSettings();
  
  memset(tempSettingKey, 0, sizeof(tempSettingKey) );
  String( ble_broadcast_start ).toCharArray( tempSettingKey, sizeof(tempSettingKey) );
  mySD.addSetting( "BC_START", tempSettingKey );
  
  memset(tempSettingKey, 0, sizeof(tempSettingKey) );
  String( ble_broadcast_end ).toCharArray( tempSettingKey, sizeof(tempSettingKey) );
  mySD.addSetting( "BC_END", tempSettingKey );
  
  memset(tempSettingKey, 0, sizeof(tempSettingKey) );
  String( ble_broadcast_time ).toCharArray( tempSettingKey, sizeof(tempSettingKey) );
  mySD.addSetting( "BC_TIME", tempSettingKey );
  
  memset(tempSettingKey, 0, sizeof(tempSettingKey) );
  String( intervalTime ).toCharArray( tempSettingKey, sizeof(tempSettingKey) );
  mySD.addSetting( "SLEEP_TIME", tempSettingKey );

  memset( tempSettingKey, 0, sizeof(tempSettingKey) );
  String( lastDate ).toCharArray( tempSettingKey, sizeof(tempSettingKey) );
  mySD.addSetting( "LASTDATE", tempSettingKey );

  //  if bluetooth is not connected, try to connect for 10 seconds.
  if( !ble.isConnected() && ble_broadcast == true )
  {
    Serial.println("Connecting ble...");
    Serial.print("broadcast time: ");Serial.println( ble_broadcast_time );
    ble_Connect( ble_broadcast_time * 1000 );
    
    if( ble.isConnected() )
    {
      delay(5000);
      ble.println("Connected!");
    }
  }

  while( ble.isConnected() && ble_broadcast == true )
  {
    Serial.println("getting command...");
    int8_t cmd = ble_GetCommand( 30000 );
    if( cmd == -1 )
    {
      ble_broadcast = false;
    }
    else
    {
      Serial.println(cmd);
      ble_ParseCommand( cmd );
    }
  }

  //  shut down
  myPower.alarm1_SetTime_Offset( intervalTime );
  myPower.alarm1_getTime();
  
  if( ble.isConnected() && ble_broadcast == true )
  {
    ble.println("Alarm Time:");
    ble.print(myPower.alarm1_date);ble.print('-');
    ble.print(myPower.alarm1_hour);ble.print(':');
    ble.print(myPower.alarm1_minute);ble.print(':');
    ble.print(myPower.alarm1_second);
    delay(5000);
  }
  
  Serial.println(F("Going to sleep.\n\n"));
  
  
  mySD.saveSettings();
  mySD.printLocalSettings();
  mySD.printSavedSettings();
  mySD.printSavedData();
  
  myPower.powerDown();
}

bool printData( char c )
{
  if( Serial )
  {
    Serial.print( c );
    return true;
  }
  return false;
}

void debug_msg ( char* msg )
{
  #if DEBUG_MODE == 1 || DEBUG_MODE == 3
  Serial.println( msg );
  #elif DEBUG_MODE == 2 || DEBUG_MODE == 3
  ble.println( msg );
  #endif
}
