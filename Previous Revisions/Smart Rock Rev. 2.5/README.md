# Smart Rock | [Updates](https://github.com/OPEnSLab-OSU/OPEnS-Lab-Home/wiki/smart-rock-updates) | [Github](https://github.com/OPEnSLab-OSU/SmartRock)
Project Leads: **Alicia Veach**, **Martin Escoto**, and **Colin Hale-Brown**

Interest in the project? Email us at: halebroc@oregonstate.edu

## Overview
Current hydrological modelling is missing data from small and seasonal streams. Data collection on these streams is sparse with measurements, if any data is taken at all. Small streams are often ignored in hydrological modelling by entities that generate public data of water resources. The ecological health of habitats for fish depends on the flow of these small streams during different seasons. monitoring can be expensive and exclusive to organizations that can afford to do so. Current barriers prevent current hydrological modeling being informed by small and seasonal streams. 

Smart Rock aims to create a low-cost device to monitor remote streams through citizen science. The device could be used as a learning tool for students, teachers, and other citizen scientists. Deploying Smart Rock in streams will allow for more accurate data collection of small and seasonal streams.


![Cover](https://user-images.githubusercontent.com/22950096/98612647-70125880-22a9-11eb-8660-03565f0426d8.png)<!--- {{:20190427_164150.jpg?400|}} -->
## Description

The Smart Rock is a submersible sensor suite that monitors water depth, temperature, turbidity, and salinity (EC) of a small stream over time and designed to be built by anyone with or without extensive experience in electronics.
Current capabilities of Smart Rock sensors are depth measurement with accuracy within 0.13 mbar resolution as compared to an out of water pressure sensor, temperature accuracy of fewer than 0.01°C, turbidity measured in JTU, and a salinity measurement that increases accuracy to less than 5 parts per million. Battery life for Smart Rock is up to 3 months with low power sleep, a function that limits power usage from the device when dormant. This can be extended by taking data less often than once every 20 minutes. The device currently costs ~ $200 with these specifications and custom parts and takes about 10 hours to assemble and program.


**Adafruit Feather M0 Basic Proto**

<details>
<summary>Show More</summary>

General Description/how it works:
	The Feather M0 Basic Proto is an Arduino-compatible microcontroller that runs on 3.3 volts. A 3.3 volt regulator allows for a 3.7 volt lithium polymer battery to be used. The feather has a 500mA peak current, has 20 GPIO pins, 10 analog inputs, and 1 analog output. These pins allow users to connect their sensors and motors to the controller to program readability and functions with Arduino.

Smart Rock Use Validation:
	The Feather M0 Basic Proto acts as the main microcontroller for Smart Rock. Integrated into the PCB, the feather gives inputs to sensors and other electronics and reads outputs. Sensors operate on the I2C interface and analog inputs. The Feather saves data to SD in a spreadsheet from the stream on Hypnos.
</details>

**Pressure/Temperature Sensor**

<details>
<summary>Show More</summary>

General Description/how it works: 
The pressure sensor runs on 3 volts from a microcontroller or direct source. The MS5803 Pressure sensor uses piezoresistivity to output pressure readings. Piezoresistivity is the change in electrical resistivity of a semiconductor when mechanical strain is applied. The sensor converts an analog output into a 24 digit output that runs on the I2C protocol. The sensor additionally provides a 24 digit output for temperature. The sensor has been calibrated at 2 temperatures and 2 pressures and 6 coefficients are calculated and stored in a 128-bit PROM. When taking new readings, the device first reads this calibration data. The digital pressure data (D1) and digital temperature data (D2) are read and temperature and pressure are then calculated. Temperature is calculated in two steps: subtracting the read temperature from the reference temperature and comparing to the temperature coefficient from calibration. Then, the electrical sensitivity is read and the actual temperature calculation is used in another calculation regarding the pressure offset caused by temperature. Following I2C protocol communication, SDA (Serial Data) output conveys the pressure and temperature readings to a microcontroller.

Smart Rock Use Validation:
	The pressure and temperature gives a two for one. Costing $10.72, this sensor provides the two primary measurements we need with one sensor. Measuring temperature and depth of a stream are the most useful in determining basic data about a remote and unknown stream. With a custom PCB designed for this sensor, connecting the sensor to the microcontroller is made easier. Following I2C protocol, the sensor is already implemented into LOOM_Library. This allows for the programming of the system to be simple. The sensor gives accurate and useful data within our budget. The size of the sensor is also fairly small and easy to make water proof.

![pressure](https://user-images.githubusercontent.com/55994278/68499563-51006700-020e-11ea-9e18-eb9015dd35ad.png)

</details>

**Turbidity Sensor**

<details>
<summary>Show More</summary>

General Description/ How it works:
	Turbidity is the measurement of the cloudiness in a liquid. This sensor uses a measurement of light transmittance to determined the total suspended solids (TSS) in the liquid. TSS increases with turbidity. Turbidity is measured in JTU which can be used to determine the cleanliness of the water, water erosion, and pollution. The sensor gives an analog output that can be converted to a measurement in JTU. Using a laser signal between two nodes, the device can convert cloudiness to JTU.

Smart Rock Use Validation:
	Turbidity in a stream can indicate the overall quality of the water and gives an idea for the amount of erosion occurring. Adding this sensor to the Smart Rock is both cheap and simple. The sensor from DF Robot costs $9.90, making it easy to keep Smart Rock inexpensive. The sensor can be hooked up to the Smart Rock through three easy connections, 3V power, GND, and an analog port. Implementing the sensor board to the electronics is relatively simple because it comes with a PCB that can be wired to the Smart Rock base PCB.

![Turbidity](https://user-images.githubusercontent.com/55994278/68499653-92911200-020e-11ea-93e1-7fa27406e73d.png)

</details>

**Salinity Sensor**

<details>
<summary>Show More</summary>

General Description/How it works:
	TDS measures the amount of organic and inorganic dissolved solids in the liquid. Using electrical conductivity, the sensor gives an analog reading that corresponds to the amount of minerals in the water. The sensor has two probes and the interference between them changes the voltage and an analog reading can be taken. The sensor kit comes with its own PCB, the electrical conductivity probe, and the required connectors.

Smart Rock Use Validation:
	Having a salinity measurement on the Smart Rock is cost effective and important to proving the capability of the sensor package. Electrical conductivity gives an idea to the amount of salts and minerals in the stream and can be used to determine the overall health of the stream. With this sensor costing $12.90, much less than similar probes, the price of having this on the Smart Rock is low enough to implement. The size of the probe is fairly small and can be sealed to be waterproof easily.
</details>

**OPEnS Lab Hypnos**

<details>
<summary>Show More</summary>

General Description/ How it works:
	The Hypnos board is an attachable precision I2C integrated real time clock and data logger. A crystal is used to keep time and is temperature compensated inside the chip. A coin cell battery is plugged into the board to keep time even when the a feather battery is not connected. Data can be saved and read from SPI or I2C protocol communication.

Smart Rock Use Validation:
	The Smart Rock is using the Hypnos to keep temperature compensated time as well as storing all the data read by the sensors while in the stream bed. Smart Rock takes data every 10 minutes and this device allows such to happen. The RTC sends a square wave signal to a digital pin on the feather to wake the device from the power sleep to take data. Having this RTC allows for the device to keep time even in a low-power sleep mode.

More information about the Hypnos Board can be found [here](https://github.com/OPEnSLab-OSU/OPEnS-Lab-Home/wiki/Hypnos).
</details>

<!--
**Reed Switch**

<details>
<summary>Show More</summary>

General Description/ How it works:
	A reed switch is a small device that closes/open when interacting with a magnetic field. It can be used for keeping a device off until opened, for example, a laptop screen. Always open reed switches remain open until a magnet is nearby. Then, it closes and allows current to flow through as a closed wire. Inside the switch there are two wires that are separated and held within a plastic frame. When a magnet is near, the two wire touch and allow current to flow.

Smart Rock Use Validation:
	The always open Reed switch for the Smart Rock is used as an interrupt. The device remains asleep until a user interacts with it with a magnet. The device can then wake and collect data to be transferred. The reed switch allows the battery to be saved by keeping the device off until it is used to collect and transfer data. The switch costs $1.08 for one, cheap and easy to implement. With LOOM, an interrupt can be easily added to wake the device when current flows from the ground to a desired pin, when the reed switch is closed.
</details>

**pH Sensor**

<details>
<summary>Show More</summary>

General Description/ How it works:
 pH is the measurement of hydrogen in a solution. This indicates the acidity of the water which is useful for the biological systems impacted by the stream. This pH sensor uses a pH composite electrode that gives a reading in millivolts that can be converted directly to pH using an analog reading. When calibrated, this probe has accuracy of +_ 0.1pH. 

Smart Rock Use Validation: 
This pH probe from DF robot comes with a pcb and the probe in standard solution. Although this probe is a lab grade probe and not meant for long-term submersion, this probe costs $29.50 and can give a good short term estimate of stream pH. Other probes tend to cost much more and are too bulky for the Smart Rock application. Having an estimate of pH can give information about the biological health of a stream. This pH sensor is also implemented into LOOM.

![ph](https://user-images.githubusercontent.com/55994278/68499450-1ac2e780-020e-11ea-8a1e-4b88694d1a3e.png)

</details>
-->

### Casing Design

The **outer Case** is made of a piece of PVC with union fittings attached to either end. The union fittings are mounted to the PVC using a layer of primer, then a layer of PVC cement. The smaller diameter, unthreaded, section of the union fitting is discarded and replaced with a circular piece of acrylic. This piece of acrylic has laser-cut holes for the sensors to be epoxied to make water-tight. The o-ring in the union fitting is coated in silicone grease to ensure a waterproof seal when the end of the union fitting is screwed back on with the acrylic. This modded union fitting design is used so that the electronics may be accessed and so that we can have the sensors protruding from one end without getting their wires twisted and tangled when the end is removed. 

![IMG_20190507_130956](https://user-images.githubusercontent.com/22950096/98614002-5d4d5300-22ac-11eb-9148-3ed21c823566.jpg)
_*Note that the image above does not include full electronics or official electronics layout._

The **internal Structure** is made up of a 3D printed rail and an acrylic platform. One section of the rail is glued to the inside of the PVC, the other section is glued to a length of acrylic. The electronics are then mounted using velcro to this acrylic and slide into the case using the rail system. Using the rail and acrylic slide makes it easy to remove/access the electronics and holds everything in place. The electronics stack up on the slide allowing for a compact design

![IMG_20190507_130937](https://user-images.githubusercontent.com/22950096/98614115-a43b4880-22ac-11eb-96a5-9fa5778ba7c6.jpg)
_*Note that the image above does not include full electronics or official electronics layout._


## Objectives

### Overall Targets:

*  Low cost

*  Durable

### Electrical Function Targets:
<details>
<summary>Show More</summary>

*  Senses underwater pressure for depth

*  Senses stream temperature

*  Senses turbidity

*  Senses salinity

*  Battery life of at least 1 week

*  Clean and user-friendly electronics packaging

*  Keeps time for data collections

*  Connects to user easily
</details>

### Casing Function Targets:
<details>
<summary>Show More</summary>

*  Waterproof

*  Remains in the location of placement

*  Electronics are securely mounted

*  Simple design

*  Aesthetically pleasing

*  Safe for the environment

*  Withstand freezing temperatures

*  Easy internal access

*  Easy to retrieve and transport
</details>

## Outcomes

Current capabilities of Smart Rock sensors are depth measurement with accuracy within 0.13 mbar resolution as compared to an out of water pressure sensor, temperature accuracy of fewer than 0.01°C, turbidity measured in JTU, and a salinity measurement with an accuracy of less than 5 parts per million. Future developments will have <!--pH sensing and--> flow sensing from the use of multiple high-accuracy pressure sensors. Battery life for Smart Rock is up to 3 months with low power sleep, a function that limits power usage from the device when dormant. This can be extended by taking data less often than once every 20 minutes. The device currently costs ~ $200 with these specifications and custom parts and takes about 10 hours to assemble and program.

### Field Test January 2020
![FieldTestphoto](https://user-images.githubusercontent.com/22950096/98614763-ef099000-22ad-11eb-8338-27d382e8bbb8.JPG)
![Turbidityresults](https://user-images.githubusercontent.com/46762333/80996902-72c15c00-8df5-11ea-9c2e-b5dc42e5fc3a.JPG)
![TDSResults](https://user-images.githubusercontent.com/46762333/80996988-91275780-8df5-11ea-907d-722e793f9230.JPG)
![BatteryResults](https://user-images.githubusercontent.com/46762333/80997060-ad2af900-8df5-11ea-9e59-19daa2c9bf59.JPG)


## Future

Updating the Smart Rock to improve reliability and ease of use. Simplifying electronics so that the salinity sensor board is built into the main feather breakout and replacing all the dupont wires and standardizing to JST connectors to make assembly straightforward and user-friendly.
 
Preparing for CUAHSI workshop in summer 2020.

## Resource List

The Bill of Materials for the current iteration of the Smart Rock can be found [here](https://github.com/OPEnSLab-OSU/SmartRock/blob/master/Smart%20Rock%20Rev%202.5%20Bill%20of%20Materials%20for%20GitHub.xlsx).

Link to Github page with code and PCB design files can be found [here](https://github.com/OPEnSLab-OSU/SmartRock).

### Tutorials

Here are Resources from the 2019 CUAHSI workshop can be found [here](https://github.com/OPEnSLab-OSU/SmartRock/tree/master/Workshop%20Materials)

## Key Words
OPEnS, SmartRock, Smart Rock, Feather M0, Adalogger, Arduino, Stream, Water Monitor, Hydrological Data, Hydrological Monitoring, Pressure, Temperature, Electrical Conductivity, Dissolved Solids, Turbidity, pH, seasonal streams, small streams

## References

Software

*  Fusion 360. (2018). San Rafael, California: Autodesk.

*  EAGLE CAD. (2018). San Rafael, California: Autodesk.

*  Arduino IDE. (2020). Turin, Italy: Arduino
