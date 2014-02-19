/* A library to setup the shift registers required for the TypeBar project. 
    Holds the functions and variables required for the ShiftRegister.h file
    The shift registers are Logic 8bit Texas Instruments CD74HC595E from Farnell UK
    See speck sheet here http://www.farnell.com/datasheets/1777736.pdf
     
    This shift register consists of 8 output pins, which are either high (1) or low (0).
	 When you pull the SRCLK (Serial Clock) pin high (analogy to ringing the bell), every 
	 pin moves one to the right. The Last pin drops out, and the new pin’s state is defined 
	 by the SER (Serial) pin, and you can set that to either 1 (HIGH) or 0 (LOW).
*/

#ifndef ShiftRegister_h
#define ShiftRegister_h

#include "Arduino.h"

//declare the new class
class ShiftRegister
{
	public:
		//set up for the three pins for each shift register and the number of shiftregisters in total
		//storage_Register_Clock_Pin (You can hold this pin LOW while you get everything setup 
		//and nothing on the display pins will change.
        setUpShiftRegister registerPins(int serial_Pin, int register_Clock_Pin, int storage_Register_Clock_Pin, int number_Of_Registers);
        setUpShiftRegister segmentPins(int a, int b, int c, int d, int e, int f, int g, int h, boolean common);
        void clearRegisters(); //reset the shift register
        void setAll(boolean allPins);//a method to reset all the pins at once
        void setPin(int index, boolean pinValue);//method to set a pin
        void update();//a method to update the current state of the pins.
        void writeRegisters();//a method to set and display the registers


    private: //a list of variables to be used by the registers allowing for 25 full registers if needed
        //variables for each pin
          int _a, _b, _c, _d, _e, _f, _g, _h, _number;
        int _serial_Pin, _register_Clock_Pin, _storage_Register_Clock_Pin, _number_of_Registers;
        byte numeral[10];
        byte numeralb[10];
        byte numeralc[10];
        byte numerald[10];
        byte numerale[10];
        byte numeralf[10];
        int segmentpins[8];
        int segmentpinsa[8];
        int segmentpinsb[8];
        boolean _common;
        boolean _commona;
        boolean _commonb;
        byte _shiftRegisters[25];
        boolean _allPins;
};

#endif
