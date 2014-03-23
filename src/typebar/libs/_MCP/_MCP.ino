/// -*- mode: Arduino; tab-width: 2; indent-tabs-mode:nil; -*-     ///
//////////////////////////////////////////////////////////////////////
/// Author: Anton Strilchuk <anton@isoty.pe>                       ///
///         Pedro Kirk	    <ped4416@gmail.com>                    ///
/// URL: http://typebar.github.io                                  ///
/// Created: 23-03-2014                                            ///
/// Last-Updated: 23-03-2014                                       ///
///   By: y_pe <anton@isoty.pe>                                    ///
///                                                                ///
/// Filename: _MCP                                                 ///
/// Version: 0.0.1                                                 ///
/// Description: Teensy Typewriter                                 ///
///                                                                ///
//////////////////////////////////////////////////////////////////////
/// This program is free software; you can redistribute it and/or  ///
/// modify it under the terms of the GNU General Public License as ///
/// published by the Free Software Foundation; either version 3,   ///
/// or (at your option) any later version.			   ///
///                                                                ///
/// This program is distributed in the hope that it will be useful ///
/// but WITHOUT ANY WARRANTY; without even the implied warranty of ///
/// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  ///
/// GNU General Public License for more details.                   ///
///                                                                ///
/// You should have received a copy of the GNU General Public      ///
/// License along with this program; see the file COPYING.         ///
/// If not, write to the Free Software Foundation, Inc.            ///
/// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.   ///
//////////////////////////////////////////////////////////////////////
#include <Wire.h>
#include "MCP23017.h"//Defaults to ADDRESS 0x20

// Connect pin #12 of the expander to Analog 5 (i2c clock)
// Connect pin #13 of the expander to Analog 4 (i2c data)
// Connect pins #15, 16 and 17 of the expander to ground (address selection)
// Connect pin #9 of the expander to 5V (power)
// Connect pin #10 of the expander to ground (common ground)

// Input #0 is on pin 21 so connect a button or switch from there to ground

MCP23017 MCP; //Define class MCP23017 as MCP

void setup() {  
  /* Sets ADDRESS for chips */
  for(int set_pin_address = 0; set_pin_address < 4; set_pin_address++)
    {
      MCP.begin(set_pin_address); //Shift through address numbers
      MCP.pinMode(set_pin_address, INPUT); //Set: pin modes for chip pins
      MCP.pullUp(set_pin_address, LOW); //Set: 100K internal pullup
    }
  
  Serial.begin(9600);// set up a Serial Libarary at 9600 bps

  pinMode(13, OUTPUT);// use the p13 LED as debugging
}

void loop() {
  // The LED will 'echo' the button
  //digitalWrite(13, MCP.digitalRead(0));
  updateKeys();//call the update method
}

void updateKeys(){
  /* Debug print function */
  //printMCPINFO();
  digitalWrite(13, HIGH);
  for(int set_pin_address = 0; set_pin_address < 4; set_pin_address++)
    {
      MCP.begin(set_pin_address);
      //      Serial.println(set_pin_address);
      if (set_pin_address == 0)
	{
	  //    Serial.println(i);
	  if(MCP.digitalRead(8) == 1)
	    {
	      Serial.print("e");
	    }
	}
      
      //calls for 16 pins from chip 2 Address 0x21
      if (set_pin_address == 3)
	{
	  if(MCP.digitalRead(0) == 0)
	    {
	      Serial.print("a");
	    }
	  else if(MCP.digitalRead(1) == 0)
	    {
	      Serial.print("s");//simply ouput a space to println.
	    }
	}
      delay(10);
    }  
  //int e = MCP2.digitalRead(2);
  //int space = MCP2.digitalRead(3);
  digitalWrite(13, LOW);
  delay(50);
}

void printMCPINFO () {
  /*
    /---------------------------------------------------.
    | FUNCTION TO PRINT OUT Debug INFO FOR MCP I/O PINS |
    `---------------------------------------------------/
  */
  for(int set_pin_address = 0; set_pin_address < 4; set_pin_address++) {
    MCP.begin(set_pin_address);
    Serial.print("\n");
    Serial.print("MCP: ");
    Serial.print(set_pin_address);
    Serial.print("\n");
    for(int i = 0; i < 16; i++) {
      Serial.print("Pin: ");
      Serial.print(i);
      Serial.print(" | ");
      Serial.print(MCP.digitalRead(i));
      Serial.print("\t\n");
    }
  }
}

/* _MCP.ino ends here */