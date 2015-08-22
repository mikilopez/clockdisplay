//decimal counter 00..99

#include <clockdisplay.h>

clockdisplay cd(4, 2, 3, GC_6052S);
byte con1, con2;

void setup()
{
  con1 = con2 = 0;
  cd.set_d3(true);
  cd.set_d4(true);
  //cd.set_hex(); //uncoment for hexadecimal counter 00..FF
}

void loop()
{
  cd.set_byte2(con2);
  cd.switch_state();
  delay(4);
  con1++;
  if (con1 == 0)
    con2++;
}
