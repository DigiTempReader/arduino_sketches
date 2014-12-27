int val = 0; // A Variable to Store the Light Value from the LDR

void setup()
{
  Serial.begin(9600);// Start a Serial Connection
}

void loop()
{
  val = analogRead(3);// Reads a 10-bit value corresponding to the voltage applied on analog input pin 3.
  Serial.print("Light Intensity is : ");// Prints the given string / value to the serial monitor
  Serial.println(val);// prints the value of the variable val to the serial monitor and moves the cursor to the next line (the ln part of println does this)
  delay(1000);
}
