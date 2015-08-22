//
//    FILE: clockdisplay.cpp
// VERSION: 0.1
// PURPOSE: Control of a clock display
// LICENSE: GPL v3 (http://www.gnu.org/licenses/gpl.html)
//
// WEBPAGE: mclopez.net
//


#include "clockdisplay.h"


/* =========================
   Constructor
   base_pin:      the Arduino pin connected to the 1st display pin
   cathode1_pin:  the Arduino pin managing the cathode1
   cathode2_pin:  the Arduino pin managing the cathode2
   display_model: the display model
   ========================= */
clockdisplay::clockdisplay(int base_pin, int cathode1_pin, int cathode2_pin, byte display_model)
{
    bpin = base_pin;
    c1 = cathode1_pin;
    c2 = cathode2_pin;
    pinMode(c1, OUTPUT);
    pinMode(c2, OUTPUT);
    for (int i=0; i<14; i++)
    {
        pinMode(bpin+i, OUTPUT);
    }
    state = 0;
    base10 = true;
    v1 = v2 = v3 = v4 = false;
    b1 = b2 = 0;
    model = display_model;
}


/* =========================
   set_dX
   Shows or hides the X digit
   ========================= */
void clockdisplay::set_d1(bool v)
{
    v1 = v;
}

void clockdisplay::set_d2(bool v)
{
    v2 = v;
}

void clockdisplay::set_d3(bool v)
{
    v3 = v;
}

void clockdisplay::set_d4(bool v)
{
    v4 = v;
}


/*
   set_byteX
   Sets the byte1 (digits 1 and 2) or the byte2 (digits 3 and 4)
*/
void clockdisplay::set_byte1(byte b)
{
    b1 = b;
}

void clockdisplay::set_byte2(byte b)
{
    b2 = b;
}


/*
   set_dec
   Show bytes in decimal format
*/
void clockdisplay::set_dec()
{
    base10 = true;
}


/*
   set_hex
   Show bytes in hexadecimal format
*/
void clockdisplay::set_hex()
{
    base10 = false;
}


/*
   swich_state
   This function must be call each 10ms aprox. (between 2ms and 20ms) in order to view the display correctly.
   Call this function only once if you want to turn off the display (after calling set_dX(false)).
*/
void clockdisplay::switch_state()
{
    byte i1, i2, i3, i4;
    i1 = i2 = i3 = i4 = 0x10; //Set all digits as non-visible
    state ^= 1; //switch commons cathodes states
    if (base10) //select decimal digits, if visible
    {
        if (v1)
        {
            i1 = (b1/10)%10;
        }
        if (v2)
        {
            i2 = b1%10;
        }
        if (v3)
        {
            i3 = (b2/10)%10;
        }
        if (v4)
        {
            i4 = b2%10;
        }
    }
    else //select hexadecimal digits, if visible
    {
        if (v1)
        {
            i1 = b1/16;
        }
        if (v2)
        {
            i2 = b1%16;
        }
        if (v3)
        {
            i3 = b2/16;
        }
        if (v4)
        {
            i4 = b2%16;
        }
    }
    setpins(i1, i2, i3, i4);
}


/*
   setpins
   Set the display pins to show tha data
*/
void clockdisplay::setpins(byte i1, byte i2, byte i3, byte i4)
{
    byte s1, s2; //values for display pins

    switch (model)
    {
        case GC_6052S:
            if (s) //set common cathode1 values
            {
                s1 = d2[i2] >> 4;
                s1 |= d1[i1] & 0x70;
                s2 = d2[i4] >> 4;
                s2 |= d3[i3] & 0x70;
            }
            else //set common cathode2 values
            {
                s1 = d2[i2] & 0x07;
                s1 |= d1[i1] << 3;
                s2 = d2[i4] & 0x07;
                s2 |= d3[i3] << 3;
            }
            break;
        case SL_2042_79TB:
            if (s) //set common cathode1 values
            {
                s1 = d2[i2] >> 4;
                s1 |= (d1[i1] & 0x70) >> 1;
                s2 = d2[i4] >> 4;
                s2 |= (d3[i3] & 0xF0) >> 1;
            }
            else //set common cathode2 values
            {
                s1 = d2[i2] & 0x0F;
                s1 |= d1[i1] << 3;
                s2 = d2[i4] & 0x0F;
                s2 |= d3[i3] << 3;
            }
            break;
    }

    //off cathodes to avoid bad view
    digitalWrite(c1,LOW);
    digitalWrite(c2,LOW);

    //set pins
    for (int i=0; i<7; i++)
    {
        digitalWrite(bpin+i, (s2 >> i) & 0x01);
        digitalWrite(bpin+i+7, (s1 >> i) & 0x01);
    }

    //select cathode
    if (state)
    {
        digitalWrite(c2,HIGH);
    }
    else
    {
        digitalWrite(c1,HIGH);
    }
}
