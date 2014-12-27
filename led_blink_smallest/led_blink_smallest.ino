#include <util/delay.h>
int main ()
  {
  DDRB = bit (5);
  while (true)
    {
      PINB = bit (5);
      _delay_ms(100);
    }
  }
