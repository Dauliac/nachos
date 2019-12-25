#include "syscall.h"
main()
{
    ForkExec("test/putchar");
    ForkExec("test/putchar");
    ForkExec("test/putchar");
    ForkExec("test/putchar");
    while(1);
    //return 0;
}
