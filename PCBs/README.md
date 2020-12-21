# Custom PCBs

Each Smart Rock contains three custom PCBs, the EC breakout board and OsmoPod can be found here. Information about the Hypnos Board can be found [Here](https://github.com/OPEnSLab-OSU/OPEnS-Lab-Home/wiki/Hypnos).

Board | Description
----- | -----
EC Breakout	| Module containing EC circuitry and breakout plugs for the other sensors.
OsmoPod | Module containing EC probes and MS5803 pressure/ temperature sensor.
Hypnos | Module for time, sleep, and data storage functionalities of the Smart Rock.

<!-- 

### OsmoPod Assembly

<details>
<summary>Show OsmoPod Assembly Guide </summary>

**OsmoPod Assembly Guide**

1. Start by applying solder paste to the OsmoPod board for the MS5803 sensor. Clean up any etra solder or move it to a trace so a short is not made.

2. Align the MS5803 with the indicator pin on the bottom of the sensor and bake it onto the board.

3. Test using a multimeter for shorts under the sensor, if it is all clear than you can move on if not use some solder rework to get the sensor on without shorts.

3. Using a soldering iron add the two surface mount resistors and one surface mount capacitor.

4. take the 3, extra long male headers and remove the center header. Install the two remaining headers into the board and use the acrylic pieces as a guide to push out the EC probes to the edge of the acrylic faceplate. 

5. Solder the headers in place then tin the inside posts for the JST wires. 

6. slip a piece of heat shrink over the 2-pin JST for the EC and the 4-pin JST for the I2C. Then solder the EC wires to their corresponding probes, the ground is indicated by its shared connection with the ground for the I2C.

7. Insert the wires into their corresponding holes (The header and board switch SDA and SLI, ground attaches to the end of the capacitor) Solder the ground first then so the data and voltage.

8. Slide the heat shrink down over the exposed headers and organize the wires then seal them from strain and interference.

9. With the epoxy mixed apply it carefully to the top of the sensor until the top of the PCB is sealed. Apply two dabs of super glue near the MS5083 then apply the shield. Use two tiny clamps or binder clips to hold the acrylic to the sensor while drying. 

10. When installing in the acrylic face plate apply super glue to the edges of the sensor cover then stick it to the face plate before sealing with epoxy.

</details>

### EC Breakout Assembly

<details>
<summary>Show EC Breakout Assembly Guide</summary>

**EC Breakout Assembly Guide**



</details>

### Hypnos Prep

The only preperation needed for the hypnos board is to solder on the female and male headers for the top and bottom of the board. 

-->
