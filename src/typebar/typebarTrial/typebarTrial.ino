/// -*- mode: Arduino; tab-width: 2; indent-tabs-mode:nil; -*-     ///
//////////////////////////////////////////////////////////////////////
/// Author: Anton Strilchuk <anton@isoty.pe>                       ///
///         Pedro Kirk <ped4416@gmail.com>                         ///
/// URL: http://typebar.github.io                                  ///
/// Created: 25-03-2014                                            ///
/// Last-Updated: 26-03-2014                                       ///
///   By: Anton Strilchuk <anton@isoty.pe>                         ///
///                                                                ///
/// Filename: typebarTrial                                         ///
/// Version: 0.0.1                                                 ///
/// Description: Teensy Typewriter                                 ///
///                                                                ///
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

/* //define all possible keys */
/* #define KEY_CTRL	0x01 */
/* #define KEY_SHIFT	0x02 */
/* #define KEY_ALT		0x04 */
/* #define KEY_GUI		0x08 */
/* #define KEY_LEFT_CTRL	0x01 */
/* #define KEY_LEFT_SHIFT	0x02 */
/* #define KEY_LEFT_ALT	0x04 */
/* #define KEY_LEFT_GUI	0x08 */
/* #define KEY_RIGHT_CTRL	0x10 */
/* #define KEY_RIGHT_SHIFT	0x20 */
/* #define KEY_RIGHT_ALT	0x40 */
/* #define KEY_RIGHT_GUI	0x80 */

/* #define KEY_A		4 */
/* #define KEY_B		5 */
/* #define KEY_C		6 */
/* #define KEY_D		7 */
/* #define KEY_E		8 */
/* #define KEY_F		9 */
/* #define KEY_G		10 */
/* #define KEY_H		11 */
/* #define KEY_I		12 */
/* #define KEY_J		13 */
/* #define KEY_K		14 */
/* #define KEY_L		15 */
/* #define KEY_M		16 */
/* #define KEY_N		17 */
/* #define KEY_O		18 */
/* #define KEY_P		19 */
/* #define KEY_Q		20 */
/* #define KEY_R		21 */
/* #define KEY_S		22 */
/* #define KEY_T		23 */
/* #define KEY_U		24 */
/* #define KEY_V		25 */
/* #define KEY_W		26 */
/* #define KEY_X		27 */
/* #define KEY_Y		28 */
/* #define KEY_Z		29 */
/* #define KEY_1		30 */
/* #define KEY_2		31 */
/* #define KEY_3		32 */
/* #define KEY_4		33 */
/* #define KEY_5		34 */
/* #define KEY_6		35 */
/* #define KEY_7		36 */
/* #define KEY_8		37 */
/* #define KEY_9		38 */
/* #define KEY_0		39 */
/* #define KEY_ENTER	40	 */
/* #define KEY_ESC		41 */
/* #define KEY_BACKSPACE	42	 */
/* #define KEY_TAB		43 */
/* #define KEY_SPACE	44	 */
/* #define KEY_MINUS	45 */
/* #define KEY_EQUAL	46 */
/* #define KEY_LEFT_BRACE	47 */
/* #define KEY_RIGHT_BRACE	48 */
/* #define KEY_BACKSLASH	49 */
/* #define KEY_NUMBER	50 */
/* #define KEY_SEMICOLON	51 */
/* #define KEY_QUOTE	52 */
/* #define KEY_TILDE	53 */
/* #define KEY_COMMA	54 */
/* #define KEY_PERIOD	55 */
/* #define KEY_SLASH	56 */
/* #define KEY_CAPS_LOCK	57 */
/* #define KEY_F1		58 */
/* #define KEY_F2		59 */
/* #define KEY_F3		60 */
/* #define KEY_F4		61 */
/* #define KEY_F5		62 */
/* #define KEY_F6		63 */
/* #define KEY_F7		64 */
/* #define KEY_F8		65 */
/* #define KEY_F9		66 */
/* #define KEY_F10		67 */
/* #define KEY_F11		68 */
/* #define KEY_F12		69 */
/* #define KEY_PRINTSCREEN	70		 */
/* #define KEY_SCROLL_LOCK	71		 */
/* #define KEY_PAUSE	72 */
/* #define KEY_INSERT	73	 */
/* #define KEY_HOME	74 */
/* #define KEY_PAGE_UP	75 */
/* #define KEY_DELETE	76 */
/* #define KEY_END		77 */
/* #define KEY_PAGE_DOWN	78	 */
/* #define KEY_RIGHT	79 */
/* #define KEY_LEFT	80 */
/* #define KEY_DOWN	81 */
/* #define KEY_UP		82 */
/* #define KEY_NUM_LOCK	83 */
/* #define KEYPAD_SLASH	84	 */
/* #define KEYPAD_ASTERIX	85	 */
/* #define KEYPAD_MINUS	86	 */
/* #define KEYPAD_PLUS	87	 */
/* #define KEYPAD_ENTER	88	 */
/* #define KEYPAD_1	89 */
/* #define KEYPAD_2	90 */
/* #define KEYPAD_3	91	 */
/* #define KEYPAD_4	92	 */
/* #define KEYPAD_5	93	 */
/* #define KEYPAD_6	94	 */
/* #define KEYPAD_7	95	 */
/* #define KEYPAD_8	96	 */
/* #define KEYPAD_9	97	 */
/* #define KEYPAD_0	98		 */
/* #define KEYPAD_PERIOD	99 */	


