#ifdef CHANGED
#include "copyright.h"
#include "system.h"
#include "userthread.h"

struct Schmurtz {
    int function;
    int arg;
} Schmurtz;

static void startUserThread(void *schmurtz) {
    DEBUG ('x', "debug schmurtz \"%d\"\n", schmurtz);

    machine->WriteRegister(4, schmurtz->arg);
    machine->WriteRegister(PCReg, schmurtz->f);

    int i;

    for (i = 0; i < NumTotalRegs; i++)
    machine->WriteRegister (i, 0);

    machine->WriteRegister(4, schmurtz->arg);
    machine->WriteRegister (PCReg, schmurtz->function);

    machine->WriteRegister (NextPCReg, machine->ReadRegister(PCReg) + 4);

    machine->WriteRegister (StackReg, currentThread->thread->numPages() * PageSize - 16);

    machine->Run();

}

extern int do_ThreadCreate(int f, int arg)
{
    struct Schmurtz* schmurtz = new struct Schmurtz;
    schmurtz->function = f;
    schmurtz->arg = arg;

    Thread *newThread = new Thread("newThread");

    newThread->Start(StartUserThread(), (void)* schmurtz);

    return 0;
}



#endif // CHANGED
