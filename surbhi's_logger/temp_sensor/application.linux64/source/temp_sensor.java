import processing.core.*; 
import processing.data.*; 
import processing.event.*; 
import processing.opengl.*; 

import processing.serial.*; 

import java.util.HashMap; 
import java.util.ArrayList; 
import java.io.File; 
import java.io.BufferedReader; 
import java.io.PrintWriter; 
import java.io.InputStream; 
import java.io.OutputStream; 
import java.io.IOException; 

public class temp_sensor extends PApplet {

//import Serial communication library


//init variables
Serial commPort;
float tempC;
float tempF;
int yDist;
PFont font12;
PFont font24;
float[] tempHistory = new float[100];

public void setup()
{
  //setup fonts for use throughout the application
  font12 = loadFont("Verdana-12.vlw"); 
  font24 = loadFont("Verdana-24.vlw"); 
  
  //set the size of the window
  size(210, 200);
  
  //init serial communication port
  commPort = new Serial(this, "COM10", 9600);
  
  //fill tempHistory with default temps
  for(int index = 0; index<100; index++)
    tempHistory[index] = 0;
}

public void draw()
{
  //get the temp from the serial port
  while (commPort.available() > 0) 
  {
    tempC = commPort.read();
  
    //refresh the background to clear old data
    background(123);

    //draw the temp rectangle
    colorMode(RGB, 160);  //use color mode sized for fading
    stroke (0);
    rect (49,19,22,162);
    //fade red and blue within the rectangle
    for (int colorIndex = 0; colorIndex <= 160; colorIndex++) 
    {
      stroke(160 - colorIndex, 0, colorIndex);
      line(50, colorIndex + 20, 70, colorIndex + 20);
    }
    
    //draw graph
    stroke(0);
    fill(255,255,255);
    rect(90,80,100,100);
    for (int index = 0; index<100; index++)
    {  
      if(index == 99)
        tempHistory[index] = tempC;
      else
        tempHistory[index] = tempHistory[index + 1];
      point(90 + index, 180 - tempHistory[index]); 
    }
  
    //write reference values
    fill(0,0,0);
    textFont(font12); 
    textAlign(RIGHT);
    text("212 F", 45, 25); 
    text("32 F", 45, 187);
  
    //draw triangle pointer
    yDist = PApplet.parseInt(160 - (160 * (tempC * 0.01f)));
    stroke(0);
    triangle(75, yDist + 20, 85, yDist + 15, 85, yDist + 25);
  
    //write the temp in C and F
    fill(0,0,0);
    textFont(font24); 
    textAlign(LEFT);
    text(str(PApplet.parseInt(tempC)) + " C", 115, 37);
    tempF = ((tempC*9)/5) + 32;
    text(str(PApplet.parseInt(tempF)) + " F", 115, 65);
  }
}
  static public void main(String[] passedArgs) {
    String[] appletArgs = new String[] { "--full-screen", "--bgcolor=#666666", "--stop-color=#cccccc", "temp_sensor" };
    if (passedArgs != null) {
      PApplet.main(concat(appletArgs, passedArgs));
    } else {
      PApplet.main(appletArgs);
    }
  }
}
