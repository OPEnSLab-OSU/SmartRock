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
#include <Wire.h>

// Include configuration
const char* json_config = 
#include "config.h"
;

// Set enabled modules
LoomFactory<
  Enable::Internet::Disabled,
  Enable::Sensors::Enabled,
  Enable::Radios::Enabled,
  Enable::Actuators::Enabled,
  Enable::Max::Enabled
> ModuleFactory{};

LoomManager Loom{ &ModuleFactory };
DynamicJsonDocument doc(1024);

const int switchPin = 19;
int switchPos = 0;

int secs = 0;
int mins = 0;
int hours = 0;
int days = 0;

volatile bool rtc_flag = false;

void wakeISR_RTC() {
  // disable the interrupt
  detachInterrupt(12);
  rtc_flag = true;
}

//custom function from Cameron of PNNL to make use of variable resistor
//found on newest hydro board PCB
void send_data(byte addr, byte data){
  Wire.beginTransmission(addr);
  Wire.write(data);
  Wire.endTransmission(true);
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
  //sets our switchPin as INPUT
  pinMode(switchPin, INPUT);
  
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

  //required for variable resistor use
  Wire.begin();

  Loom.begin_serial(true);
  Loom.parse_config(json_config);
  Loom.print_config();


 //Got rid of the physical switch, so just have it read
  //from the custom file
  switchPos = digitalRead(switchPin);
  char* customOp = "customOperationInterval.txt";
  readOpInt(customOp);
  
//  if (switchPos == HIGH) {
//    char* defaultOp = "operationInterval.txt";
//    readOpInt(defaultOp);
//    
//  }else{
//      char* customOp = "customOperationInterval.txt";
//      readOpInt(customOp);
//  }
  
  // Register an interrupt on the RTC alarm pin
  Loom.InterruptManager().register_ISR(12, wakeISR_RTC, LOW, ISR_Type::IMMEDIATE);

  LPrintln("\n ** Setup Complete ** ");
  Serial.flush();
}

byte res = 10; // EC Resolution anything larger than 0

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


  //send data to address of I2C
  send_data(0x2E, res); // set resistance in EC circuit

  //aim to 10000 for max EC value for solution then calibrate.
    
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
