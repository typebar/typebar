
//define all possible keys
#define KEY_CTRL	0x01
#define KEY_SHIFT	0x02
#define KEY_ALT		0x04
#define KEY_GUI		0x08
#define KEY_LEFT_CTRL	0x01
#define KEY_LEFT_SHIFT	0x02
#define KEY_LEFT_ALT	0x04
#define KEY_LEFT_GUI	0x08
#define KEY_RIGHT_CTRL	0x10
#define KEY_RIGHT_SHIFT	0x20
#define KEY_RIGHT_ALT	0x40
#define KEY_RIGHT_GUI	0x80

#define KEY_A		4
#define KEY_B		5
#define KEY_C		6
#define KEY_D		7
#define KEY_E		8
#define KEY_F		9
#define KEY_G		10
#define KEY_H		11
#define KEY_I		12
#define KEY_J		13
#define KEY_K		14
#define KEY_L		15
#define KEY_M		16
#define KEY_N		17
#define KEY_O		18
#define KEY_P		19
#define KEY_Q		20
#define KEY_R		21
#define KEY_S		22
#define KEY_T		23
#define KEY_U		24
#define KEY_V		25
#define KEY_W		26
#define KEY_X		27
#define KEY_Y		28
#define KEY_Z		29
#define KEY_1		30
#define KEY_2		31
#define KEY_3		32
#define KEY_4		33
#define KEY_5		34
#define KEY_6		35
#define KEY_7		36
#define KEY_8		37
#define KEY_9		38
#define KEY_0		39
#define KEY_ENTER	40	
#define KEY_ESC		41
#define KEY_BACKSPACE	42	
#define KEY_TAB		43
#define KEY_SPACE	44	
#define KEY_MINUS	45
#define KEY_EQUAL	46
#define KEY_LEFT_BRACE	47
#define KEY_RIGHT_BRACE	48
#define KEY_BACKSLASH	49
#define KEY_NUMBER	50
#define KEY_SEMICOLON	51
#define KEY_QUOTE	52
#define KEY_TILDE	53
#define KEY_COMMA	54
#define KEY_PERIOD	55
#define KEY_SLASH	56
#define KEY_CAPS_LOCK	57
#define KEY_F1		58
#define KEY_F2		59
#define KEY_F3		60
#define KEY_F4		61
#define KEY_F5		62
#define KEY_F6		63
#define KEY_F7		64
#define KEY_F8		65
#define KEY_F9		66
#define KEY_F10		67
#define KEY_F11		68
#define KEY_F12		69
#define KEY_PRINTSCREEN	70		
#define KEY_SCROLL_LOCK	71		
#define KEY_PAUSE	72
#define KEY_INSERT	73	
#define KEY_HOME	74
#define KEY_PAGE_UP	75
#define KEY_DELETE	76
#define KEY_END		77
#define KEY_PAGE_DOWN	78	
#define KEY_RIGHT	79
#define KEY_LEFT	80
#define KEY_DOWN	81
#define KEY_UP		82
#define KEY_NUM_LOCK	83
#define KEYPAD_SLASH	84	
#define KEYPAD_ASTERIX	85	
#define KEYPAD_MINUS	86	
#define KEYPAD_PLUS	87	
#define KEYPAD_ENTER	88	
#define KEYPAD_1	89
#define KEYPAD_2	90
#define KEYPAD_3	91	
#define KEYPAD_4	92	
#define KEYPAD_5	93	
#define KEYPAD_6	94	
#define KEYPAD_7	95	
#define KEYPAD_8	96	
#define KEYPAD_9	97	
#define KEYPAD_0	98		
#define KEYPAD_PERIOD	99	


//KeyIn Trial
#include <Wire.h>
#include "MCP23017.h"//Defaults to ADDRESS 0x20


bool shiftOn = false;//keep track of shift press

