# Smart Rock | [Updates](https://github.com/OPEnSLab-OSU/OPEnS-Lab-Home/wiki/smart-rock-updates) | [Wiki](https://github.com/OPEnSLab-OSU/OPEnS-Lab-Home/wiki/Smart-Rock)
Project Leads: **Colin Hale-Brown**, **Martin Escoto**, and **Alicia Veach**

Interest in the project? Email us at: halebroc@oregonstate.edu

- [x] Latest hardware version: 3
- [x] Latest software version: 2.5

The Smart Rock is a submersible sensor suite that monitors water depth, temperature, turbidity, and salinity (EC) of a small stream over time and designed to be built by anyone with or without extensive experience in electronics.

## Smart Rock Validation
 
<details><summary>Hardware Requirements</summary>

* Acrylic cap forms watertight seal with the union fitting.
* No lose components inside the Smart Rock.
* Sensors are robust enough to be deployed for one or more deployments.
* Electronics are accessible and easy to maintain.
* Materials used will not pollute or damage the environment. 
* Can withstand freezing temperatures.
* Have reliable mounting points for fixing the Smart Rock during testing and deployment.
</details>

<details><summary>Electronics Requirements</summary>

* EC Sensor is reporting consistent data.
* Turbidity sensor is reporting consistent data.
* MS5803 can sense pressure reliably
* MS5803 can sense temperature reliably  
* Battery life could last 4 months or more with default/ recommended settings.
* Sensor Data can be reliably be stored.
* All wires have unique connectors to make miss-wiring impossible.
</details>

<details><summary>Software Requirements</summary>

* Smart Rock can sleep for prolonged battery life.
* Set RTC through serial. 
* Records time along with data.
* With the use of the onboard switch, the Smart Rock has two modes.
* Settings for modes must be configurable.
* Code is robust enough to run without error for 3-6 months.
</details>

<!--

## Bill of Materials

<details><summary>Bill of Materials</summary>

This bill of materials in the complete bill of materials and what you will recieve in each kit. For info about the materials and assembly of the custom PCBs please visit the PCB folder and read the corresponding README.

Kits | Type
---- | ----
A | Fully Assembled
B | To be Assembled
C | In house parts only

**Mechanical**

