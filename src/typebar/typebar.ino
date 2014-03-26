/// -*- mode: Arduino; tab-width: 2; indent-tabs-mode:nil; -*-     ///
//////////////////////////////////////////////////////////////////////
/// Author: Anton Strilchuk <anton@isoty.pe>                       ///
///         Pedro Kirk	    <ped4416@gmail.com>                    ///
/// URL: http://typebar.github.io                                  ///
/// Created: 23-03-2014                                            ///
/// Last-Updated: 26-03-2014                                       ///
///   By: Anton Strilchuk <anton@isoty.pe>                         ///
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
 * |       18 | 5v                           | RESET                  |
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
 * NC     - | 14 || 15 | <- A0
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

/*  */
byte key_matrix_QA2[] =
  {KEY_Q, //0
   KEY_A, //1
   KEY_2, //2
   KEY_Z, //3
   KEY_W, //4
   KEY_S, //5
   KEY_3, //6
   KEY_X, //7
   KEY_E, //8
   KEY_D, //9
   KEY_4, //10
   KEY_C, //11
   KEY_R, //12
   KEY_F, //13
   KEY_5, //14
   KEY_V  //15
  };

byte key_matrix_TG6[] =
  {KEY_T,    //0
   KEY_G,    //1
   KEY_6,    //2
   KEY_B,    //3
   KEY_Y,    //4
   KEY_H,    //5
   KEY_7,    //6
   KEY_N,    //7
   KEY_U,    //8
   KEY_J,    //9
   KEY_8,    //10
   KEY_M,    //11
   KEY_I,    //12
   KEY_K,    //13
   KEY_9,    //14
   KEY_COMMA //15
  };
byte key_matrix_OLMINUS[] =
  {KEY_O,         //0
   KEY_L,         //1
   KEY_MINUS,     //2
   KEY_PERIOD,    //3
   KEY_P,         //4
   KEY_SEMICOLON, //5
   KEY_LEFT,      //6
   KEY_RIGHT,     //7
   KEY_UP,        //8
   KEY_DOWN       //9
  };

boolean shift_key_pressed = false;

void setup() {  
  /* Sets ADDRESS for chips */
  for(int set_pin_address = 0; set_pin_address < 4; set_pin_address++)
    {
      MCP.begin(set_pin_address); //Shift through address numbers
      MCP.pinMode(set_pin_address, INPUT); //Set: pin modes for chip pins
      MCP.pullUp(set_pin_address, 1); //Set: 100K internal pullup
    }
  
  Serial.begin(9600);// set up a Serial Libarary at 9600 bps

  pinMode(13, OUTPUT);// use the p13 LED as debugging
}

void loop() {
  // The LED will 'echo' the button
  // MCP.begin(0); //Shift through address numbers
  printMCPINFO();

  //  get_keypress_input();//call the update method
}

/*---------------.
| READ FUNC DEFS |
`---------------*/

