#include "syscall.h"
void
print (char c, int n)
{
    int i;
#if 1
    for (i = 0; i < n; i++)
      {
      PutChar (c + i);
      }
#endif
}

int
main ()
{
    print ('a', 1);
    ThreadExit();
    //return 0;
}