Item Description | Notes | Quantity per 1 SR | Part Number | Dist. Website | In kits 
------ | ------ | ------ | ------- | ------ | ------ 
PVC Pipe (Quantity in inches) | 2.5" pipe | 4.125 | 5AFJ8 | [Grainger](https://www.grainger.com/product/GRAINGER-APPROVED-Pipe-5AFJ8?) | A,B
PVC Union Fitting | Only part of the fitting is used, cemented onto pipe | 1 | 457-025 | [SupplyHouse](https://www.supplyhouse.com/Spears-457-025-2-1-2-PVC-Sch-40-Socket-Union-w-Buna-N-O-ring) | A,B
PVC Cap Fitting | Cemented onto pipe | 1 | 447-025 | [SupplyHouse](https://www.supplyhouse.com/Spears-447-025-2-1-2-PVC-Schedule-40-Cap) | A,B
Acrylic_Faceplate | Laser cut from 1/4" extruded acrylic. | 1 | #### | [McMasterCarr](https://www.mcmaster.com/8560K357/) | A,B,C
Sled_Base | Laser cut from 1/8" extruded acrylic. | 1 | #### | [McMasterCarr](https://www.mcmaster.com/8589K43/) | A,B,C
Electronics_Mount | Laser cut from 1/8" extruded acrylic. | 1 | #### | [McMasterCarr](https://www.mcmaster.com/8589K43/) | A,B,C
Turbidity_Mount | Laser cut from 1/8" extruded acrylic. | 1 | #### | [McMasterCarr](https://www.mcmaster.com/8589K43/) | A,B,C
3" Velcro Cable Tie |  | 1 | 4330221319 | [Amazon](https://www.amazon.com/dp/B00QMMKY8I/) | A,B
Battery_Mount | 3D Printed | 1 | #### |  | A,B,C
Turbidity_Cover | 3D Printed | 1 | #### |  | A,B,C
Rail_Outside | 3D Printed | 1 | #### |  | A,B,C
Rail_Inside | 3D Printed | 1 | #### |  | A,B,C
8mm M3 Screw |  | 2 | 91292A112 | [McMasterCarr](https://www.mcmaster.com/91292a112) | A,B
10mm M3 Screw |  | 4 | 91292A113 | [McMasterCarr](https://www.mcmaster.com/91292A113/) | A,B
M3 Nut |  | 10 | 91828A211 | [McmasterCarr](https://www.mcmaster.com/91828A211/) | A,B

**Electrical**

Item Description | Notes | Quantity per 1 SR | Part Number | Dist. Website | In kits 
------ | ------ | ------ | ------- | ------ | ------ 
Feather M0 Basic Proto | Microcontroller | 1 | 2772 | [Adafruit](https://www.adafruit.com/product/2772) | A,B
Hypnos Board | Data logging, system power, real time clock. | 1 | #### |  | A,B,C
MicroSD Card with adapter | For storing data in Hypnos. | 1 | #### | [Amazon](https://www.amazon.com/SanDisk-Mobile-MicroSDHC-SDSDQM-B35A-Adapter/dp/B004ZIENBA/) | A,B
CR1220 Coin Cell | For keeping time when battery is removed. | 1 | 54ZU79 | [Grainger](https://www.grainger.com/product/GRAINGER-APPROVED-1220-54ZU79) | A,B
Battery Charger | Charge lipo battery cell | 1 | 1304 | [Adafruit](https://www.adafruit.com/product/1304) | A,B
Lithium Ion Battery | 3.7V 2200mAh | 1 | 1781 | [Adafruit](https://www.adafruit.com/product/1304) | A,B
3-pin JST Cable | 100mm long | 1 | 4336 | [Adafruit](https://www.adafruit.com/product/4336) | A,B
Short Male Header | For Hypnos and Feather Boards | 2 | 3002 | [Adafruit](https://www.adafruit.com/product/3002) | A,B
Short Female Header | For Hypnos and EC Breakout Boards | 2 | 2940 | [Adafruit](https://www.adafruit.com/product/2940) | A,B
OsmoPod | MS5803 and EC | 1 | #### |  | A,B,C
EC Breakout Board | Main Board | 1 | #### |  | A,B,C

**Assembly, Calibration, and Deployment**

Item Description | Notes | Quantity per 1 SR | Part Number | Dist. Website | In kits 
------ | ------ | ------ | ------- | ------ | ------ 
Lead-free Solder | 
Marine Epoxy | 
Super Glue |
Popsicle Stick |
30 mL Cups |
3 mL Pipette
DI Rinse Pouch |
10 μS/cm calibration pouch |
447 μS/cm calibration pouch |
1213 μS/cm calibration pouch |
Desicant Packets | 
</details>

## Assembly Guide

<details><summary>Enclosure Assembly</summary>

**Materials**

* PVC Enclosure *(Assuming it is fully assembled and cemented in place)*
* Rail_Outside

Additional Materials

* Super Glue

**Enclosure Assembly Procedure**

1. Remove the cap on the PVC enclosure

2. Apply super glue to the curved bottom of the Rail_Outside *(be careful not to apply it to the retaining clip)*

3. Align the front edge of the Rail_Outside with the front edge of the pipe and apply pressure until the super glue has set. *(Try and make it as straight as possible to make sliding the electronics as easy as possible.)*
</details>
<details><summary>Sled Assembly</summary>

**Materials**

* Rail_Inside
* Sled_Base
* Electronics_Mount
* Turbidity_Mount
* Battery_Mount
* 8mm M3 Screws (2x)
* 10mm M3 Screws (4x)
* M3 Nuts (10x)
* Turbidity Breakout Board
* EC Breakout Board
* 3-pin JST Cable *(Male to Male)*

Additional Materials

* Super Glue

**Sled Assembly Procedure**

1. Find the top and bottom of the sled *(Large cutout on the right)* and align the rail with its indicator on the bottom of the sled. 

2. Apply super glue to the top of the rail and using the indicator and bottom face apply pressure and hold the rail aligned until the glue is set.

1. To start assembling the sled, populate the Turbidity and EC Breakout Mounts with 10mm M3 screws and capture them with nuts.

2. Add the turbidity breakout board to the Turbidity_Mount and the EC breakout board to the Electronics_Mount on their stand-offs and capture them with another nut.

3. Matching the tabs and corresponding slots, attach the Electronics_Mount and the Battery_Mount together fitting the velcro into the provided channel.

3. Slip the Turbidity_Mount onto the Battery_Mount and slide back to connect onto the remaining tabs on the Electronics_Mount.

4. Drop the assembly onto the sled in the corresponding tabs and mount with the two 8mm M3 screws captured with nuts on the underside of the Sled_Base.

5. Plug-in the 3-pin JST cable to the EC Breakout Board and twist the cable to wind it once then plug the other end into the Turbidity Breakout Board. 
</details>

<details><summary>Component Assembly</summary>

<details><summary>End Cap Assembly</summary>

**Materials**

* Acrylic Faceplate
* Turbidity Sensor

Additional Materials

* 30mL cup
* popsicle stick
* Marine Epoxy
* Super glue
* Scissors
* Paper Towels

**End Cap Assembly Procedure**

1. Prep the Turbidity sensor by using the scissors to trim the two mounting holes off.

2. Cut the tip of the marine epoxy with the scissors - *be careful as it will ooze after opening*

3. Squeeze out 15 ml of marine epoxy into the 30 ml cup and mix thoroughly using a popsicle stick.

4. Apply marine epoxy around the edge of the turbidity sensor.

5. On the faceplate, apply super glue around the turbidity sensor's hole on the inside face where the turbidity sensor will contact the acrylic faceplate.

6. Insert the turbidity sensor into the hole. The black plastic peg should point directly at the slot on the faceplate.

7. Press the turbidity sensor into the hole, apply super glue to the end of each arm on the sensor and apply the sensor cover. Hold until the super glue sets. 

8. Use the popsicle stick to move or add epoxy to turbidity sensor to create a good seal on the inside of the faceplate.

8. On the outside of the acrylic plate, apply epoxy to the lip around the turbidity sensor cover. 

10. If needed, use the popsicle stick to move or apply more epoxy to the sensor cover.

11. Set somewhere safe to dry for at least 4 hours, overnight if possible.
</details>
</details>

## Test Procedures

<details><summary>Test for Leaks</summary>

1. Start by removing the sled if it is installed in the smart rock and preparing a tub or bucket of water.

2. Add silicone greese to the o-ring to help create a good seal.

2. Add the acrylic faceplate and seal union fitting with an empty smart rock. 

3. Completely submerge the Smart Rock in water and hold it there for 30 seconds.

4. Check for leaks by looking for, water pooling inside the Smart Rock. If there are none resubmerge for 3 to 5 minutes.

5. Check for water inside the Smart Rock, if none can be seen then check the o-ring is compressed. 

6. If all looks in order unscrew the union fitting and fell for water inside. If there is no water inside the smart rock it is not leaking.
</details>

<details><summary>Test EC Breakout Board</summary>


</details>
<details><summary>Test and Calibrate the Turbidity Sensor</summary>


</details>
<details><summary>Test and Calibrate the EC and MS5803 Sensors</summary>


</details>
<details><summary> </summary>


</details>

## Operation Guide

-->
