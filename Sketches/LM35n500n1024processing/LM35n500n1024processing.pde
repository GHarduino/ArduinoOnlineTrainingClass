//import Serial communication library
import processing.serial.*;

//init variables
Serial commPort;
float tempC;
float tempF;
int yDist;
PFont font12;
PFont font24;
float[] tempHistory = new float[100];

void setup()
{
  //setup fonts for use throughout the application
  font12 = loadFont("Verdana-12.vlw"); 
  font24 = loadFont("Verdana-24.vlw"); 
  
  //set the size of the window
  size(410, 400);
  
  //init serial communication port
  commPort = new Serial(this, "COM7", 9600);
  
  //fill tempHistory with default temps
  for(int index = 0; index<100; index++)
    tempHistory[index] = 0;
}

void draw()
{
  //get the temp from the serial port
  while (commPort.available() > 0) 
  {
    tempC = commPort.read();
    //tempC = (tempC/1024.0)*500.0;
  
  
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
    yDist = int(160 - (160 * (tempC * 0.01)));
    stroke(0);
    triangle(75, yDist + 20, 85, yDist + 15, 85, yDist + 25);
  
    //write the temp in C and F
    fill(0,0,0);
    textFont(font24); 
    textAlign(LEFT);
    text(str(int(tempC)) + " C", 100, 37);
    tempF = ((tempC*9)/5) + 32;
    text(str(int(tempF)) + " F", 100, 65);
  }
}