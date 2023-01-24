# OsmoPod

## OsmoPod V1.0 Sensor Package

<!-- More information about the OsmoPod can be found [Here](https://github.com/OPEnSLab-OSU/PNNLFluxV1/wiki/OsmoPod) -->

### Bill of Materials

Item Description | Notes | Quantity per 1 SR | Part Number | Dist. Website 
------ | ------ | ------ | ------- | ------
OsmoPod_Shield | Part laser cut from 1/16" extruded acrylic sheet. | 1 | #### | [McMasterCarr](https://www.mcmaster.com/8589K11/)
OsmoPod PCB |  | 1 | #### | 
10k Resistor | Soldered onto PCB | 2 | RR1220P-103-D | [Digi-Key](https://www.digikey.com/en/products/detail/susumu/RR1220P-103-D/432854)
100nF Capacitor | Soldered onto PCB | 1 | CL21F104ZBCNNNC | [Digi-key](https://www.digikey.com/en/products/detail/samsung-electro-mechanics/CL21F104ZBCNNNC/3889093)
MS5803 Sensor | Pressure and temperature sensor. | 1 | MS580302BA01-00 | [Digi-key](https://www.digikey.com/en/products/detail/te-connectivity-measurement-specialties/MS580302BA01-00/5277629)
Long Male Headers | EC probes for sensing. | 1 | 400 | [Adafruit](https://www.adafruit.com/product/400)
2-pin Male JST | EC probe wires. | 1 | B07449V33P | [Amazon](https://www.amazon.com/Shappy-Pieces-Connector-Silicone-Female/dp/B07449V33P/)
4-pin Male JST | I2C wires for MS5803. | 1 | 4330130986 | [Amazon](https://www.amazon.com/2-0MM-Female-Single-Connector-Wires/dp/B0732MMD7K)
3/8" Heat Shrink | about 1/2" long | 1 |  |

### OsmoPod Assembly Guide

Please read through the entire assembly guide before you begin.

1. Align the MS5803 with the indicator pin on the bottom of the sensor with the indicator trace on the PCB. Use a clamp (I use a small binder clip) to hold the sensor in place.

2. With the board in a vise and the sensor clamped in place, solder the sensor to the board. Use the exposed contacts on the side to ensure a solid connection.

3. Visually inspect the soldering points for a bad connection then test for shorts under the sensor using the continuity setting on a multi meter. The image below shows the circuit. If any of the pins are connected under the sensor or solder has bridged between traces add rosin and re-flow the solder to un-bridge those connections.

<p align="center">
    <img src="https://user-images.githubusercontent.com/22950096/107816880-36c70a00-6d2a-11eb-8f9e-42e476cd147a.png" alt="logo" height="300"></a>
<p>

4. Flip the board over and solder the two surface mount resistors (R1 & R2) and one surface mount capacitor (C1) to the corresponding pads.

![Solder R1, R2, C1](https://github.com/OPEnSLab-OSU/SmartRock/blob/master/Previous%20Revisions/media/OsmoPod_Components.gif)

5. Take 3 long male headers and using pliers pull out the center header. Using a measuring device pull the two remaining headers so 10mm of the header is exposed from one side.

<p align="center">
    <img src="https://user-images.githubusercontent.com/22950096/107816292-645f8380-6d29-11eb-8e9f-3e4d8c7ecb6d.jpg" alt="logo" height="300"></a>
<p>

6. Install the headers on to the board in the GND and EC holes from the bottom of the board. Solder one of the headers in place, then make sure the plastic casing is flush with the PCB, if it is then solder the other header. If not re-flow the first one the straighten the probes.

7. Prep the wires and the board by slip a piece of heat shrink over the 2-pin JST for the EC and the 4-pin JST for the I2C for the MS5803. Then tin the backside of the EC probes so they can accept a wire.

8. Solder The EC wires to their posts with the red wire connecting to EC and the black wire to GND. For the I2C wires start with the black GND wire. The ground of the I2C should be soldered to the right pad of the capacitor next to the VCC hole with the wire pointing towards the inside of the PCB. After the ground is soldered the rest of the wires can be put in their corresponding holes and soldered in place.

Wire | Position 
------ | ------ 
EC - BLK | GND Post
EC - RED | EC Post
I2C - BLK | C1 Right Pad
I2C - RED | VCC Hole
I2C - WHT | SDA Hole
I2C -YLW | SCL Hole

9. Slide the heat shrink down over the exposed headers and organize the wires before gently heating the heat shrink sealing exposed headers.

10. With the epoxy mixed, less than 10mL needed, apply it carefully to the top of the PCB until the entire PCB is covered. Apply the OsmoPod_Shield to the epoxied PCB and apply pressure until the super glue has set Add more epoxy if a holes or gaps can let water in. Be careful to avoid getting epoxy in the MS5803 Sensor or on the EC Probes above the acrylic.  

11. Set the Osmopod in a location to dry overnight, make sure it is upright while drying.

The OsmoPod is ready to be tested and then installed on an acrylic face plate.
