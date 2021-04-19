/*
  Basically a Blink Test for the Smart Rock to Ensure the Lights are Working.
*/

// Define LED Pins
int GLED = 14; // Green LED
int OLED = 15; // Orange LED
int RLED = 16; // Red LED

void setup() {
  // initialize the leds as outputs.
  pinMode(GLED, OUTPUT);
  pinMode(OLED, OUTPUT);
  pinMode(RLED, OUTPUT);

}

void loop() {
  digitalWrite(GLED, HIGH);   // turn the Green LED on
  delay(1000);                       // wait for a second
  digitalWrite(GLED, LOW);    // turn the Green LED off
  delay(1000);                       // wait for a second
  
  digitalWrite(OLED, HIGH);   // turn the Orange LED on
  delay(1000);                       // wait for a second
  digitalWrite(OLED, LOW);    // turn the Orange LED off
  delay(1000);                       // wait for a second
  
  digitalWrite(RLED, HIGH);   // turn the Red LED on
  delay(1000);                       // wait for a second
  digitalWrite(RLED, LOW);    // turn the Red LED off
  delay(1000);                       // wait for a second
}
