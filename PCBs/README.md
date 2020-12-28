# Custom PCBs

Each Smart Rock contains three custom PCBs, the EC breakout board and OsmoPod can be found here. Information about the Hypnos Board can be found [Here](https://github.com/OPEnSLab-OSU/OPEnS-Lab-Home/wiki/Hypnos).

Board | Description
----- | -----
EC Breakout	| Module containing EC circuitry and breakout plugs for the other sensors.
OsmoPod | Module containing EC probes and MS5803 pressure/ temperature sensor.
Hypnos | Module for time, sleep, and data storage functionalities of the Smart Rock.

### OsmoPod Sensor Package

<details>
<summary>OsmoPod Bill of Materials</summary>

Item Description | Notes | Quantity per 1 SR | Part Number | Dist. Website 
------ | ------ | ------ | ------- | ------
OsmoPod_Shield | Laser cut from 1/16" extruded acrylic sheet. | 1 | #### | [McMasterCarr](https://www.mcmaster.com/8589K11/)
OsmoPod PCB |  | 1 | #### | 
10k Resistor | Soldered onto PCB | 2 | RR1220P-103-D | [Digi-Key](https://www.digikey.com/en/products/detail/susumu/RR1220P-103-D/432854)
100nF Capacitor | Soldered onto PCB | 1 | CL21F104ZBCNNNC | [Digi-key](https://www.digikey.com/en/products/detail/samsung-electro-mechanics/CL21F104ZBCNNNC/3889093)
MS5803 Sensor | Pressure and temperature sensor. | 1 | MS580302BA01-00 | [Digi-key](https://www.digikey.com/en/products/detail/te-connectivity-measurement-specialties/MS580302BA01-00/5277629)
Long Male Headers | EC probes for sensing. | 1 | 400 | [Adafruit](https://www.adafruit.com/product/400)
2-pin Male JST | EC probe wires. | 1 | B07449V33P | [Amazon](https://www.amazon.com/Shappy-Pieces-Connector-Silicone-Female/dp/B07449V33P/)
4-pin Male JST | I2C wires for MS5803. | 1 | 4330130986 | [Amazon](https://www.amazon.com/2-0MM-Female-Single-Connector-Wires/dp/B0732MMD7K)
1/4" Heat Shrink | about 1/2" long | 1 |  |

</details>

<details>
<summary>OsmoPod Assembly Guide</summary>

1. Start by applying solder paste to the OsmoPod board for the MS5803 sensor. Clean up any etra solder or move it to a trace so a short is not made when the board is baked.

2. Align the MS5803 with the indicator pin on the bottom of the sensor and bake it onto the board.

3. Test using a multimeter for shorts under the sensor, if it is all clear than you can move on to the next step. If not use a heat gun or soldering iron to rework the solder and remove any shorts or finish connection if they are missing.

3. Using a soldering iron add the two surface mount resistors and one surface mount capacitor to the correspoding pads.

4. Take 3, long male headers and remove the center header using pliers. Install the two remaining headers into the board through the bottom and use the acrylic pieces as a guide to push out the EC probes to the edge of the acrylic faceplate. 

5. Solder the headers in place, then tin the inside posts to connect the JST wires. 

6. Slip a piece of heat shrink over the 2-pin JST for the EC and the 4-pin JST for the I2C for the MS5803. Then solder the EC wires to their corresponding probes, the ground is indicated by its shared connection with the ground for the I2C.

7. Solder the ground for the I2C to the last right side of the capacitor with the wire pointing toward the top.

8. Insert the remaining wires into their corresponding holes (SLI, SDA, and VCC).

9. Slide the heat shrink down over the exposed headers and organize the wires before sealing them.

10. With the epoxy mixed, only about 10mL needed, apply it carefully to the top of the PCB until the entire PCB is covered. Apply super glue to the OsmoPod_Shield near the MS5083 sensor hole then apply the shield to the epoxied PCB and apply pressure until the super glue has set. 

11. Add more epoxy to close the gap between the PCB and the Acrylic shield.

12. When installing in the acrylic face plate apply super glue to the edges of the sensor cover then stick it to the face plate before sealing with epoxy.

</details>

<!--

### EC Breakout Board

<details>
<summary>EC Breakout Board Bill of Materials</summary>

</details>

<details>
<summary>EC Breakout Assembly Guide</summary>


</details>

### Hypnos Board

<details>
<summary>Hypnos Bill of Materials</summary>

Item Description | Notes | Quantity per 1 SR | Part Number | Dist. Website 
------ | ------ | ------ | ------- | ------
Hypnos Board | Data logging, system power, real time clock. | 1 | #### |  
Short Male Header | For Hypnos and Feather Boards | 2 | 3002 | [Adafruit](https://www.adafruit.com/product/3002)
Short Female Header | For Hypnos and EC Breakout Boards | 2 | 2940 | [Adafruit](https://www.adafruit.com/product/2940)

</details>

<details>
<summary>Hypnos Assembly Guide</summary>

*If your hypnos board already has short headers attached you are ready to go*

1. The female headers on the hypnos board are going to accept the feather while the male headers are for the control side. Start by identifying which pair goes to which.

2. Start by soldering on the inside female headermaking sure the header is straight and flush with the PCB.

3. Then flip over the board with one headers soldered and solder the male headers. 

3. Flip the board over and complete the last female header.

4. Check that all soldering points are making good, complete contact and no two pins are shorting.

</details>

-->