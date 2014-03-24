/// -*- mode: Arduino; tab-width: 2; indent-tabs-mode:nil; -*-     ///
//////////////////////////////////////////////////////////////////////
/// Author: Anton Strilchuk <anton@isoty.pe>                       ///
///         Pedro Kirk	    <ped4416@gmail.com>                    ///
/// URL: http://typebar.github.io                                  ///
/// Created: 23-03-2014                                            ///
/// Last-Updated: 23-03-2014                                       ///
///   By: y_pe <anton@isoty.pe>                                    ///
///                                                                ///
/// Filename: typebar                                              ///
/// Version: 0.0.1                                                 ///
/// Description: Teensy Typewriter                                 ///
///                                                                ///
//////////////////////////////////////////////////////////////////////
/// This program is free software; you can redistribute it and/or  ///
/// modify it under the terms of the GNU General Public License as ///
/// published by the Free Software Foundation; either version 3,   ///
/// or (at your option) any later version.			  			           ///
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

/* MCP23017 16-bit I/O Port Expander (I2C) Info
 *
 * | Expander | Board                        | Pin Name               |
 * |----------+------------------------------+------------------------|
 * |        1 | KEY_IN                       | GPB0                   |
 * |        2 | KEY_IN                       | GPB1                   |
 * |        3 | KEY_IN                       | GPB2                   |
 * |        4 | KEY_IN                       | GPB3                   |
 * |        5 | KEY_IN                       | GPB4                   |
 * |        6 | KEY_IN                       | GPB5                   |
 * |        7 | KEY_IN                       | GPB6                   |
 * |        8 | KEY_IN                       | GPB7                   |
 * |        9 | 5v                           | VDD                    |
 * |       10 | GND                          | VSS                    |
 * |       11 |                              | NC/CHIP SELECT         |
 * |       12 | 19                           | SCL/SERIAL CLOCK       |
 * |       13 | 18                           | SDA/SERIAL DATA I/O    |
 * |       14 |                              | NC/SERIAL DATA OUT     |
 * |       15 | See Address Selection Table  | Hardware Address Pin   |
 * |       16 | See Address Selection Table  | Hardware Address Pin   |
 * |       17 | See Address Selection Table  | Hardware Address Pin   |
 * |       18 | GND                          | RESET                  |
 * |       19 |                              | Interrupt Output PORTB |
 * |       20 |                              | Interrupt Output PORTA |
 * |       21 | KEY_IN                       | GPA0                   |
 * |       22 | KEY_IN                       | GPA1                   |
 * |       23 | KEY_IN                       | GPA2                   |
 * |       24 | KEY_IN                       | GPA3                   |
 * |       25 | KEY_IN                       | GPA4                   |
 * |       26 | KEY_IN                       | GPA5                   |
 * |       27 | KEY_IN                       | GPA6                   |
 * |       28 | KEY_IN                       | GPA7                   |
 * |----------+------------------------------+------------------------|
 *        
 * MCP23017 PinOut:
 * GPB0 <-> |  1 || 28 | <-> GPA7
 * GPB1 <-> |  2 || 27 | <-> GPA6
 * GPB2 <-> |  3 || 26 | <-> GPA5
 * GPB3 <-> |  4 || 25 | <-> GPA4
 * GPB4 <-> |  5 || 24 | <-> GPA3
 * GPB5 <-> |  6 || 23 | <-> GPA2
 * GPB6 <-> |  7 || 22 | <-> GPA1
 * GPB7 <-> |  8 || 21 | <-> GPA0
 * VDD   -> |  9 || 20 | -> INTA
 * VSS   -> | 10 || 19 | -> INTB
 * NC     - | 11 || 18 | -> RESET
 * SCL   -> | 12 || 17 | <- A2
 * SDA  <-> | 13 || 16 | <- A1
 * NC     - | 13 || 15 | <- A0
 *
 * I2C Expander Address Selection
 * | Expander | Address | A0, A01, A02  |
 * |----------+---------+---------------|
 * |        1 |    0x20 | GND, GND, GND |
 * |        2 |    0x21 | GND, GND, 5v  |
 * |        3 |    0x22 | GND, 5v, GND  |
 * |        4 |    0x23 | GND, 5v, 5v   |
 * |----------+---------+---------------|
 */
/* Teensy 3.0 PinOut:
 * GND  -> | [] || [] | <- Vin  (3.7V to 5.5V)
 * RX1  -> |  0 || [] | <- AGND
 * TX1  -> |  1 || [] | <- 3.3V (100 mA max)
 * CS   -> |  2 || 23 | <- A9
 * PWM  -> |  3 || 22 | <- A8
 * PWM  -> |  4 || 21 | <- A7
 * PWM  -> |  5 || 20 | <- A6
 * PWM  -> |  6 || 19 | <- A5
 * RX3  -> |  7 || 18 | <- A4
 * TX3  -> |  8 || 17 | <- A3
 * RX2  -> |  9 || 16 | <- A2
 * TX2  -> | 10 || 15 | <- A1
 * DOUT -> | 11 || 14 | <- A0
 * DIN  -> | 12 || 13 | <- LED
 */

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