#include "syscall.h"
/*void print(char c, int n)
{
    int i;
#if 1
    for (i = 0; i < n; i++) {
        PutChar(c + i);
    }
    PutChar('\n');
#endif
}*/
int
main ()
{
    int c;
    (char) c = 't';

    while ((char) c != 'q')
      {
	  c = GetChar ();
	  PutChar ((char) c);
      }
    return 0;
}
