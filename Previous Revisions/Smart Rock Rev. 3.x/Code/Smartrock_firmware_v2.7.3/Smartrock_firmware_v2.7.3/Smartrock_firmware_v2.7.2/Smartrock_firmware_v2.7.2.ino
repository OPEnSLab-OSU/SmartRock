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
#include <ArduinoJson.h>
#include <SdFat.h>
//#include <Wire.h>

// Include configuration
const char* json_config = 
#include "config.h"
;

// Set enabled modules
LoomFactory<
  Enable::Internet::Disabled,
  Enable::Sensors::Enabled,
  Enable::Radios::Disabled,
  Enable::Actuators::Disabled,
  Enable::Max::Disabled
> ModuleFactory{};

LoomManager Loom{ &ModuleFactory };
DynamicJsonDocument doc(1024);

int secs = 0;
int mins = 20;
int hours = 0;
int days = 0;

volatile bool rtc_flag = false;


void wakeISR_RTC() {
  // disable the interrupt
  detachInterrupt(12);
  rtc_flag = true;
}

//custom function to read specified operation interval file from SD
void readOpInt(char* opInt){

  SdFat sd;
  digitalWrite(8, HIGH);
  bool sd_found = sd.begin(SD_CS, SD_SCK_MHZ(50));
  if (sd_found){
    LPrintln("Found SD");
  } else {
    LPrintln("SD Not Found");
  }
  
  File file = sd.open(opInt);
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

void setup() 
{
  
  // Needs to be done for Hypno Board
  pinMode(5, OUTPUT);   // Enable control of 3.3V rail 
  pinMode(6, OUTPUT);   // Enable control of 5V rail 
  pinMode(12, INPUT_PULLUP);    // Enable waiting for RTC interrupt, MUST use a pullup since signal is active low
  pinMode(13, OUTPUT);

  //digitalWrite(switchPin, HIGH);
  //See Above
  digitalWrite(5, LOW); // Enable 3.3V rail
  digitalWrite(6, HIGH);  // Enable 5V rail
  digitalWrite(13, LOW);

  Loom.begin_serial(true);
  Loom.parse_config(json_config);
  Loom.print_config();

  //read from the custom file
  char* customOp = "SD_config.txt";
  readOpInt(customOp);
  
  // Register an interrupt on the RTC alarm pin
  Loom.InterruptManager().register_ISR(12, wakeISR_RTC, LOW, ISR_Type::IMMEDIATE);

  LPrintln("\n ** Setup Complete ** ");
  Serial.flush();
}

void loop() 
{
  
  digitalWrite(5, LOW); // Disable 3.3V rail
  digitalWrite(6, HIGH);  // Disable 5V rail
  digitalWrite(13, HIGH);

  // As it turns out, if the SD card is initialized and you change
  // the states of the pins to ANY VALUE, the SD card will fail to
  // write. As a result, we ensure that the board has been turned
  // off at least once before we make any changes to the pin states
  if (rtc_flag) {
    pinMode(23, OUTPUT);
    pinMode(24, OUTPUT);
    pinMode(10, OUTPUT);

    delay(1000);

    Loom.power_up();
  }

  Loom.measure();
  Loom.package();
  Loom.display_data();
  Loom.SDCARD().log();

  // set the RTC alarm to a custom duration specified by 
  // the user via operationInterval.txt or customOperationInterval.txt 
  // depending on switch position
  Loom.InterruptManager().RTC_alarm_duration(TimeSpan(days,hours,mins,secs));
  Loom.InterruptManager().reconnect_interrupt(12);

  digitalWrite(13, LOW);
  digitalWrite(5, HIGH); // Enable 3.3V rail
  digitalWrite(6, LOW);  // Enable 5V rail
  pinMode(23, INPUT);
  pinMode(24, INPUT);
  pinMode(10, INPUT);

  // Sleep Manager autmatically calls power_down on every sensor before sleeping
  // And power_up after waking.

  rtc_flag = false;
  Loom.SleepManager().sleep();
  while (!rtc_flag);
}
