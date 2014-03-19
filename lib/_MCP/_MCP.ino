#include <Wire.h>
#include "MCP23017.h"//chip1 Address 0x20//chip 1 for inputs 1-16
#include "MCP23017_2.h"//chip2 Address 0x21//chip to for inputs 17-32
#include "MCP23017_3.h"//chip3 Address 0x22//chip 3 for inputs 33-
#include "MCP23017_4.h"//chip3 Address 0x23//chip 4 for LED bulb sends


// Basic pin reading and pullup test for the MCP23017 I/O expander
// public domain!

// Connect pin #12 of the expander to Analog 5 (i2c clock)
// Connect pin #13 of the expander to Analog 4 (i2c data)
// Connect pins #15, 16 and 17 of the expander to ground (address selection)
// Connect pin #9 of the expander to 5V (power)
// Connect pin #10 of the expander to ground (common ground)

// Input #0 is on pin 21 so connect a button or switch from there to ground

MCP23017 mcp;//for chip 1
MCP23017_2 mcp2;//for chip 2
MCP23017_3 mcp3;//for chip 3
MCP23017_4 mcp4;//for chip 4

void setup() {  

  delay(6000); //  Give the keyboard driver time to boot

  mcp.begin();// use  address 0 on the chip
  mcp2.begin();// use  address 0 on the chip
  mcp3.begin();// use  address 0 on the chip
  mcp4.begin();// use  address 0 on the chip

  mcp.pinMode(0, INPUT);
  mcp.pullUp(0, HIGH);// turn on a 100K pullup internally saves needing the resister on the board
  
  mcp2.pinMode(0, INPUT);
  mcp2.pullUp(0, HIGH);// turn on a 100K pullup internally
  
  mcp3.pinMode(0, INPUT);
  mcp3.pullUp(0, HIGH);// turn on a 100K pullup internally

  mcp4.pinMode(0, INPUT);
  mcp4.pullUp(0, HIGH);// turn on a 100K pullup internally 

  Serial.begin(9600);// set up a Serial Libarary at 9600 bps

  pinMode(13, OUTPUT);// use the p13 LED as debugging
}

void loop() {
  // The LED will 'echo' the button
  //digitalWrite(13, mcp.digitalRead(0));
  updateKeys();//call the update method 
}

void updateKeys(){
  
  //debug the chips.. 
  //Serial.print("Chip 1 = ");
  //Serial.println(mcp2.digitalRead(0));
  //Serial.print("Chip 2 = ");
  // Serial.println(mcp2.digitalRead(0));
  //Serial.print("Chip 3 = ");
  //Serial.println(mcp3.digitalRead(0));
  //Serial.print("Chip 4 = ");
  // Serial.println(mcp4.digitalRead(0));

//calls for 16 pins from chip 1 Address 0x20
  //int a = mcp3.digitalRead(0);
  //int s = mcp3.digitalRead(1);

  int e = mcp3.digitalRead(14);
  int space = mcp3.digitalRead(15);

//calls for 16 pins from chip 2 Address 0x21
  int a = mcp4.digitalRead(0);
  int s = mcp4.digitalRead(1);
  //int e = mcp2.digitalRead(2);
  //int space = mcp2.digitalRead(3);

//calls for 16 pins from chip 3 Address 0x22

//need sends for 16 LEDs pins from chip 3 Address 0x22
  
  if(a == 0)//we pressed an a!
  {
    Serial.print("a");
    //Keyboard.print("a");
    //sendSCByte(SC_A);//print to text file. 
    delay(250);//allow a delay so it only prints once. 
  } 
  else if(s == 0)//we pressed an s
  {
    Serial.print("s");
    //sendSCByte(SC_R);//
    delay(250);//allow a delay so it only prints once. 
  } 
  else if(e == 0)//we pressed an e
  {
    Serial.print("e");
     delay(250);//alow a delay so it only prints once.  
  } 
  else if(space == 0)//we pressed spacebar
  {
    Serial.print(" ");//simply ouput a space to println. 
    delay(250);//allow a delay so it only prints once. 
  }
}
