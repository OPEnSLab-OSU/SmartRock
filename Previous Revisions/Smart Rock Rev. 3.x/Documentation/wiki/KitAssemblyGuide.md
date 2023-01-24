# Kit Assembly Guide

Welcome to the Kit Assembly Guide. Assembling the kit will take roughly one hour to complete from start to finish.

### Kit Contents

Hardware
- [ ] PVC Enclosure
- [ ] M3 Nut (10x)
- [ ] 8mm M3 Screw (2x)
- [ ] 10mm M3 Screw (4x)
- [ ] 3" Velcro Cable Tie

Laser Cut Parts
- [ ] Sled_Base
- [ ] Electronics_Mount
- [ ] Turbidity_Mount

3D Printed Parts
- [ ] Battery_Mount

Electronics
- [ ] Feather M0
- [ ] Hypnos
- [ ] EC Breakout Board
- [ ] 16GB Micro-SD Card
- [ ] Micro-SD Card to SD Card Adapter
- [ ] 3.3V 2200mAh Li-Po Battery
- [ ] Coin Cell Battery
- [ ] Li-Po Battery Charger
- [ ] Acrylic Faceplate

Additional Items
- [ ] Desiccant Packet (2x)

More information about parts and where to source them can be found in the [Bill of Materials](https://github.com/OPEnSLab-OSU/SmartRock/wiki/Bill-of-Materials).

### Electronics Information

Before you start assembling, open your lithium battery and get it on the charger. It will take a couple of hours to get it charged for the first time. Lithium-ion batteries pose a serious fire risk when charging or discharging. Please be mindful of charging location, any damage to a lithium ion battery can lead to fire. If a battery's casing starts to show signs of damage or if the battery gets puffy please **stop using the battery immediately** and recycle it responsibly. If you have more questions please refer to your batteries MDS and safety information.

Circuit boards should be conformal coated before being deployed underwater. The OPEnS Lab conformal coats all boards before shipping them for the longevity of the probes. Please **DO NOT Solder on a board that has been conformal coated** the fumes are extremely toxic. If boards are not conformal coated be mindful of touching the circuit boards without actively grounding your body. The static charge in your body may damage or ruin the components. If you need to solder please use the correct conformal coating removal gels before doing so and  

It is unlikely but possible when handling micro-SD Cards to damage or corrupt the data stored on the card. Try not to touch the pins (Gold pads) on the card, the static charge of your body can wreak havoc.

### Sled Assembly

**Materials**

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
* 3" Cable Tie

Additional Materials

* pliers can be useful here

**Sled Assembly Procedure**

1. Lay out the Electronics_Mount with the sloped corners in the top left. Take two 10mm screws putting them up through the Electronics Mount in opposite corners and capturing each with 1 nut to make posts. 

2. Set the EC Breakout board on the posts of the Electronics_Mount with the JST Connects on the Right. Then capture it with another nut on each post. 

3. Lay out the Turbidity_Mount with the sloped corners in the top left corner. Take two 10mm screws and put them up through the Turbidity_Mount in opposite corners. Capture each of them with 1 nut to make posts. 

4. Set the Turbidity Breakout Board on the standoffs with the Blue Box on top and switch on bottom and capture it with two more nuts.

5. Take the 3" Velcro Cable tie and stick it to its self making a loop. Put this around the battery mount lining it up with the slot. 

6. Take the Electronics_Mount with the EC Breakout Board mounted and mesh it with the battery mount in the two slots on the prints side. Make sure the Velcro tie is sitting in the slot not interfering with the two parts touching. Take the Turbidity_Mount with the Turbidity Breakout board attached and slot it over both the Battery Mount onto the Electronics_Mount's tabs.

7. With the Mounts and print slotted together drop it into the Sled_Base using the Tabs and slots making sure the Velcro tie doesn't interfere.

8. Take two 8mm bolts and drop them through the Battery_Mount into the Sled_Base. Capture them with a nut on the bottom of the Sled_Base.

9. Plug the 3-pin JST into the Turbidity breakout board in the beige connector closer to the EC Breakout Board. Tuck the cable in by Wrap it in one loop and plug it in the the 3-pin JST plug on the EC Breakout Board.

<!-- 
![Turbidity_SledAssembly](https://github.com/OPEnSLab-OSU/SmartRock/blob/master/Previous%20Revisions/media/Sled_RailAssembly.gif)
-->

<!--
### Enclosure Assembly

**Materials**

* PVC Enclosure *(Assuming it is fully assembled and cemented in place)*
* Rail_Outside

Additional Materials

* Super Glue

**Enclosure Assembly Procedure**

1. Remove the cap on the PVC enclosure to get easy access to the inside lip of the housing. 

2. Identify the lip that is the end of the pipe and the start of the union fitting and find a clean spot to attach the rail to.

3. Use the Rail_Outside to do a test fit, if it the location looks good apply super glue to the curved bottom of the Rail_Outside *(be careful not to apply it to the retaining clip)*

4. Align the front edge of the Rail_Outside, the open side, with the front edge of the pipe and apply pressure until the super glue has set. *(Try and make it as straight as possible to make sliding the electronics as easy as possible.)*

5. Once the super glue has set use the sled to check that it is straight enough to go all the way in. The front edge of the two rails should be flush.
-->

### Electronics Assembly

**Materials**

* Feather M0
* Hypnos Board
* Micro-SD Card
* Coin Cell Battery
* Sled Assembly

** Electronics Assembly Procedure**

1. Insert the coin cell battery into the Appropriate slot on the Hypnos Board. The positive side of the battery faces outward from the board.

2. Plug the SD card into a computer and confirm that a config file is loaded.

3. With the config file confirmed plug the SD card into the Hypnos Board. The gold pins on the card face the PCB of the Hypnos.

4. Stack the Feather onto the Female headers on the Hypnos Board. Make sure the two are aligned and every pin is in a header, there should be no extra pins. 

5. Stack the Feather and Hypnos on to the EC Breakout Board on the Sled. Ensure once again there are no extra headers. 

6. Double check the stack of PCBs to ensure they are completely plugged in and secure. 

### Sensor Assembly

**Materials**

* Acrylic Faceplate With sensors 
* Turbidity Wire

**Sensor Assembly Procedure**

1. Inspect both ends of the Turbidity Wire and uncoil it slightly. Take the end with the clip and plug it into the **Turbidity sensor**, the remaining end will plug into the white connector on the Turbidity Breakout Board. This cable is directional please double check it is in correctly.

2. Plug in the 2-pin and the 4-pin wires from the OsmoPod to the EC Breakout Board 

## Conclusion

The sled should slide into the enclosure relatively easily. Center the acrylic faceplate and ensure it is resting flush before screwing on the top of the union fitting.

If you are interested in how the in "house parts" are built you can visit the In-House Parts section of the wiki to find their assembly guides.
