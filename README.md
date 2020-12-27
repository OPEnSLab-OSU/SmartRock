# Smart Rock | [Updates](https://github.com/OPEnSLab-OSU/OPEnS-Lab-Home/wiki/smart-rock-updates) | [Wiki](https://github.com/OPEnSLab-OSU/OPEnS-Lab-Home/wiki/Smart-Rock)
Project Leads: **Colin Hale-Brown**, **Martin Escoto**, and **Alicia Veach**

Interest in the project? Email us at: halebroc@oregonstate.edu

- [x] Latest hardware version: 3
- [x] Latest software version: 2.5

The Smart Rock is a submersible sensor suite that monitors water depth, temperature, turbidity, and salinity (EC) of a small stream over time and designed to be built by anyone with or without extensive experience in electronics.

<!--

## Smart Rock Validation
 
<details>
<summary>Show Hardware Requirements</summary>

**Hardware Requirements**

* Acrylic cap forms watertight seal with the union fitting.
* No lose components inside the Smart Rock.
* Sensors are robust enough to be deployed for one or more deployments.
* Electronics are accessible and easy to maintain.
* Materials used will not pollute or damage the environment. 
* Can withstand freezing temperatures.
* Have reliable mounting points for fixing the Smart Rock during testing and deployment.
</details>

<details>
<summary>Show Electronics Requirements</summary>

**Electronics Requirements**

* EC Sensor is reporting consistent data.
* Turbidity sensor is reporting consistent data.
* MS5803 can sense pressure reliably
* MS5803 can sense temperature reliably  
* Battery life could last 4 months or more with default/ recommended settings.
* Sensor Data can be reliably be stored.
* All wires have unique connectors to make miss-wiring impossible.
</details>

<details>
<summary>Show Software Requirements</summary>

**Software Requirements**

* Smart Rock can sleep for prolonged battery life.
* Set RTC through serial. 
* Records time along with data.
* With the use of the onboard switch, the Smart Rock has two modes.
* Settings for modes must be configurable.
* Code is robust enough to run without error for 3-6 months.
</details>

## Bill of Materials

<details>
<summary>Show Bill of Materials</summary>

**Bill of Materials**

Kits | Type
---- | ----
A | Fully Assembled
B | To be Assembled
C | In house parts only


Item Description | Notes | Quantity per 1 SR | Part Number | Dist. Website | In kits 
------ | ------ | ------ | ------- | ------ | ------ 
PVC Pipe (Quantity in inches) | 2.5" pipe | 4.125 | 5AFJ8 | [Grainger](https://www.grainger.com/product/GRAINGER-APPROVED-Pipe-5AFJ8?) | A,B
PVC Union Fitting | Only Part of the fitting is used, cemented onto pipe | 1 | 457-025 | [SupplyHouse](https://www.supplyhouse.com/Spears-457-025-2-1-2-PVC-Sch-40-Socket-Union-w-Buna-N-O-ring) | A,B
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
</details>

## Assembly Guide

<details>
<summary>Show Materials</summary>

#### Materials

* Smart Rock Enclosure
* Turbidity Sensor kit
* Acrylic Faceplate
* Hypnos
* Feather
* EC Breakout Board
* Sled_Base
* Turbidity_Mount
* Electronics_Mount
* Turbidity_Cover
* Battery_Mount
* Rails (Inside and Out)
* M3 screw 8mm (2x)
* M3 screw 10mm (4x)
* M3 nut (10x)
* SD Card (16gb)
* CR1220 Button Cell
* 3" velcro strap


Aditional Materials
* Super Glue
* Marine Epoxy

</details>

<details>
<summary> End Cap Procedure </summary>

***Assemble End Cap***

1. Prep the Turbidity sensor and. For the Turbidity sensor, trim the two mounting holes off. For the Make sure all wires are are un clipped or outof te way..

2. Cut the tip of the marine epoxy with scissors - *be careful as it will ooze after opening*

3. Mix 15 ml of marine epoxy in a 30 ml cup using a popsicle stick.

4. Apply marine epoxy around the edge of the turbidity sensor.

5. On the faceplate, apply super glue around the turbidity sensor's hole on the inside face where the turbidity sensor will contact the acrylic faceplate.

6. Insert the turbidity sensor into the hole. The black plastic peg should point directly at the slot on the faceplate.

7. Press the turbidity sensor into the hole and hold until the super glue sets. If necessary, use the popsicle stick to move or add epoxy to turbidity sensor to create a good seal on the inside.

8. On the outside of the acrylic plate, apply epoxy around the outside of the sensor. 

9. On the top of the two pillars of the sensor apply super glue, cover the sensor with the 3D printed cover to the sensor and hold it for a minute giving the sensor a chance to stick in place.

10. If needed, use the popsicle stick to move or apply more epoxy to the sensor cover.

11. Set somewhere safe to dry for at least 4 hours, overnight if possible.

***Assemble the Sled***

1. Find the top and bottom of the sled and align the rail with its indicator on the bottom of the sled. Apply super glue to the top of the rail and using the indicator and front ed

1. To start assembling the sled, populate the Turbidity and EC Breakout Mounts with 10mm M3 screws and capture them with nuts.

2. Add the PCBs onto their stand-offs and capture them with another nut.

3. Matching the tabs and corresponding slots, attach the EC Breakout Mount and the battery Mount together fitting the velcro into the provided channel.

3. Slip the turbidity mount onto the battery mount and onto the remaining tabs.

4. Drop the assembly onto the sled and mount with the two 8mm M3 screws captured with nuts on the underside of the Smart Rock.
 
</details>

## Test Procedures
<details>
<summary>Test for Leaks</summary>

1. Start by removing the sled if it is installed in the smart rock and preparing a tub or bucket of water.

2. Add the acrylic faceplate and seal union fitting with an empty smart rock. 

3. Completely submerge the Smart Rock in water and hold it there for 30 seconds.

4. Check for leaks and water pooling inside the Smart Rock. If there are none resubmerge for 3 to 5 minutes.

5. Check for water inside the Smart Rock, if none can be seen then unscrew the union fitting and check that the o-ring is compressed and making a complete seal, the faceplate should stick to the capsule if the seal is sticking.

6. If there is no water inside the smart rock it is not leaking.

</details>

<details>
<summary>Test EC Breakout Board</summary>

</details>

<details>
<summary>Test and Calibrate the Turbidity Sensor</summary>

</details>

<details>
<summary>Test and Calibrate the EC and MS5803 Sensors</summary>

</details>

<details>
<summary> </summary>

</details>

## Operation Guide

-->
