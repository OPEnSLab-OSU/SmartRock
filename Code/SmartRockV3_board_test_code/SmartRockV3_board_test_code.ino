///////////////////////////////////////////////////////////////////////////////

// This is simple one of the simplest examples of using Loom. The code used
// in this example shows up in the majority of other cases as well. 

// The include, config, LoomFactory, and LoomManager are typically used in
// this way.

// The setup almost always includes what is in this example, and in many 
// cases, no further setup is necessary

// The loop is also the start of what most cases use, namely: measure,
// package, display, and wait (according to 'interval' in the config).
// Other examples simply build off of this sequence

// Documentation for ADS1115: https://openslab-osu.github.io/Loom/doxygenV2/html/class_loom___a_d_s1115.html

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
	Enable::Radios::Disabled,
	Enable::Actuators::Disabled,
	Enable::Max::Disabled
> ModuleFactory{};

LoomManager Loom{ &ModuleFactory };


//pins for the LEDs
int LED1_pin = 5;
int LED2_pin = 6;
int LED3_pin = 10;


//pin for the switch
const int switchPin = 9;
int switchPos = 0;




void setup() 
{

  pinMode(switchPin, INPUT);
  pinMode(LED1_pin, OUTPUT);
  pinMode(LED2_pin, OUTPUT);
  pinMode(LED3_pin, OUTPUT);

  
   
	Loom.begin_serial(true);
	Loom.parse_config(json_config);
	Loom.print_config();

	LPrintln("\n ** Setup Complete ** ");
  Serial.flush();
}


void loop() 
{

  switchPos = digitalRead(switchPin);

  if(switchPos == HIGH){

    LPrintln("\n***************LED STATUS***************");
    LPrintln("**********************************\n");
    digitalWrite(LED1_pin, HIGH);
    delay(100);
    digitalWrite(LED1_pin, LOW);
    delay(100);
    LPrintln("\n LED 1 Working!");
    
    digitalWrite(LED2_pin, HIGH);
    delay(100);
    digitalWrite(LED2_pin, LOW);
    delay(100);
    LPrintln("\n LED 2 Working!");
    
    digitalWrite(LED3_pin, HIGH);
    delay(100);
    digitalWrite(LED3_pin, LOW);
    delay(100);
    LPrintln("\n LED 3 Working!");
    LPrintln("\n***************************************\n");

    LPrintln("\n***************SWITCH STATUS***************");
    LPrintln("********************************************\n");
    LPrintln("SWITCH == HIGH");
    LPrintln("\n******************************************\n");
    
    
  }else{

    LPrintln("\n***************LED STATUS***************");
    LPrintln("*****************************************\n");
    digitalWrite(LED1_pin, LOW);
    delay(100);
    LPrintln("\n LED 1 is OFF!");
    digitalWrite(LED2_pin, LOW);
    delay(100);
    LPrintln("\n LED 2 is OFF!");
    digitalWrite(LED3_pin, LOW);
    delay(100);
    LPrintln("\n LED 3 is OFF!");
    LPrintln("\n*****************************************\n");

    LPrintln("\n***************SWITCH STATUS***************");
    LPrintln("********************************************\n");
    LPrintln("SWITCH == LOW");
    LPrintln("\n******************************************\n");
    
  }
   
	Loom.measure();
	Loom.package();
	Loom.display_data();
	Loom.pause();

}