//basic array of key inputs. 
//uint8_t may need this? 
int textInputChip1[] = {KEY_Q,KEY_A,KEY_2,KEY_Z,KEY_W,KEY_S,KEY_3,KEY_X,KEY_E,KEY_D,KEY_4,KEY_C,
KEY_R,KEY_F,KEY_5,KEY_V};
//http://www.asciitable.com/ I Have used hex code values instead of KEY-- 
// int textInputChip1[] = 51,41,32,5A,57,53,33,58,45,44,34,43,
// 52,46,35,56};
//
int textInputChip2[] = {KEY_T,KEY_G,KEY_6,KEY_B,KEY_Y,KEY_H,KEY_7,KEY_N,KEY_U,KEY_J,KEY_8,KEY_M,
KEY_I,KEY_K,KEY_9,KEY_COMMA};

//only 10 keys here
int textInputChip3[] = {KEY_O,KEY_L,KEY_MINUS,KEY_PERIOD,KEY_P,KEY_SEMICOLON,KEY_LEFT,KEY_RIGHT,
KEY_UP,KEY_DOWN};//3/4 = key_left, 1/2 = key_right, 1/8 = key_up, 6/8 = key_down.. may need to change these. Look at typewriter

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
  //updateKeys();//call the update method
  sendText();
}


// void loop()
// {
// //call the method to print text to file
// //sendText();

// }

//make sure only correct key is sent to USB Keyboard
void mapToText(int key, int modifier) {
  // // press one key with up to one modifier, then release
  // Keyboard.set_modifier(modifier);
  // Keyboard.set_key1(key);
  // Keyboard.set_key2(0);
  // Keyboard.set_key3(0);
  // Keyboard.set_key4(0);
  // Keyboard.set_key5(0);
  // Keyboard.set_key6(0);
  // Keyboard.send_now();
  // delay(1);
  // Keyboard.set_key1(0); 
  // Keyboard.send_now();
}

