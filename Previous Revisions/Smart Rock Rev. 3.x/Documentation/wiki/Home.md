# Home

<p align="center">
    <img src="https://user-images.githubusercontent.com/22950096/106803380-03dd9180-6619-11eb-9fe8-4dbe40daf72f.png" alt="logo" height="150"></a>
<p>

Project Leads: **Colin Hale-Brown**, **Brenda Fasse**

<!-- Past team members **Annika Sundstorm** -->

Interested in the project? Email us at: halebroc@oregonstate.edu

<!--**We are taking pre-orders for the V3 Smart Rock at the form [HERE](https://forms.gle/heTsUhmxyKFWzNU9A).**-->
<!--
**Smart Rock Virtual Workshop with CUAHSI**: [Open Hydrological Sensor Technologies: DIY Stream Sensor Networks](https://www.cuahsi.org/education/training/training-and-workshops/open-hydrological-sensor-technologies-diy-stream-sensor-networks):
Monday September 20 - Wednesday September 22, 9:00 am PT  - 12:00 pm PT. [**Register**](https://web.cvent.com/event/a9b4330e-efd9-4988-a294-09152a079004/summary) by August 30 at 11:59 PM ET.
-->
_To return to the OPEnS Lab wiki click [HERE](https://github.com/OPEnSLab-OSU/SmartRock)._

## Overview
Current hydrological modelling is missing data from small and seasonal streams. Data collection on these streams is sparse with measurements, if any data is taken at all. Small streams are often ignored in hydrological modelling by entities that generate public data of water resources. The ecological health of habitats for fish depends on the flow of these small streams during different seasons. monitoring can be expensive and exclusive to organizations that can afford to do so. Current barriers prevent current hydrological modeling being informed by small and seasonal streams. 

Smart Rock aims to create a low-cost device to monitor remote streams through the ideals and goals of citizen science. The device could be used as a learning tool for students, teachers, and other citizen scientists. Deploying Smart Rock in streams will allow for more accurate data collection of small and seasonal streams.

![Cover](https://user-images.githubusercontent.com/22950096/106802651-160b0000-6618-11eb-814b-6e9be7e951d1.jpg)
<!--- https://user-images.githubusercontent.com/22950096/106802651-160b0000-6618-11eb-814b-6e9be7e951d1.jpg, https://user-images.githubusercontent.com/22950096/103161041-477aeb00-4791-11eb-861f-7c8f8370842b.jpg, 98612647-70125880-22a9-11eb-8660-03565f0426d8.png -->

## Description

The Smart Rock is a submersible sensor suite that monitors water depth, temperature, turbidity, and salinity (EC) of a small stream over time and designed to be built by anyone with or without extensive experience in electronics.<!-- Current capabilities of Smart Rock sensors are depth measurement with accuracy within 0.13 mbar resolution as compared to an out of water pressure sensor, temperature accuracy of fewer than 0.01°C, turbidity measured in JTU, and a salinity measurement that increases accuracy to less than 5 parts per million. Battery life for Smart Rock is up to 3 months with low power sleep, a function that limits power usage from the device when dormant. This can be extended by taking data less often than once every 20 minutes.--> The device currently costs ~ $250 with these specifications and custom parts and takes about 10 hours to assemble and program.

<!--
| Specification  | Metric | Value| SR Version | Date |
| ------------- | ------------- | ------------- | ------------- | -------------
| Battery life	| Months  | In Testing | 3 |
| Electrical conductivity | µs | In Testing | 3 |
| MS5803 Pressure | mbar | In Testing | 3 |
| MS5803 Temperature | °C | In Testing | 3 | 
| Turbidity | JTU | In Testing | 3 |
-->

### Device Components Info

<details>
<summary>Adafruit Feather M0 Basic Proto</summary>

General Description/how it works:
	The Feather M0 Basic Proto is an Arduino-compatible microcontroller that runs on 3.3 volts. A 3.3 volt regulator allows for a 3.7 volt lithium polymer battery to be used. The feather has a 500mA peak current, has 20 GPIO pins, 10 analog inputs, and 1 analog output. These pins allow users to connect their sensors and motors to the controller to program readability and functions with Arduino.

Smart Rock Use Validation:
	The Feather M0 Basic Proto acts as the main microcontroller for Smart Rock. Integrated into the electronics stack, the feather gives inputs to sensors and other electronics and reads outputs. Sensors operate on the I2C interface and analog inputs. The Feather saves data to SD in a spreadsheet from the stream on Hypnos.
</details>

<details>
<summary>Pressure/Temperature Sensor</summary>

General Description/how it works: 
The pressure sensor runs on 3 volts from a microcontroller or direct source. The MS5803 Pressure sensor uses piezoresistivity to output pressure readings. Piezoresistivity is the change in electrical resistivity of a semiconductor when mechanical strain is applied. The sensor converts an analog output into a 24 digit output that runs on the I2C protocol. The sensor additionally provides a 24 digit output for temperature. The sensor has been calibrated at 2 temperatures and 2 pressures and 6 coefficients are calculated and stored in a 128-bit PROM. When taking new readings, the device first reads this calibration data. The digital pressure data (D1) and digital temperature data (D2) are read and temperature and pressure are then calculated. Temperature is calculated in two steps: subtracting the read temperature from the reference temperature and comparing to the temperature coefficient from calibration. Then, the electrical sensitivity is read and the actual temperature calculation is used in another calculation regarding the pressure offset caused by temperature. Following I2C protocol communication, SDA (Serial Data) output conveys the pressure and temperature readings to a microcontroller.

![pressure](https://user-images.githubusercontent.com/55994278/68499563-51006700-020e-11ea-9e18-eb9015dd35ad.png)

MS580302BA Water Level Spec
| Pressure | Condition | Min | Max | Unit |
| -------- | --------- | --- | --- | ---- |
| Operating Range | Full Accuracy | 300 | 1100 | mbar |
| Extended Range | Linear Range | 10 | 2000 | mbar |
| Absolute Accuracy | at 25°C |  |  |  mbar |
| Absolute Accuracy | at 25°C |  |  |  mbar |
| Absolute Accuracy | at 25°C |  |  |  mbar |
| Absolute Accuracy | at 25°C |  |  |  mbar |
| Maximum Error | VDD=1.8V...3.6V | -2.5 | +2.5 | mbar |
| Stability |  | -1 | +1 | mbar/yr |

MS580302BA Water Temperature Spec
| Temperature | Condition | Min | Max | Unit |
| ----------- | --------- | --- | --- | ---- |
| Range |  | -40 | +85 | °C |
| Absolute Accuracy | at 25°C | -0.8 | +0.8 | °C |
| Absolute Accuracy | -20...85°C | -2.0 | +2.0 | °C |
| Absolute Accuracy | -40...85°C | -4.0 | +4.0 | °C |
| Maximum Error | VDD=1.8V...3.6V |-0.5 | +0.5 | °C |

The data above is from the data sheet provided by the manufacturer, a complete data sheet for the sensor can be found [here](https://www.te.com/commerce/DocumentDelivery/DDEController?Action=showdoc&DocId=Data+Sheet%7FMS5803-02BA%7FB3%7Fpdf%7FEnglish%7FENG_DS_MS5803-02BA_B3.pdf%7FCAT-BLPS0010) if you are interested in more details.

Smart Rock Use Validation:
	The pressure and temperature gives a two for one. Costing $10.72, this sensor provides the two primary measurements we need with one sensor. Measuring temperature and depth of a stream are the most useful in determining basic data about a remote and unknown stream. With a custom PCB designed for this sensor, connecting the sensor to the microcontroller is made easier. Following I2C protocol, the sensor is already implemented into LOOM_Library. This allows for the programming of the system to be simple. The sensor gives accurate and useful data within our budget. The size of the sensor is also fairly small and easy to make water proof.

</details>

<details>
<summary>Turbidity Sensor</summary>

General Description/ How it works:
	Turbidity is the measurement of the cloudiness in a liquid. This sensor uses a measurement of light transmittance to determined the total suspended solids (TSS) in the liquid. TSS increases with turbidity. Turbidity is measured in JTU which can be used to determine the cleanliness of the water, water erosion, and pollution. The sensor gives an analog output that can be converted to a measurement in JTU. Using a laser signal between two nodes, the device can convert cloudiness to JTU.

Smart Rock Use Validation:
	Turbidity in a stream can indicate the overall quality of the water and gives an idea for the amount of erosion occurring. Adding this sensor to the Smart Rock is both cheap and simple. The sensor from DF Robot costs $9.90, making it easy to keep Smart Rock inexpensive. The sensor can be hooked up to the Smart Rock through three easy connections, 3V power, GND, and an analog port. Implementing the sensor board to the electronics is relatively simple because it comes with a PCB that can be wired to the Smart Rock EC Breakout Board.

![Turbidity](https://user-images.githubusercontent.com/55994278/68499653-92911200-020e-11ea-93e1-7fa27406e73d.png)

</details>

<details>
<summary>Salinity Sensor</summary>

General Description/How it works:
	TDS measures the amount of organic and inorganic dissolved solids in the liquid. Using electrical conductivity, the sensor gives an analog reading that corresponds to the amount of minerals in the water. The sensor has two probes and the interference between them changes the voltage and an analog reading can be taken. The sensor is built into the same board as the MS5803 and connects to the EC Breakout Board on the electronics stack.

Smart Rock Use Validation:
	Having a salinity measurement on the Smart Rock is cost effective and important to proving the capability of the sensor package. Electrical conductivity gives an idea to the amount of salts and minerals in the stream and can be used to determine the overall health of the stream. With this sensor costing ~$15.00, much less than similar probes, the price of having this on the Smart Rock is low enough to implement. The size of the probe is small and can be sealed to be waterproof easily.
</details>

<details>
<summary>OPEnS Lab Hypnos</summary>

General Description/ How it works:
	The Hypnos board is an attachable precision I2C integrated real time clock and data logger. A crystal is used to keep time and is temperature compensated inside the chip. A coin cell battery is plugged into the board to keep time even when the a feather battery is not connected. Data can be saved and read from SPI or I2C protocol communication.

Smart Rock Use Validation:
	The Smart Rock is using the Hypnos to keep temperature compensated time as well as storing all the data read by the sensors while in the stream bed. Smart Rock takes data every 20 minutes and this device allows such to happen. The RTC sends a square wave signal to a digital pin on the feather to wake the device from the power sleep to take data. Having this RTC allows for the device to keep time even in a low-power sleep mode.

More information about the Hypnos Board can be found [here](https://github.com/OPEnSLab-OSU/OPEnS-Lab-Home/wiki/Hypnos).
</details>

### Casing Design

The **outer case** is made of a piece of PVC with an union fitting at one end and a cap at the other. The union fitting and cap are mounted to the PVC using a layer of primer, then a layer of PVC cement. The smaller diameter, unthreaded, section of the union fitting is discarded and replaced with a circular piece of acrylic. This piece of acrylic has laser-cut holes for the sensors to be epoxied to make water-tight. The o-ring in the union fitting is coated in silicone grease to ensure a waterproof seal when the end of the union fitting is screwed back on with the acrylic. This modded union fitting design is used so that the electronics may be accessed and so that we can have the sensors protruding from one end without getting their wires twisted and tangled when the end is removed. 

![SmartRock_Enclosure](https://user-images.githubusercontent.com/22950096/124837006-dfc00c80-df38-11eb-9002-7ebd81290e0e.PNG)
_*Note this image is just the PVC enclosure._

The **internal structure** is made up of an acrylic platform that slides into the PVC enclosure. The electronics are then mounted this acrylic structure and slid into the case. Using the acrylic structure makes it easy to remove/access the electronics and holds everything in place. The electronics stack up on the slide allowing for a compact design.

![SmartRock_AcrylicStructure](https://user-images.githubusercontent.com/22950096/124837952-b56f4e80-df3a-11eb-936f-739e94609acf.PNG)
_*Note that the image above does not include electronics._

## Objectives

*  Low cost

*  Durable

*  Senses underwater pressure for depth

*  Senses stream temperature

*  Senses turbidity

*  Senses salinity

*  Battery life of at least 3 months

*  Clean and user-friendly electronics packaging

*  Keeps time for data collections

*  Connects to user easily

*  Waterproof

*  Remains in the location of placement

*  Safe for the environment

*  Withstand freezing temperatures

*  Easy internal access

*  Easy to retrieve and transport

## Outcomes

Current capabilities of Smart Rock sensors are depth measurement with accuracy within 0.13 mbar resolution as compared to an out of water pressure sensor, temperature accuracy of fewer than 0.01°C, turbidity measured in JTU, and a salinity measurement with an accuracy of less than 5 parts per million. Future developments will have flow sensing from the use of multiple high-accuracy pressure sensors. Battery life for Smart Rock is up to 3 months with low power sleep, a function that limits power usage from the device when dormant. This can be extended by taking data less often than once every 20 minutes. The device currently costs ~ $250 with these specifications and custom parts and takes about 10 hours to assemble and program.

<!--
### Field Test January 2020
![FieldTestphoto](https://user-images.githubusercontent.com/22950096/98614763-ef099000-22ad-11eb-8338-27d382e8bbb8.JPG)
![Turbidityresults](https://user-images.githubusercontent.com/46762333/80996902-72c15c00-8df5-11ea-9c2e-b5dc42e5fc3a.JPG)
![TDSResults](https://user-images.githubusercontent.com/46762333/80996988-91275780-8df5-11ea-907d-722e793f9230.JPG)
![BatteryResults](https://user-images.githubusercontent.com/46762333/80997060-ad2af900-8df5-11ea-9e59-19daa2c9bf59.JPG)
-->

## Future

The Smart Rock team is developing and revising the Smart Rock to improve the user experience and improve the quality of the Smart Rock. 

## Resource List

Link to Github page where code, design files, and guides can be found [here](https://github.com/OPEnSLab-OSU/SmartRock).

### Tutorials

Here are Resources from the 2019 CUAHSI workshop can be found [here](https://github.com/OPEnSLab-OSU/SmartRock/tree/master/Workshop%20Materials https://github.com/OPEnSLab-OSU/SmartRock/tree/master/Workshop%20Materials)

## Key Words
OPEnS, SmartRock, Smart Rock, Feather M0, Adalogger, Arduino, Stream, Water Monitor, Hydrological Data, Hydrological Monitoring, Pressure, Temperature, Electrical Conductivity, Dissolved Solids, Turbidity, seasonal streams, small streams

## References

Software

*  Fusion 360. (2018). San Rafael, California: Autodesk.

*  EAGLE CAD. (2018). San Rafael, California: Autodesk.

*  Arduino IDE. (2020). Turin, Italy: Arduino
