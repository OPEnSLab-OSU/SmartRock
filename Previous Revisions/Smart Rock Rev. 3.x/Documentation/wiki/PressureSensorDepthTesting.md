# Pressure Sensor Depth Testing

Performed and documented by Kaden Bennett and Chris Milford

**Experiment Description**

A Smart Rock was deployed overnight at the bottom of a 4 meter standpipe, using a nylon rope tied around the PVC casing for deployment and retrieval. Attached to the Smart Rock was a HOBO pressure and temperature logger (hereafter referred to as the &ldquo;silver HOBO logger&rdquo;). This logger was attached to the Smart Rock with stainless steel hose clamps and zip ties. The experimental setup can be seen in the Deployment Information section below.

Outside of the standpipe, there was deployed a second HOBO pressure and temperature logger (hereafter referred to as the atmospheric HOBO logger). This logger measured the atmospheric pressure in the vicinity of the standpipe, for use in pressure compensation. In order to calculate the depth of both the Smart Rock and the silver HOBO logger, the absolute pressure readings were both adjusted by subtracting the atmospheric pressure present outside the standpipe at that moment in time, as recorded by the atmospheric pressure logger.


**Deployment Information**

Time (PDT) | Event | Data Collected
-- | -- | --
8/25/22 5:09 PM | Smart Rock submerged at full testing depth | Stage height: 399 cm
8/26/22 10:37 AM | Smart Rock retrieved from standpipe | Stage height: 398 cm

###### Table 1: Deployment Timeline

There was a 5 cm offset between the Smart Rock and silver HOBO logger pressure sensors in our experimental setup, as can be seen below.

<img src="https://lh6.googleusercontent.com/rwChWde2Qvd1e696PlcA1B61d706veVi_TbcPStrp8xeiqYqRLxembslSadZrxm0LOAkEOiwbV_E3gTVAKXk2Bml1DCdoYjDqoSsDRv5g2wDrg4QcYlNlPSNJv6b9354WKuyyi9aBTZJyuHdbDaa2SGovvtTy8SKBkEwof2sRfE2Tl0-Bk_B3MyOHKX7" width="278" height="370" style="margin-left:0px;margin-top:0px;"/>

<img src="https://lh3.googleusercontent.com/OZgCCOdfekL7813O-BqMFHsBJv0ZtNBx1nSaIuGvDbH59Ez_NbkVxuzxTXJdH62RxJn_gO2w9sn9X1MYzpFl9we2GQaMiaJMRFPuqNm2WJh6yj_n7-koYuNK8XWDDo0d5oeQJIa5HGJkR7Biyoqiq1jtqYNPbXZ_m0oK7JSA7UWIwoRv7lYc7SkhsXxD" width="278" height="371" style="margin-left:0px;margin-top:0px;" />

</span></span></p><p dir="ltr" style="line-height:1.3800000000000001;text-align: center;margin-top:0pt;margin-bottom:0pt;">

###### Images 1-2: Experimental Setup of Smart Rock and Silver HOBO Logger

* The Smart Rock was sealed by the normal process, with a set screw and vacuum grease, which has been shown to consistently prevent leakages in previous deployments. However, upon retrieval, it was observed that water had infiltrated the internal Smart Rock compartment. This may be a result of the higher pressures endured during this experiment in comparison with our typical shallow water deployments and tests.


**Pressure Data:**

<img src="https://lh5.googleusercontent.com/lokBEyO8RJC1Cuwf8AITx_7FATQlX-F7mK62MM3SH4jxYUh4wy9GFU2MrIatKFNpdrTvciP80J0sX8UJ-W8Mn6u49UY8llJlJOt0bSgx6R-AzlVob9ojactTuFT1ka6oNOaNbEvTuxhyiOjr0D0GOZpzd0JZq9qnwn-s3xKREW2JZzKvAKOIsenaJY6F" width="577" height="359" style="margin-left:0px;margin-top:0px;" />

