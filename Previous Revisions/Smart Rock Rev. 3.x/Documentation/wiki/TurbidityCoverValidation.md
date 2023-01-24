# Turbidity Cover Validation

To validate the turbidity cover as effective it will have to show that it is effective at...

* Protecting the Turbidity sensor and keep it from getting pushed into the Smart Rock.
* Blocking stray light from interfering with the turbidity sensor.
* Not affect its ability to take measurements. 

To verify the effectiveness of the cover at this it will undergo a mechanical review to show how its geometry will prevent the sensor from caving in. To verify that the sensor cover blocks light two experiments will be conducted. The first will show the effectiveness of of the cover to block light by showing readings with and without the cover in different positions. The second will test how the much the cover affects the turbidity reading by testing known solutions with the sensor covered and uncovered.

**Mechanical Review**

The Turbidity cover is meant to use the sides of the sensor as a guide to hold it in position as it covers the top and sides completely. It is not meant to touch the top of the turbidity sensor, leaving a small gap between the cover and the sensor. The base of the turbidity cover has a flange which sits against the acrylic face plate transferring any force pushing on the turbidity cover into the acrylic face plate. This prevents the sensor from getting pushed into the Smart Rock flooding the unit. Below are two animations made using the CAD of the Smart Rock, one showing the the system with a cover and the other without. This shows that without a cover if enough force is applied it can break the epoxy sealing the sensor to the face plate creating a leak or completely flooding the unit.   

###### _Figure 1. Turbidity Sensor with cover_
![TurbidityCover_Cross](https://user-images.githubusercontent.com/22950096/108557339-4a83ea80-72ad-11eb-8754-9f37d8a39b05.PNG)

###### _Figure 2. Turbidity Sensor without cover_
![Tubridity_Exposed](https://user-images.githubusercontent.com/22950096/108476435-e0d0f580-7246-11eb-874d-153b7a906bdd.gif)

**Turbidity Cover Validation**

For the turbidity cover to pass the validation it must block stray light from influencing the sensor without interfering with the sensors abilities to collect data. First the sensor will be tested to see what wavelengths of light it is actually reading so when I preform my tests I know that my light source will have a measurable impact on the sensor. Then I will run tests to ensure that the cover actually blocks stray light from interfering with the sensor. After it's confirmed to block light it will be tested to see how it affects the sensors ability to collect data. All the following data is the raw analog values that the sensor stores. Because of this when light interferes with the sensor an increase in analog output should occur. This is because the sensor is made of a LED and a diode, the value recorded is the amount of light that can pass across the gap between the emitter and receiver. This translates to cleaner water lets more light pass, resulting in a higher value. 

For the first test different light sources were shine into the sensor directly. This tells us what frequencies of light actually are being measured by the sensors receiver by how large of a jump they cause. As seen in figure 3 the light on the blue end of the spectrum going into the ultra-violet had the largest response while the infrared was barely picked up. 

###### _Figure 3. How effective different sources of light influence the sensors readings._
![Turbidity_Light_Influence](https://user-images.githubusercontent.com/22950096/110067298-4d102680-7d28-11eb-9776-537bdf072c92.png)

Moving forward the white LED is used for testing because it is the best balance of influencing the sensor and not too many high energy particles for safety during tests. This next test the Smart Rock took a measurement every second while the light was turned on and off every ten minutes. Half way through the test the turbidity cover was added and the intervals continued on and off every ten minutes. 

###### _Figure 4. Before and after having the cover on the sensor with stray light._
![Turbidity_Cover_Blocking](https://user-images.githubusercontent.com/22950096/110067294-4bdef980-7d28-11eb-8f09-c9f8021e5284.png)

This shows that the turbidity cover does effectively lower the stray light interfering with the sensor. The light interference on the sensor is reduced by %80 by adding the turbidity cover as seen in figure 4. The cover definitely blocks interfering light and to test if it will interfere with the sensors measurements I filled a tub with filtered water. I also measured 500mL of warm filtered water into a glass and mixed it with two Nescafe Taster's Choice instant coffee packets, each meant for 8oz. Stirring until the instant coffee was dissolved and then let to sit for 5 minutes before being stirred again to ensure all the crystals had fully dissolved. 100mL of instant coffee was added at a time and sat until it had completely dispersed into the tub evenly. Then another 100mL was added until there was no more. This was done for the Smart Rock with and without a turbidity cover cleaning everything thoroughly between tests.

###### _Figure 5. Turbidity reading with and without the cover._
![Turbidity_Cover_Interference](https://user-images.githubusercontent.com/22950096/110067296-4c779000-7d28-11eb-9367-8f0650f81f99.png)

The raw data was adjusted to align the start times of the two trials to make comparing easier. When the instant coffee is initially added both variations spike to roughly the same value however the sensor without a cover has a harder following the steady increase in turbidity. At the end of both trials the sensors are taken out of the coffee tub, washed to remove any coffee from the outside, then put into another tub of clean water to get another base line. While the sensor with a cover returns to roughly the same initial value the sensor without a cover struggles to recover to its initial value. I think this may have been due to some other factor as I would expect the sensor to increase more than it did even though it did become stable. 

<!--
![Turbidity_Side](https://user-images.githubusercontent.com/22950096/108502963-7c269280-7268-11eb-88b0-6957515014e3.png)
--!>

To conclude the turbidity cover succeeds at its goal both mechanically protecting the sensor and blocking stray light from interfering with its readings. The cover is validated to be implemented on the Smart Rock. The turbidity cover can also be applied to previous versions of the Smart Rock to improve their measurements and protect them from leaks and damage as well.
