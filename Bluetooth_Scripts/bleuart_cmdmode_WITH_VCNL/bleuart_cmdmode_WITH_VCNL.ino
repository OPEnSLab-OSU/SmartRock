/***************************************************
  Author: Max Emrich
  Date: 6/3/2025
****************************************************/

#include <Arduino.h>
#include <SPI.h>
#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_SPI.h"
#include "BluefruitConfig.h"

// ───── Feather M0 Bluefruit LE built-in SPI pins ─────
Adafruit_BluefruitLE_SPI ble(8 /*CS*/, 7 /*IRQ*/, 4 /*RST*/);

/* ============================== 
  Turn this on only for one-time factory reset.
  Note: This might be necessary for connecting and
  disconnecting to different devices  
============================== */
#define FACTORYRESET_ENABLE  0

void error(const __FlashStringHelper*err) {
  Serial.println(err);
  while (1); // halt
}

#include <Loom_Manager.h>

#include <Hardware/Loom_Hypnos/Loom_Hypnos.h>
#include <Sensors/I2C/Loom_ADS1115/Loom_ADS1115.h>
#include <Sensors/I2C/Loom_MS5803/Loom_MS5803.h>
#include <Sensors/Loom_Analog/Loom_Analog.h>
#include <Wire.h>
#include "Adafruit_VCNL4010.h"

Adafruit_VCNL4010 vcnl; // We use the VCNL4010, not the 4020
Manager manager("Device", 1);

const int BAUD_RATE = 9600;

void setup(void)
{
  Serial.begin(BAUD_RATE); 
  Wire.begin(); // Intialize I2C

  /* ============================== 
  Initialze Loom Setup 
  ============================== */
  manager.initialize();
  manager.beginSerial(BAUD_RATE);
  delay(500);

  /* ============================== 
  Initialize the VCNL4010 sensor  
  ============================== */
  vcnl.begin();
  if (vcnl.begin() == false) { 
    Serial.println("Couldn't find VCNL4010 sensor!");
    while(1);
  }
  
  /* ============================== 
  Here we start to attempt to connect to the
  UART bridge from the Feather M0 to the UART 
  bridge on our app.

  Explanation of Functions:
  --> ble: is the object that represents our UART bridge,
  functions can be called on this bridge

  --> ble.echo(): whatever is sent from the BLE (sensor) or from
  the app gets sent back (echoes every message) 

  --> ble.setMode(): sets the advertising state of the BLE device,
  in this case, we set it to be constantly and immediately advertising
  the BLE to any other bluetooth capable device in the area (range is TBD) 

  --> ble.sendCommandCheckOK(): returns a boolean based on wheather or not
  the AT+ command was successfully sent to the BLE, true if the command
  was verifiably sent, false otherwise
  ============================== */
  Serial.println(F("Feather M0 Bluefruit -- UART bridge"));
  // 1) initialise the nRF51
  if ( !ble.begin(false /* Verbose = off */) ) {
    error(F("Couldnt find Bluefruit"));
  }
  ble.echo(false);  // turn off echo

  // 2) optional one-time factory reset
  if (FACTORYRESET_ENABLE) {
    if ( !ble.factoryReset() ) {
      error(F("Factory reset failed"));
    }
  }

  // 3) start advertising immediately in UART mode
  ble.setMode(BLUEFRUIT_MODE_DATA);

  Serial.println(F("Ready -- open phone app to UART, tap Connect"));

  // SET A NEW DEVICE NAME:  
  // AT+GAPDEVNAME=new_name
  Serial.println("Trying to change Device Name...");
  if (ble.isConnected()) {
    Serial.println("Changing Device Name...");
    if (!ble.sendCommandCheckOK(F("AT+GAPDEVNAME=FeatherM0+1"))) {
      Serial.println("Error: Could not change Device Name");
    } else {
      Serial.println("Changed Device Name");
    }
  }
}

void loop(void)
{
  Serial.println("testing at top of loop");
  int proximity;
  proximity = vcnl.readProximity();
  Serial.println("Proximity: ");
  Serial.println(proximity);
  delay(100);

  /* ==============================
    IMPORTANT NOTE: nRF can only send 20 byte chunks, so
      if we don't want weird byte splitting when we
      recieve the data on the app, we need to send data 
      neatly in less than or equal to 20 byte chunks

    ANOTHER NOTE: ble.println (as opposed to ble.print ) 
      makes sure to terminate the current 20 byte packet being sent 
      BEFORE 20 bytes so the next chunk doesn't absorb anything 
      from the previous chunks
   ============================== */

  if (ble.isConnected()) {
    ble.println("Current proximity: ");
    ble.println(proximity);
  }

  delay(200);

  // 1) bytes arriving from phone to USB
  while (ble.available()) {   // data waiting from BLE?
    Serial.write(ble.read());
  }
  
  delay(500);
  // 2) bytes typed in Serial Monitor to phone
  while (Serial.available()) {    // data waiting from USB?
    ble.println(Serial.read()); // <---- This is functionality for being able to send to phone by typing into serial monitor
  } 
  delay(500);
}

