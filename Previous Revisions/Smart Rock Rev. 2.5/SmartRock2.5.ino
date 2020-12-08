///////////////////////////////////////////////////////////////////////////////

// This example is the code used for the OPEnS Lab's Smart Rock.

// The device expects to have:
// - Feather M0 WiFi
// - OPEnS Lab hydro board 
// - Hypnos Board
// - MS5803 pressure sensor
// - Analog sensors:
// 		- EC / Total dissolved solids (pin A0)
// 		- pH (pin A1)
// 		- Turbidity (pin A2)

// The device:
//    - Wakes from sleep
//		- Reads sensors
//		- Logs to SD
//		- Returns to sleep

// The provided configurations should be copied to a micro SD card to be used on the device.
// They will not work as provided, you must fill out/configure the following as needed:
// - Device name 
// - Instance number
// - Interval
// - SD default save file
// - WiFi SSID
// - WiFi Password

///////////////////////////////////////////////////////////////////////////////

#include <Loom.h>

// Include configuration
const char* json_config = 
#include "config.h"
;

// Set enabled modules
LoomFactory<
	Enable::Internet::WiFi,
	Enable::Sensors::Enabled,
	Enable::Radios::Disabled,
	Enable::Actuators::Enabled,
	Enable::Max::Disabled
> ModuleFactory{};

LoomManager Loom{ &ModuleFactory };
//


void setup() 
{ 
	  pinMode(5, OUTPUT);   // Enable control of 3.3V rail 
  pinMode(6, OUTPUT);   // Enable control of 5V rail 


	pinMode(9, INPUT_PULLUP);			// To detect mode
	//pinMode(10, OUTPUT);				// To be able to turn sensor on/off 
										// Not currently being used due to conflict with SD CS pin

	Loom.begin_LED();					// LED setup
	Loom.begin_serial(true);			// Start Serial, false indicates don't wait for Serial Monitor


	Loom.parse_config(json_config);
//	}

	Loom.print_config(true);				// Print config

	LPrintln("\n ** Setup Complete ** ");

	Loom.flash_LED(5, 50, 50, false);		// Flash to indicate is setup
}


void loop() 
{
   digitalWrite(5, LOW); // Enable 3.3V rail
   digitalWrite(6, HIGH);  // Enable 5V rail

	 //Loom.pause(100);			// Warmup time
   delay(1000);         // delay time
	Loom.measure();				// Collect data


	Loom.package();				// Build Json from data
	Loom.display_data();		// Print data (will not work properly if using nap instead of pause below)

	Loom.SDCARD().log();		// Log to SD

	// The following if statements are a means of having both Max and GoogleSheets modes
	// work with the same code. If a module exists, it will use it, otherwise it was 
	// probably not instantiated for this mode and will skip it.

 digitalWrite(5, HIGH); // Disables 3.3V rail
 digitalWrite(6, LOW);  // Disables 5V rail
	//Loom.pause(); 				// Wait (delay) based on 'interval' value in config
	Loom.nap(); 				// Wait (sleepy dog) based on 'interval' value in config
}
