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

int sensorPin_1 = A0; // hook up first sensor
int sensorPin_2 = A2; // hook up second sensor

int sensorValue_1 = 0; // initialize sensor 1 value to zero
int sensorValue_2 = 0; // initialize sensor 2 value to zero

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

    sensorValue_1 = analogRead(sensorPin_1); // store sensor 1 pin value 
    sensorValue_2 = analogRead(sensorPin_2); // store sensor 2 pin value

    Serial.println(sensorValue_1); // plot sensor 1 value via serial plotter
    Serial.print(","); // seperator; essential to have seperate graphed lines in serial plotter 
    Serial.println(sensorValue_2); // plot sensor 2 value via serial plotter
    delay(20); // wait 20ms so that data is spaced out just enough to be readable

    Loom.pause(1000);
}
