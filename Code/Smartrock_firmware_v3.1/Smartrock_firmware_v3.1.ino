///////////////////////////////////////////////////////////////////////////////

// This code is for the OPEnS Lab Smart Rock and Smart Rock Beta Group

// Includes
// - SD
// - DS3231 RTC
// - Deep Sleep functionality thanks to Hypnos (link below for more information)
// - EC
// - Turbidity
// - Pressure
// - Temp

// Further details about the Hypnos board can be found here:
// https://github.com/OPEnSLab-OSU/OPEnS-Lab-Home/wiki/Hypnos

///////////////////////////////////////////////////////////////////////////////

#include <Loom.h>

// Include configuration
const char* json_config = 
#include "config.h"
;

using namespace Loom;
Loom::Manager Feather{};

DynamicJsonDocument doc(1024);

int secs = 0;
int mins = 20;
int hours = 0;
int days = 0;

void wakeISR_RTC() {
  // disable the interrupt
  detachInterrupt(12);
}

//custom function to read specified operation interval file from SD
void readOpInt(char* opInt){
  File file;
  file.open(opInt);
  if (file){
    LPrintln("File is good");
  }
  DeserializationError error = deserializeJson(doc, file);
  
  if (error) { // Make sure json was valid
    LPrintln("deserializeJson() failed: ", error.c_str());
  }
  
  serializeJsonPretty(doc, Serial);
  JsonObject json = doc.as<JsonObject>();

  //This will set the time values
  //based on the values parsed from .txt file on SD
  secs = json["seconds"];
  mins = json["minutes"];
  hours = json["hours"];
  days = json["days"];
}

void writeSerialNo(){
  File file;
  file.open(getSD(Feather).get_default_file(), O_WRITE | O_AT_END);
  if (!file){
    LPrintln("Could not log serial number.");
    return;
  }

  file.print("Serial Number: ");
  file.print(Feather.get_serial_no());
  file.print("\n");
  file.close();
}

void setup() 
{
  // Needs to be done for Hypno Board
  pinMode(5, OUTPUT);   // Enable control of 3.3V rail 
  pinMode(6, OUTPUT);   // Enable control of 5V rail 

  //See Above
  digitalWrite(5, LOW); // Enable 3.3V rail
  digitalWrite(6, HIGH);  // Enable 5V rail

  Feather.begin_LED();
  Feather.begin_serial(true);
  Feather.parse_config(json_config);
  Feather.print_config();

  //read from the custom file
  char* customOp = "SD_config.txt";
  readOpInt(customOp);
  
  // Register an interrupt on the RTC alarm pin
  getInterruptManager(Feather).register_ISR(12, wakeISR_RTC, LOW, ISR_Type::IMMEDIATE);

  writeSerialNo();

  LPrintln("\n ** Setup Complete ** ");
}

void loop() 
{
  Feather.measure();
  Feather.package();
  Feather.display_data();
  getSD(Feather).log();

  // set the RTC alarm to a custom duration specified by 
  // the user via operationInterval.txt or customOperationInterval.txt 
  // depending on switch position
  getInterruptManager(Feather).RTC_alarm_duration(TimeSpan(days,hours,mins,secs));
  getInterruptManager(Feather).reconnect_interrupt(12);

  digitalWrite(5, HIGH); // Disable 3.3V rail
  digitalWrite(6, LOW);  // Disable 5V rail

  // Disable SPI pins/SD chip select to save power
  pinMode(23, INPUT);
  pinMode(24, INPUT);
  pinMode(10, INPUT);

  Feather.power_down();
  getSleepManager(Feather).sleep(); // Sketch pauses here until RTC alarm

  digitalWrite(5, LOW); // Enable 3.3V rail
  digitalWrite(6, HIGH);  // Enable 5V rail

  pinMode(23, OUTPUT);
  pinMode(24, OUTPUT);
  pinMode(10, OUTPUT);

  Feather.power_up();
  delay(1000);
}
