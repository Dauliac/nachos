#ifdef CHANGED
#include "syscall.h"

void
threadator (void *arg)
{
    int x = *((int *) arg);
    PutInt (x);
    PutChar ('\n');
    ThreadExit ();
}

int
main ()
{
    int t1 = 2;
    int t2 = 3;
    int t3 = 4;
    ThreadCreate (threadator, &t1);
    ThreadCreate (threadator, &t2);
    ThreadCreate (threadator, &t3);
    ThreadExit ();
    return 0;
}
#endif
