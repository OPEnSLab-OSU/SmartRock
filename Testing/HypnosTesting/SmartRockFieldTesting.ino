///////////////////////////////////////////////////////////////////////////////

// This example is the code used for the OPEnS Lab's Smart Rock 

// It is using the following modules:
// - DS3231 RTC
// - Interrupt Manager
// - Sleep Manager
// - Analog (for turbidity, TDS)
// - Adalogger m0
// - MS5803 pressure sensor

// Normal operation is:
// - Collect data
// - Log data to SD card
// - Set alarm for next wake time
// - Go to sleep until alarm

// You can also wake the Smart Rock by putting a magnet near the reed switch.
// This will also trigger data logging and then return to sleep

///////////////////////////////////////////////////////////////////////////////

#include <Loom.h>

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




#define ALARM_PIN 6		// Wire interrupt on RTC to this pin
#define REED_PIN 11		// Wire reed switch to this pin


volatile bool alarmFlag = false;
volatile bool reedFlag = false;


void alarmISR() { 
	detachInterrupt(digitalPinToInterrupt(ALARM_PIN)); 
	// detachInterrupt(digitalPinToInterrupt(REED_PIN)); 
	alarmFlag = true;
	// LPrintln("\n\n", "Alarm went off", "\n");
}
void reedISR() { 
	// detachInterrupt(digitalPinToInterrupt(ALARM_PIN)); 
	detachInterrupt(digitalPinToInterrupt(REED_PIN));
	reedFlag = true;
	// LPrintln("\n\n", "Reed switch triggered", "\n"); 
}



void setup() 
{
	pinMode(5, OUTPUT);
	pinMode(6, OUTPUT);

	digitalWrite(5, LOW);
	digitalWrite(6, HIGH);

	Loom.begin_LED();
	Loom.flash_LED(10, 200, 200, true);
	Loom.begin_serial();

	pinMode(10, OUTPUT);   

	Loom.parse_config(json_config);
	Loom.print_config();

	// pinMode(ALARM_PIN, INPUT_PULLUP);
	// pinMode(REED_PIN, INPUT_PULLUP);

	Loom.InterruptManager().register_ISR(ALARM_PIN, alarmISR, LOW, ISR_Type::IMMEDIATE);
	Loom.InterruptManager().register_ISR(REED_PIN, reedISR, LOW, ISR_Type::IMMEDIATE);

	LPrintln("\n ** Setup Complete ** ");
}


void loop() 
{
	//required for HYPNOS
	digitalWrite(5, LOW);
	digitalWrite(6, HIGH);
	pinMode(23, INPUT);
	pinMode(24, INPUT);
	pinMode(10, INPUT);

	LPrintln("AlarmFlag : ", alarmFlag);
	LPrintln("ReedFlag  : ", reedFlag);

	digitalWrite(LED_BUILTIN, HIGH);

	//digitalWrite(10, HIGH); //commented out for HYPNOS test
	Loom.SDCARD().power_up(10); //required to power_up SD on alarm wake up
	Loom.pause(200);

	Loom.measure();

	//digitalWrite(10, LOW); //commented out for HYPNOS test

	Loom.package();
	Loom.add_data("wakeType", "type", alarmFlag ? "alarm" : "reed");
	Loom.display_data();
	Loom.SDCARD().log();

	
	Loom.pause(500);
	Loom.InterruptManager().register_ISR(ALARM_PIN, alarmISR, LOW, ISR_Type::IMMEDIATE);
	Loom.InterruptManager().register_ISR(REED_PIN, reedISR, LOW, ISR_Type::IMMEDIATE);
	Loom.InterruptManager().RTC_alarm_duration(TimeSpan(5));

	// delay(4000);

	alarmFlag = false;
	reedFlag = false;

	// required for HYPNOS
	digitalWrite(5, HIGH);
	digitalWrite(6, LOW);
	pinMode(23, OUTPUT);
	pinMode(24, OUTPUT);
	pinMode(10, OUTPUT);

	// Go to sleep
	Loom.SleepManager().sleep();
	// 
	
}
