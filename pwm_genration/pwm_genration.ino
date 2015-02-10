int user_cycles;
int user_duty;

int temp_cycles = 1010;
int temp_duty = 490;

void set(int cycles, float duty) 
{
char oldSREG;
int dutyCycle = cycles * duty;
if (dutyCycle < 6) 
  {
  dutyCycle = 6; // Prevent duty cycle from being too short
  }

if (dutyCycle > 1015) 
  {
  dutyCycle = 1015; // Prevent duty cycle from being 100%
  }
/*
if (cycles < 50) 
  {
  cycles = 50; // Prevent frequency from being too high
  }
*/

oldSREG = SREG; // Save the registers
cli(); // Disable interrupts for 16 bit register access
ICR1 = cycles; // ICR1 is TOP in p & f correct pwm mode
OCR1A = dutyCycle; // OCR1A is BOTTOM
SREG = oldSREG; // Restore the registers
}


void setup()
{

pinMode(9, OUTPUT);
pinMode(10,OUTPUT);

TCCR1A = 0; // clear control register A
TCCR1B = _BV(WGM13); // set mode 8: phase and frequency correct pwm, stop the timer
TCCR1B &= ~(_BV(CS10) | _BV(CS11) | _BV(CS12)); // Clear all prescaler bits
TCCR1B |= _BV(CS10); // choose prescaler 1, no prescaling, and start the clock
DDRB |= _BV(PORTB1); // sets data direction register for pwm output pin
TCCR1A |= _BV(COM1A1); // activates the output pin
//pinMode(A0, INPUT);
//pinMode(A1, INPUT);
pinMode(13, OUTPUT);
Serial.begin(9600);

digitalWrite(10,HIGH);
}


void serialEvent() 
{
  while (Serial.available())
  {
    // get the new byte:
    char inChar = (char)Serial.read(); 
    // add it to the inputString:
    if (inChar == '+') 
    {
      temp_cycles += 10;
    } 
    else if (inChar == '-') 
    {
      temp_cycles -= 10;
    }
    else if (inChar == '*') 
    {
      temp_duty += 10;
    } 
    else if (inChar == '/') 
    {
      temp_duty -= 10;
    }
  }

}



void loop()
{

  Serial.print(temp_cycles);
  Serial.print("\t\t");
  Serial.println(temp_duty);
  
  if (temp_cycles != user_cycles || temp_duty != user_duty)
  {
  user_cycles = temp_cycles;
  user_duty = temp_duty;
  set(user_cycles, user_duty / 1024.0);
  }

}
