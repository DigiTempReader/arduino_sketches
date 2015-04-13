/*
  AnalogReadSerial
  Reads an analog input on pin 0, prints the result to the serial monitor.
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.
 
 This example code is in the public domain.
 */

// the setup routine runs once when you press reset:
int sensorvalue1=100;
int sensorvalue2=45;
int sensorvalue3=1045;
int sensorvalue4=10045;




void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  //int sensorValue = analogRead(A0);
  // print out the value you read:
  Serial.print("{\"Voltage\":");
  Serial.print(sensorvalue1);
  Serial.print(",");
  Serial.print("\"Current\":");
  Serial.print(sensorvalue2);
  Serial.println("}");
  
  delay(1000);        // delay in between reads for stability
}