void sendText()
{

	for(int set_pin_address = 0; set_pin_address < 4; set_pin_address++) {
	    MCP.begin(set_pin_address);

	    //call chip 1 text mappings
	    if (set_pin_address == 0)
	    {
			//for(int keyCode1 = 0; keyCode1 < textInputChip1.length; keyCode1 ++)
			for(int keyCode1 = 0; keyCode1 < 16; keyCode1 ++)
			{//iterate over the key code array
			    //setup for chip 1 reaadings
				if(shiftOn == false)
				{
					//Serial.print(textInputChip1[keyCode1]);
					mapToText(MCP.digitalRead(textInputChip1[keyCode1]), 0);//set keys to first chip for lower case
				}else if (shiftOn == true){
					//Serial.print(textInputChip1[keyCode1]);
					mapToText(MCP.digitalRead(textInputChip1[keyCode1]), MODIFIERKEY_SHIFT);//set keys to first chip for upper case
				}
			}
		}
		//call chip 2 text mappings
		if (set_pin_address == 1)
	    {
			//for(int keyCode2 = 0, keyCode2 < textInputChip2.length; keyCode2 ++)
			for(int keyCode2 = 0; keyCode2 < 16; keyCode2 ++)
			{//iterate over the key code array
			    //setup for chip 2 readings
				if(shiftOn == false)
				{
					//Serial.print(textInputChip2[keyCode2]);
					mapToText(MCP.digitalRead(textInputChip2[keyCode2]), 0);//set keys to fchip2 for lower case
				}else if (shiftOn == true){
					//Serial.print(textInputChip2[keyCode2]);	
					mapToText(MCP.digitalRead([textInputChip2[keyCode2]), MODIFIERKEY_SHIFT);//set keys to chip2 for upper case
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
			for(int keyCode3 = 0; keyCode3 < 16; keyCode3 ++)
			{//iterate over the key code array
			    //setup for chip 3 readings
				if(shiftOn == false)
				{
					//Serial.print(textInputChip3[keyCode3]);
					mapToText(MCP.digitalRead(textInputChip3[keyCode3]), 0);//set keys to chip3 for lower case
				}else if (shiftOn == true){
					//Serial.print(textInputChip3[keyCode3]);
					mapToText(MCP.digitalRead([textInputChip3[keyCode3]), MODIFIERKEY_SHIFT);//set keys to chip3 for upper case
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



// void mapToText(int pinInput)
// {
//    pinInput = dataFromPins;//take in the updateKeys information.. 

//     for(int inputKeys = 0; inputKeys < 42; inputKeys++)//iterate through all 42 standard keys from typewriter
        
//         if(shiftOn == false)
//         {//allow the printing of all the lower case letters and numbers
// 		    Keyboard.set_modifier(0);//no modifier keys.. 
// 		    switch (pinInput) {//take data from pins
// 			    case 0;
// 			      Keyboard.set_key1(KEY_Q);
// 			      break;
// 			    case 1:
// 			      Keyboard.set_key1(KEY_A);
// 			      break;
// 			    case 2:
// 			      Keyboard.set_key1(KEY_2);
// 			      break;
// 			    case 3;
// 			      Keyboard.set_key1(KEY_Z);
// 			      break;
// 			    case 4:
// 			      Keyboard.set_key1(KEY_W);
// 			      break;
// 			    case 5:
// 			      Keyboard.set_key1(KEY_S);
// 			      break;
// 			    case 6:
// 			      Keyboard.set_key1(KEY_3);
// 			      break;
// 			    case 7:
// 			      Keyboard.set_key1(KEY_X);
// 			      break;
// 			    case 8;
// 			      Keyboard.set_key1(KEY_E);
// 			      break;
// 			    case 9:
// 			      Keyboard.set_key1(KEY_D);
// 			      break;
// 			    case 10:
// 			      Keyboard.set_key1(KEY_4);
// 			      break;
// 			    case 11:
// 			      Keyboard.set_key1(KEY_C);
// 			      break;
// 			    case 12:
// 			      Keyboard.set_key1(KEY_R);
// 			      break;
// 			    case 13:
// 			      Keyboard.set_key1(KEY_F);
// 			      break;
// 			    case 14;
// 			      Keyboard.set_key1(KEY_5);
// 			      break;
// 			    case 15:
// 			      Keyboard.set_key1(KEY_V);
// 			      break;
			   
// 		} else if(shiftOn == true)
// 		{//allow the printing of all the upper case letters and numbers
//  			Keyboard.set_modifier(MODIFIERKEY_SHIFT);
// 			switch (pinInput) {//take data from pins
// 			    case 0;
// 			      Keyboard.set_key1(KEY_Q);
// 			      break;
// 			    case 1:
// 			      Keyboard.set_key1(KEY_A);
// 			      break;
// 			    case 2:
// 			      Keyboard.set_key1(KEY_2);
// 			      break;
// 			    case 3;
// 			      Keyboard.set_key1(KEY_Z);
// 			      break;
// 			    case 4:
// 			      Keyboard.set_key1(KEY_W);
// 			      break;
// 			    case 5:
// 			      Keyboard.set_key1(KEY_S);
// 			      break;
// 			    case 6:
// 			      Keyboard.set_key1(KEY_3);
// 			      break;
// 			    case 7:
// 			      Keyboard.set_key1(KEY_X);
// 			      break;
// 			    case 8;
// 			      Keyboard.set_key1(KEY_E);
// 			      break;
// 			    case 9:
// 			      Keyboard.set_key1(KEY_D);
// 			      break;
// 			    case 10:
// 			      Keyboard.set_key1(KEY_4);
// 			      break;
// 			    case 11:
// 			      Keyboard.set_key1(KEY_C);
// 			      break;
// 			    case 12:
// 			      Keyboard.set_key1(KEY_R);
// 			      break;
// 			    case 13:
// 			      Keyboard.set_key1(KEY_F);
// 			      break;
// 			    case 14;
// 			      Keyboard.set_key1(KEY_5);
// 			      break;
// 			    case 15:
// 			      Keyboard.set_key1(KEY_V);
// 			      break;

// 		}
//     }     
// }