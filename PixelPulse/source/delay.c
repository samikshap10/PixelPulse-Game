#include <MKL25Z4.H>

void Delay(uint16_t cnt)
{
  int i,j;

    // 1 instruction takes 1/48000000 = 20nsec to execute
  // at 48Mhz system clock
    for (j=0; j<5; j++)
    {
        for(i=0;i<cnt;i++);
    }
}
