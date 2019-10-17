#ifdef CHANGED
#include "copyright.h"
#include "system.h"
#include "userthread.h"

extern int do_ThreadCreate(int f, int arg)
{
    Thread *t = new Thread ("new thread");
    t->Yield();
}

static void startUserThread(void * schmurtz) { 

}

#endif // CHANGED
