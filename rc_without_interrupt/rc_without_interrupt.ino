

int ch1=3;
int ch2=4;
int ch3=5;
int ch4=6;
int ch5=8;
int ch6=9;
int ch7=10;
int ch8=11;

static int ch1_val, ch2_val, ch3_val, ch4_val, ch5_val, ch6_val, ch7_val, ch8_val;

int led = 7;
void setup() {
 
pinMode(ch1, INPUT); // Set our input and output pins as such
pinMode(ch2, INPUT);
pinMode(ch3, INPUT);
pinMode(ch4, INPUT); // Set our input and output pins as such
pinMode(ch5, INPUT);
pinMode(ch6, INPUT);
pinMode(ch7, INPUT); // Set our input and output pins as such
pinMode(ch8, INPUT);

pinMode(led, OUTPUT);
Serial.begin(9600); //initialise serial
 
}
 
void loop() {
ch1_val = pulseIn(ch1, HIGH, 25000); // Read the HIGH pulse width of
ch2_val = pulseIn(ch2, HIGH, 25000); // each channel with timeout specified
ch3_val = pulseIn(ch3, HIGH, 25000);
ch4_val = pulseIn(ch4, HIGH, 25000); // Read the HIGH pulse width of
ch5_val = pulseIn(ch5, HIGH, 25000); // each channel with timeout specified
ch6_val = pulseIn(ch6, HIGH, 25000);
ch7_val = pulseIn(ch7, HIGH, 25000); // Read the HIGH pulse width of
ch8_val = pulseIn(ch8, HIGH, 25000); // each channel with timeout specified
 
Serial.println(ch1_val);
Serial.println(ch2_val);
Serial.println(ch3_val);
Serial.println(ch4_val);
Serial.println(ch5_val);
Serial.println(ch6_val);
Serial.println(ch7_val);
Serial.println(ch8_val);
Serial.print('\n');

digitalWrite(led, HIGH); // turn the LED on (HIGH is the voltage level)
delay(400); // wait for a second
digitalWrite(led, LOW); // turn the LED off by making the voltage LOW
delay(400);
}