//KeyIn Trial
#include <Wire.h>
#include "MCP23017.h"//Defaults to ADDRESS 0x20


bool shiftOn = false;//keep track of shift press

//basic array of key inputs. 
//uint8_t may need this?

/* char smallcase [26] = { 'a','b','c','d','e','f','g','h','i', */
/*                         'j','k','l','m','n','o','p','q','r', */
/*                         's','t','u','v','w','x','y','z' }; */

/* char lowercase[42] = { 'q', 'a', '2', 'z', 'w', 's', '3', 'x',  */
/* 		       'e', 'd', '4', 'c', 'r', 'f', '5', 'v',  */
/* 		       't', 'g', '6', 'b', 'y', 'h', '7', 'n',  */
/* 		       'u', 'j', '8', 'm', 'i', 'k', '9', '\,',  */
/* 		       'o', 'l', '\-', '\.', 'p', '\;',  */
/* 		       '\~', '\!', '\#', '\$'}; */

/* char uppercase [42] = {"Q", "A", "\"", "Z", "W", "S", "\/", "X", */
/* 		       "E", "D", "\@", "C", "R", "F", "£", "V", */
/* 		       "T", "G", "\_", "B", "Y", "H", "\&", "N", */
/* 		       "U", "J", "\'", "M", "I", "K", "\(", "\?", */
/* 		       "O", "L", "\)", "\`", "P", "\:", */
/* 		       "\^", "\*", "+" }; */

byte textInputChip1[] =
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

byte textInputChip2[] =
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
byte textInputChip3[] =
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
  digitalWrite(13, HIGH);
  delay(500);
  digitalWrite(13, LOW);
}

void loop() {
  // The LED will 'echo' the button
  //digitalWrite(13, MCP.digitalRead(0));
  //updateKeys();//call the update method
  printMCPINFO();
  //sendText();
}

//make sure only correct key is sent to USB Keyboard
void mapToText(byte key, int modifier) {
  // press one key with up to one modifier, then release
  Keyboard.set_modifier(modifier);
  Keyboard.set_key1(key);
  Keyboard.set_key2(0);
  Keyboard.set_key3(0);
  Keyboard.set_key4(0);
  Keyboard.set_key5(0);
  Keyboard.set_key6(0);
  Keyboard.send_now();
  delay(100);
  Keyboard.set_key1(0); 
  Keyboard.send_now();
}

void sendText()
{

  for(int set_pin_address = 0; set_pin_address < 4; set_pin_address++) {
    MCP.begin(set_pin_address);

    //call chip 1 text mappings
    if (set_pin_address == 0)
      {
        for(int keyCode = 0; keyCode < 16; keyCode ++)
          {//iterate over the key code array
            //setup for chip 1 readings
            //	    printMCPINFO();
            ledDebug();
            delay(100);
            Serial.println(textInputChip1[keyCode]);
            //mapToText(textInputChip1[keyCode], 0);
            if(MCP.digitalRead(keyCode) == 0) {
              //Serial.println(smallcase[keyCode]); //debug
              //Keyboard.println(smallcase[keyCode1]); //to editor
              
              ledDebug();
            }
            else if (MCP.digitalRead(keyCode) == 0 && shiftOn) {
              //Serial.println(smallcase[keyCode]); //debug
              //Keyboard.println(smallcase[keyCode1]); //to editor
              ledDebug();
            }
            //mapToText(MCP.digitalRead(textInputChip[keyCode]), 0);
            //set keys to first chip for lower case

          }
      }
    //call chip 2 text mappings
    if (set_pin_address == 1)
      {
        //for(int keyCode2 = 0, keyCode2 < textInputChip2.length; keyCode2 ++)
        for(int keyCode = 0; keyCode < 16; keyCode ++)
          {//iterate over the key code array
            //setup for chip 2 readings
            //Serial.println(smallcase[keyCode]);
            if(MCP.digitalRead(keyCode) == 0) {
              // Serial.println(smallcase[keyCode]); //debug
              //Keyboard.println(smallcase[keyCode1]); //to editor
              ledDebug();
            }
            else if (MCP.digitalRead(keyCode) == 0 && shiftOn) {
              // Serial.println(smallcase[keyCode]); //debug
              //Keyboard.println(smallcase[keyCode1]); //to editor
              ledDebug();
            }
          }
      }
    //call chip 3 text mappings 
    /*--------------------------
      Need to add in Space Bar and other keys here.. ? 
    */
    
    if (set_pin_address == 2)
      {
        //for(int keyCode3 = 0; keyCode3 < textInputChip3.length; keyCode3 ++)
        for(int keyCode = 0; keyCode < 16; keyCode ++)
          {//iterate over the key code array
            if(MCP.digitalRead(keyCode) == 0) {
              //Serial.println(smallcase[keyCode]); //debug
              //Keyboard.println(smallcase[keyCode1]); //to editor
              ledDebug();
            }
            else if (MCP.digitalRead(keyCode) == 0 && shiftOn) {
              //Serial.println(smallcase[keyCode]); //debug
              //Keyboard.println(smallcase[keyCode1]); //to editor
              ledDebug();
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

void ledDebug() {
  digitalWrite(13, HIGH);
  delay(50);
  digitalWrite(13, LOW);
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