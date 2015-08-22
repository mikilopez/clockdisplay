//
//    FILE: clockdisplay.h
// VERSION: 0.1
// PURPOSE: Control of a clock display
// LICENSE: GPL v3 (http://www.gnu.org/licenses/gpl.html)
//
// WEBPAGE: mclopez.net
//


#ifndef clockdisplay_h
#define clockdisplay_h

#if defined(ARDUINO) && (ARDUINO >= 100)
  #include <Arduino.h>
 #else
  #include <WProgram.h>
#endif

//display models
#define GC_6052S  1
#define SL_2042_79TB	2

class clockdisplay
{
    public:
        clockdisplay(int base_pin, int cathode1_pin, int cathode2_pin, byte display_model);
        void set_d1(bool v);
        void set_d2(bool v);
        void set_d3(bool v);
        void set_d4(bool v);
        void set_byte1(byte b);
        void set_byte2(byte b);
        void set_dec();
        void set_hex();
        void switch_state();
    protected:
        byte bpin, c1, c2;
        byte b1, b2;
        bool v1, v2, v3, v4;
        bool base10;
        byte state;
        byte model;
        void setpins(byte i1, byte i2, byte i3, byte i4);
        
        //for each model, where to get data from pindata
        PROGMEM const byte modeldata =
        	{
        	{2, 0, 1, 0}, //GC_6052S
        	{4, 3, 5, 3}  //SL_2042_79TB
        	};
        			
        //data values for pins
        PROGMEM const byte pindata =
        	{
        	{0xB7, 0x06, 0xE5, 0x67, 0x56, 0x73, 0xF3, 0x07, 0xF7, 0x77, 0xD7, 0xF2, 0xB1, 0xE6, 0xF1, 0xD1, 0x00}, //0
        	{0x7B, 0x30, 0x67, 0x76, 0x3C, 0x5E, 0x5F, 0x70, 0x7F, 0x7E, 0x7D, 0x1F, 0x4B, 0x37, 0x4F, 0x4D, 0x00}, //1
        	{0x00, 0x09, 0x3E, 0x3D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //2
        	{0x7B, 0x60, 0x5E, 0x76, 0x65, 0x37, 0x3F, 0x70, 0x7F, 0x77, 0x7D, 0x2F, 0x1B, 0x6E, 0x1F, 0x1D, 0x00}, //TODO this is same as pindata[0]
        	{0x00, 0x12, 0x46, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //4
        	{0xBE, 0x06, 0x7C, 0x6E, 0xC6, 0xEA, 0xFA, 0x0E, 0xFE, 0xEE, 0xDE, 0xF2, 0xB8, 0x76, 0xF8, 0xD8, 0x00}  //TODO this is same as pindata[1]
        	};
};

#endif