###### Figure 1: Smart Rock and HOBO Logger Absolute Pressure Data

<img src="https://lh5.googleusercontent.com/tt0j8oSrjgrhRhtUNPsh35uUzYYdQTvnLuvk9zBHgo4A0tvq9dzS2vo5BKfLMgI0qTNyMP6c5uaBEqiFJ846VEzkgMocDgG7T4AA9Va-JT23ufiiy1f-9YAsIC1b7cFDnyEoOWX97PWy-ollRMIdL44SLZ0hguC7C_FFYL6lLgY4Hhfv-TDKto5MA05D" width="583" height="363" style="margin-left:0px;margin-top:0px;" />

###### Figure 2: Smart Rock and Silver HOBO Logger Depths</span></p><br /><br /><p dir="ltr" style="line-height:1.3800000000000001;margin-top:0pt;margin-bottom:0pt;">

<img src="https://lh5.googleusercontent.com/6jsN62zdX2YNCbyq9iPaGDgmfxuvH5CCi7C18tJImp--PY5yJILDRtGixmuhdajkl9zE5haJ-lo4NhI9cCgFZZ3EANTiMA0-YgPF6Y3Z14sfSXlA0wwT1qAfdgmJJ5pSGvtDxUaBr2Cbkjlrxs-DkbbNKWbcLcx79JTW6ZzJGl0CIDj2N6MMWr5_Pzqy" width="625" height="415" style="margin-left:0px;margin-top:0px;" />

###### Figure 3: Atmospheric HOBO Logger Pressure Data

* The stair-step behaviour observed in the first few hours of the depth data (prior to 5:09 PM) is a result of the gradual filling of the standpipe and the plugging of various leaks which arose during the deployment.

* In the calculation of the depth of the Silver HOBO logger, it was taken into account that there was also a 0.62 mbar reading differential between that logger and the HOBO logger used to measure atmospheric pressure. This value was calculated as the average difference between the atmospheric pressure readings of the two loggers before the deployment began. The Smart Rock had a reading differential of less than 0.01 mbar with the atmospheric pressure logger, so that value was treated as insignificant.

* A constant conversion factor of 1.01972 was used to convert from mbar pressure units to cm of water head.

* The observed difference between the recorded depths of the Smart Rock and the silver HOBO logger is partially due to a 5 cm offset in the sensor height in our experimental setup.

* The calculated error of the Smart Rock pressure sensor at a submerged depth of ~4m is 3.45 mbar / 3.52 cm, after accounting for the sensor offset.

* A comparison of this data along with the result of our previous standpipe test against the data sheet specifications of the MS5803 pressure sensor used in the Smart Rock is shown below. As can be clearly seen, the performance of the Smart Rock&rsquo;s pressure sensor deteriorates quicker with increasing pressure than the manufacturer's specifications would suggest. This is likely a result of other temperature/pressure dependent components of the Smart Rock electronics.

<img src="https://lh3.googleusercontent.com/yy4s-3Uhs9GilkFcnBDGHtgYcbn_xokxuglEfxpi9u8FOSWVg7WHFo9K8LEwXhk3Y0NEMlNu4z-3Hck7mYihm1ShSZtsgPEfn0NW3itCI2juDmEShmJRIVuomHExvNhP_jRVofq4-ku8xCIKI3qcEhjKnkDtuyX6MUgIfHP6_KJeSwDs9o6KrDUoMIAJ" width="624" height="360" style="margin-left:-45px;margin-top:0px;" />

###### Figure 4: Pressure Error Comparison with Manufacturer Specifications

* Ultimately, this error is still less than 0.5%, considering the magnitude of the absolute pressure reading. When compared to the water depth being analyzed, the error is slightly below 1% of the water pressure reading. This offset of 3-4 cm at a water depth of around 400 cm is not hugely significant, but is worth keeping under consideration for deep water Smart Rock deployments.