void get_keypress_input()
{
  for(int set_pin_address = 0; set_pin_address < 4; set_pin_address++) {
    MCP.begin(set_pin_address);
    //call chip 1 text mappings
    if (set_pin_address == 0)
      {
        for(int set_keypressed = 0; set_keypressed < 16; set_keypressed ++)
          {//iterate over the key code array
            //setup for chip 1 readings
            //	    printMCPINFO();
            active_debug_indicator_led();
            delay(5000);
            Serial.println(key_matrix_QA2[set_keypressed]);
            mapToText(key_matrix_QA2[set_keypressed], 0);
            if(MCP.digitalRead(set_keypressed) == 0) {
              //Serial.println(smallcase[set_keypressed]); //debug
              //Keyboard.println(smallcase[set_keypressed1]); //to editor
              active_debug_indicator_led();
            }
            else if (MCP.digitalRead(set_keypressed) == 0 && shift_key_pressed) {
              //Serial.println(smallcase[set_keypressed]); //debug
              //Keyboard.println(smallcase[set_keypressed1]); //to editor
              active_debug_indicator_led();
            }
            //mapToText(MCP.digitalRead(textInputChip[set_keypressed]), 0);
            //set keys to first chip for lower case

          }
      }
    //call chip 2 text mappings
    if (set_pin_address == 1)
      {
        for(int set_keypressed = 0; set_keypressed < 16; set_keypressed ++)
          {//iterate over the key code array
            //setup for chip 2 readings
            //Serial.println(smallcase[set_keypressed]);
            if(MCP.digitalRead(set_keypressed) == 0) {
              // Serial.println(smallcase[set_keypressed]); //debug
              //Keyboard.println(smallcase[set_keypressed]); //to editor
              active_debug_indicator_led();
            }
            else if (MCP.digitalRead(set_keypressed) == 0 && shift_key_pressed) {
              // Serial.println(smallcase[set_keypressed]); //debug
              //Keyboard.println(smallcase[set_keypressed]); //to editor
              active_debug_indicator_led();
            }
          }
      }
    //call chip 3 text mappings 
    /*--------------------------
      Need to add in Space Bar and other keys here.. ? 
    */
    
    if (set_pin_address == 2)
      {
        for(int set_keypressed = 0; set_keypressed < 16; set_keypressed ++)
          {//iterate over the key code array
            if(MCP.digitalRead(set_keypressed) == 0) {
              //Serial.println(smallcase[set_keypressed]); //debug
              //Keyboard.println(smallcase[set_keypressed]); //to editor
              active_debug_indicator_led();
            }
            else if (MCP.digitalRead(set_keypressed) == 0 && shift_key_pressed) {
              //Serial.println(smallcase[set_keypressed]); //debug
              //Keyboard.println(smallcase[set_keypressed]); //to editor
              active_debug_indicator_led();
            }
          }
      }	
    //chip 4 is outputs for LEDs
    //call chip 4 LED mappings
    if (set_pin_address == 3)
      {
        for(int ledOut = 0; ledOut<16; ledOut++)
          {
            //code to print out 16 leds.. 
          }
      }
  } 
}

void mapToText(byte key, int modifier) {
  /*--------------------------------------------------.
  | Keys can be pressed with, or without the use      |
  | of a modifier key.                                |
  | NOTE: this can be somewhat fiddly on a typewriter |
  `--------------------------------------------------*/
  Keyboard.set_modifier(modifier);
  Keyboard.set_key1(key);
  
  /*-NKRO and Keypress Limit-----------------------------------------------.
  | The Keyboard lib allows for a maximum of 6 keys to be pressed          |
  | simultaneous - this is fine for applications like a Typewriter         |
  | but is unfortunately limiting for modern keyboards, as No Key          |
  | Roll Over (NKRO) is a common feature that allows you to press          |
  | unlimited keys together, creating key chords, or key                   |
  | combinations of any specific size.                                     |
  | E.g.                                                                   |
  | CMD+CTRL+ALT+SHIFT+A+G+B+C+...out of fingers (Achieveable with NKRO)   |
  | CMD+CTRL+ALT+SHIFT+A+G (Achieveable with Arduino USB_KEYBOARD Library) |
  `-----------------------------------------------------------------------*/
  
  /* FUNCTIONS
   * Keyboard.set_key(VALUE) 
   *   can take either a Key value defined in table 
   *   below, or, a 0 indicating the key is currently off.
   * Keyboard.set_modifier(MODIFIER_KEY)
   *   can be set
   */ 
  Keyboard.send_now();
  delay(100);
  Keyboard.set_key1(0); 
  Keyboard.send_now();
}

/*----------------.
| DEBUG FUNC DEFS |
`----------------*/
void printMCPINFO () {
  /*
    /---------------------------------------------------.
    | FUNCTION TO PRINT OUT DEBUG INFO FOR MCP I/O PINS |
    `---------------------------------------------------/
  */
  for(int set_pin_address = 0; set_pin_address < 4; set_pin_address++) {
    MCP.begin(set_pin_address);
    Serial.print("\n");
    Serial.print("MCP: ");
    Serial.print(set_pin_address);
    Serial.print("\n");
    for(int i = 0; i < 16; i++) {
      int val = MCP.digitalRead(i);
      Serial.print("Pin: ");
      Serial.print(i);
      Serial.print(" | ");
      Serial.print(val, DEC);
      Serial.print("\t\n");
    }
  }
}


void active_debug_indicator_led() {
  digitalWrite(13, HIGH);
  delay(50);
  digitalWrite(13, LOW);
}

/* _MCP.ino ends here */