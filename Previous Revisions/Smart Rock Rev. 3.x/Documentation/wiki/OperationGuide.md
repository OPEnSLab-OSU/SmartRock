# Operation Guide

Welcome to the Operation Guide. To start using your Smart Rock please charge the 3.3V Li-Po battery using the included charger.

On the bottom of the Hypnos board there is a holder for the coin cell battery to attach. The positive pole of the battery points away from the board and makes contact with the protruding metal housing. Next comes the SD card which is installed with the contacts facing the board. When the SD card is installed it should go in easily and click in place.

With the feather M0 installed on the Hypnos, plug the feather into a computer using the included micro-USB cable. The computer should have a serial monitor installed, we use the one that comes with the Arduino IDE. Have the serial monitor ready so when it boots up you can set the time on the clock, if you don't get to it before it goes to sleep/ starts taking data it should take the time from the computer it is plugged into and use that. You can power off the Smart Rock and check the SD card to make sure the correct time is stored on the SD card. To ensure the time is set, power on the Smart Rock using the 3.3V Li-Po battery and let it collect a data point or two and check the SD card to make sure the time is being kept correctly. 

If everything looks good, you are good to deploy your unit after validating/ calibrating the sensors to your liking.


## Troubleshooting

Your Smart Rock comes preprogrammed and includes software that is stable for long term use.
However, it is possible for unexpected behavior(s) to occur.

Below is a list of behaviors that may occur or have occurred, with detailed steps to solve them.


## [My Smart Rock is not turning on when I plug in the battery]

This behavior often occurs because the battery is not charged. To verify that the battery is the issue follow the steps below.

### Fix 1

	+ Check that the battery is charged
		- Plug battery into charging port
		- After the battery is charged, plug battery into Smart Rock power port
		- The Smart Rock should turn on and begin it's normal operation
		- If Smart Rock does not turn on and begin normal operation, proceed to next step

### Fix 2

	+ Plug the Smart Rock into a computer using the provided micro USB cable
		- The LEDs on the Smart Rock should turn on and proceed to it's normal operation. 
		- If the Smart Rock turns on and resumes operation while plugged into the






## [Why are the LEDs on my Smart Rock staying solid red; No blinking]

This behavior sometimes occurs for a number of unknown reasons, it could happen from handling the Smart Rock and accidentally moving one of the wires too much, or it could be caused by a poorly soldered pin that is causing a short. It may also be caused by a corrupted upload of the Arduino sketch.

### Fix 1

	+ Simply, restart the Smart Rock by pressing the Reset button on top of the Smart Rock electronics assembly.
	+ If the Smart Rock does not resume normal operation, proceed to Fix 2.
 
### Fix 2
	
	+ Unplug the battery from the Smart Rock
	+ Wait 10 seconds
	+ Plug the battery into the Smart Rock again
	+ If Smart Rock does not resume normal operation, proceed to Fix 3
### Fix 3 

	+ Unplug the battery from the Smart Rock
	+ Remove Smart Rock electronics assembly
	+ Disassemble Smart Rock electronics assembly
		- Remove the top black Arduino Feather board
		- Remove the middle green Hypnos board
	+ Examine each individual board for errors in solder points.
	+ If there are any noticeable errors in the soldering, proceed to correct these errors with the appropriate tools.
	+ If solder errors existed and have been corrected, reassemble Smart Rock electronics assembly
    + If issue persists, proceed to Fix 4


### Fix 4

    + Plug Smart Rock electronic assembly into computer 




