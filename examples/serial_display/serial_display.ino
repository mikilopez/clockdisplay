#include <clockdisplay.h>
#include <TimerOne.h>

clockdisplay cd(4, 2, 3, SL_2042_79TB);
byte h, m;

void setup()
{
  cd.set_d1(true); //visualiza 4 digitos
  cd.set_d2(true);
  cd.set_d3(true);
  cd.set_d4(true);
  Timer1.initialize(1000);
  Timer1.attachInterrupt(isr);
  Serial.begin(57600);
  //cd.set_hex(); //uncoment for hexadecimal counter 00..FF
}

void isr()
{
  cd.switch_state();
}

void loop()
{
  char r;
  if (Serial.available() > 0)
  {
    r = Serial.read();
    if (r=='h')
      {
        h = Serial.parseInt();
        cd.set_byte1(h);
      }
    if (r=='m')
      {
        m = Serial.parseInt();
        cd.set_byte2(m);
      }
  }
}
