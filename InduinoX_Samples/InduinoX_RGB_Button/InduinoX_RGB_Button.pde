/*
***********************************************************************************************************************
*******************************### RGB LED COLOR CONTROL USING BUTTONS ###*********************************************
*/

int RGB[3];  // Variable to store individual Color Value of Different Colors of the RGB LED
int arr_ind=0; // Variable for Navigating through the Above Array - An Aray Index Variable

void setup()
{
  pinMode(7,INPUT); // The Increment Button
  pinMode(8,INPUT); // The Color Select Button
  pinMode(9,INPUT); // The Decrement Button
  digitalWrite(7,HIGH); // Enabling the Internal Pull-Up Resistor for the Button
  digitalWrite(8,HIGH);// Enabling the Internal Pull-Up Resistor for the Button
  digitalWrite(9,HIGH);// Enabling the Internal Pull-Up Resistor for the Button
  pinMode(11,OUTPUT);//LED for Current Selected Color Indication for RED Color - Lights up When the User Selects RED Color
  pinMode(12,OUTPUT);//LED for Current Selected Color Indication for BLUE Color - Lights up When the User Selects BLUE Color
  pinMode(13,OUTPUT);//LED for Current Selected Color Indication for GREEN Color - Lights up When the User Selects GREEN Color
  RGB[0] = 0; // RGB[0] will store the value for the BLUE Color
  RGB[1] = 0; // RGB[1] will store the value for the RED Color
  RGB[2] = 0; // RGB[2] will store the value for the GREEN Color
  applyColor(); // Calling a Function that will handle the AnalogWrite functions for the RGB LED
}
  
void loop()
{
  if(digitalRead(7)==0) // Checking if the Increment button is Being Pressed, If True, the value of the currently selected color's value is incremented
  {
    if(RGB[arr_ind]<255) // Checks if the currently selected color value is lesser than 255 before incrementing. So when it reaches 255, the value is reset to 0.
      RGB[arr_ind]++;
    else
      RGB[arr_ind]=0;
   delay(100);
  }
  if(digitalRead(9)==0)// Checking if the Decrement button is Being Pressed, If True, the value of the currently selected color's value is decremented
  {
    if(RGB[arr_ind]>0)// Checks if the currently selected color value is greater than 0 before decrementing. So when it reaches 0, the value is reset to 255.
      RGB[arr_ind]--;
    else
      RGB[arr_ind]=255;
   delay(100);
  }
  if(digitalRead(8)==0)// Checking if the color button is Being Pressed, If True, the value of the array index is incremented to the next value
  {
    if(arr_ind<2)
      arr_ind++;
    else
      arr_ind=0;
    while(digitalRead(8)==0); // This while is used to debounce the button press or in other words, wait for the user to release the button
    delay(50);
  }
  if((digitalRead(7)==0)&&(digitalRead(9)==0))// Checking if both the increment & decrement buttons are being pressed at the same time. If so, all color values are reset to zero
  {
    RGB[0] = 0; // RGB[0] will store the value for the BLUE Color
    RGB[1] = 0; // RGB[1] will store the value for the RED Color
    RGB[2] = 0; // RGB[2] will store the value for the GREEN Color
    digitalWrite(11,HIGH);digitalWrite(12,HIGH);digitalWrite(13,HIGH);// This to indicate a reset in progress. All three LEDS GLOW for 200 milliseconds and go Off
    delay(200);
    digitalWrite(11,LOW);digitalWrite(12,LOW);digitalWrite(13,LOW);
  }
    
  switch(arr_ind) // The switch is used to indicate the current color selection through the corresponding LED based on the current value of the Array Index
  {
    case 0: digitalWrite(11,LOW);digitalWrite(12,HIGH);digitalWrite(13,LOW);break;
    case 1: digitalWrite(11,HIGH);digitalWrite(12,LOW);digitalWrite(13,LOW);break;
    case 2: digitalWrite(11,LOW);digitalWrite(12,LOW);digitalWrite(13,HIGH);break;
  }
  applyColor();// Calling a Function that will handle the AnalogWrite functions for the RGB LED
  
}

// The function applyColor() will apply the RGB array variable's current value to the Analog Pins 3,5 & 6 which control the RGB LED
void applyColor()
{
  analogWrite(3,RGB[0]);
  analogWrite(5,RGB[1]);
  analogWrite(6,RGB[2]);
}

