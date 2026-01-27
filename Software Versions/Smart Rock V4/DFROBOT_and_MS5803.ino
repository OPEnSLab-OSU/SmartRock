/*!
 * @file getOxygenData.ino
 * @brief Read oxygen concentration ,The unit is concentration percent (% vol).
 * @n step: we must first determine the iic device address, will dial the code switch A0, A1 (ADDRESS_0 for [0 0]), (ADDRESS_1 for [1 0]), (ADDRESS_2 for [0 1]), (ADDRESS_3 for [1 1]).
 * @n Then calibrate the oxygen sensor
 * @n note: it takes time to stable oxygen concentration, about 10 minutes.
 * @n The experimental phenomenon is that a certain percentage of oxygen concentration is printed on the serial port.
 * @n Because the oxygen concentration in oxygen air is certain, the data will not be greater than 25% vol.
 * @copyright Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license The MIT License (MIT)
 * @author ZhixinLiu(zhixin.liu@dfrobot.com)
 * @version V1.0
 * @date 2021-10-22
 * @url https://github.com/DFRobot/DFRobot_OxygenSensor
 */
#include "DFRobot_OxygenSensor.h"

/*
 * i2c slave Address, The default is ADDRESS_3.
 * ADDRESS_0   0x70  i2c device address.
 * ADDRESS_1   0x71
 * ADDRESS_2   0x72
 * ADDRESS_3   0x73
 */
#define Oxygen_IICAddress ADDRESS_3
//#define my_I2C_addy 0x68
#define COLLECT_NUMBER 10  // collect number, the collection range is 1-100.
DFRobot_OxygenSensor oxygen;

#include <Wire.h>
#include "DFRobot_OxygenSensor.h"

#include <Loom_Manager.h>
#include <Hardware/Loom_Hypnos/Loom_Hypnos.h>

#include <Sensors/I2C/Loom_MS5803/Loom_MS5803.h>


//OPEnS Loom Constructors
Manager manager("Data", 1);

// OPEnS Hypnos Constructors
Loom_Hypnos hypnos(manager, HYPNOS_VERSION::V3_3, TIME_ZONE::PST);
Loom_MS5803 ms(manager, 119);

TimeSpan sleepInterval;

bool has_calibrated;
bool first_loop;
float startTime;
float O2_scaling_factor = 0.0;  // scaling factor (this will change later)
float correctedO2 = 0.0;
float O2_offset = 0.0;
bool O2_sensor_good = false;

//int sleepInterval = 1200; // 60 seconds * 20 = 1200 seconds // Units of sleepInterval = SECONDS

// Called when the interrupt is triggered
void isrTrigger() {
  hypnos.wakeup();
}

void setup() {
  startTime = 0.0;
  has_calibrated = false;
  first_loop = true;
  
  hypnos.enable();  // turn on SD rail (and O2 rail)
  delay(100);       // *** important ***

  manager.beginSerial();  // sets up manager serial logging

  manager.initialize();  // <- calls Hypnos::initializeSD() which runs SD.begin()
                         //    RETURNS HERE ONLY if SD mount succeeded

  delay(300);
  // Gets sleep interval from SD card
  sleepInterval = hypnos.getConfigFromSD("SD_config.json");
  // Register the ISR and attach to the interrupt
  hypnos.registerInterrupt(isrTrigger);

  Wire.begin();
  for (byte a = 1; a < 127; a++) {
    Wire.beginTransmission(a);
    if (Wire.endTransmission() == 0) {
      Serial.print("Found device at 0x"); // Find the address of all I2C devices
      Serial.println(a, HEX);
    }
  }

  // Oxygen sensor init
  if (!oxygen.begin(Oxygen_IICAddress)) {
    Serial.println("I2C device number error!");
    delay(1000);
  } else {
    O2_sensor_good = true;
  }
  Serial.println("Oxygen sensor OK");
  /* ---------- ONE-TIME CALIBRATION ----------
     Run once in clean outdoor air, then
     comment this line out. Don’t overwrite
     the key on every reboot.  */
  //oxygen.calibrate(20.9);

}

// ----------------------------------------------------------------------------------------------------------------

void loop() {
  //startTime += sleepInterval;

  // --- Read O2 concentration directly from sensor (register 0x03 = %vol * 1000) --- REMEMBER: This is according to DFROBOT's backend code
  uint16_t rawO2 = 0;
  float o2Percent = NAN;

  if (O2_sensor_good) {
    Wire.beginTransmission(Oxygen_IICAddress);
    Wire.write(0x03);
    Wire.endTransmission();

    delay(100);
    Wire.requestFrom(Oxygen_IICAddress, (uint8_t)2);
    delay(100);
  }

  if (Wire.available() == 2) {
    uint8_t msb = Wire.read();
    uint8_t lsb = Wire.read();
    rawO2 = ((uint16_t)msb << 8) | lsb;
    o2Percent = rawO2 / 1000.0;
  } else {
    Serial.println("Warning: I2C read failed, skipping measurement.");
    o2Percent = NAN;   // don’t reuse previous value
  }
  delay(100);


  // -----------------------------------------------------------------------------
  // DEFINING THE CALIBRATION CONSTANT -------------------------------------------
  // -----------------------------------------------------------------------------
  if (first_loop == true) {
    O2_offset = 20.9 - o2Percent;
    // Note: use averaging of first few samples:
    // take multiple readings, average them, then compute O2_offset
    //oxygen.calibrate(20.9, 26000);
  }
  first_loop = false;
  correctedO2 = o2Percent + O2_offset;
  // -----------------------------------------------------------------------------
  // -----------------------------------------------------------------------------
  // -----------------------------------------------------------------------------

  // // ---- Apply linear correction: scale 26% (or any other value above or below 20.9%) reading to 20.9% ----
  // if (first_loop) O2_scaling_factor = o2Percent;
  // float correctedO2 = (o2Percent / O2_scaling_factor) * 20.9; // Fix this so that this works with whatever value the O2 sensor reads initially (for some period of time, take an average)

  // ---- Print / log ----
  Serial.print("Raw O2 register: ");
  Serial.println(rawO2);
  Serial.print("Raw O2 (% vol): ");
  Serial.println(o2Percent);
  Serial.print("O2 Offset: ");
  Serial.println(O2_offset);
  Serial.print("Corrected O2 (% vol): ");
  Serial.println(correctedO2);

  // Use this instead of getOxygenData()
  manager.measure();
  manager.package();
  manager.addData("DFROBOT", "O2 Vol %", correctedO2);
  manager.addData("DFROBOT", "Raw O2 %", rawO2);
  manager.addData("DFROBOT", "O2 Offset%", O2_offset);

  manager.addData("MS5803", "Pressure", ms.getPressure());
  manager.addData("MS5803", "Temperature", ms.getTemperature());
  manager.display_data(); 
  //manager.display_data();
  hypnos.logToSD();

  hypnos.setInterruptDuration(sleepInterval); // this variable is now USER SET <---- !!! 
  hypnos.reattachRTCInterrupt();

  // Serial.print("CURRENT TIME ELAPSED SINCE START (s): ");
  // Serial.println(startTime);

  hypnos.sleep(false);
}
