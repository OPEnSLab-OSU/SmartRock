/////////////////////////////////////////////////////

//code for OPEnS Lab's Smart Rock project
//Test code to log live data and display it in real time

/////////////////////////////////////////////////////

#include <Loom.h>

const char* json_config =
#include "config.h"
;

LoomFactory<
	Enable::Internet::Disabled,
	Enable::Sensors::Enabled,
	Enable::Radios::Enabled,
	Enable::Actuators::Enabled,
	Enable::Max::Enabled
> ModuleFactory{};

LoomManager Loom{ &ModuleFactory };

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

  LPrintln("\n ** Setup Complete ** ");
}

void loop()
{
    Loom.measure();
    Loom.package();
    Loom.SDCARD().log();

    Loom.pause(1000);
}
