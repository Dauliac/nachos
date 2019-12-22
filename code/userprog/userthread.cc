#ifdef CHANGED
#include "addrspace.h"
#include "copyright.h"
#include "userthread.h"
#include "system.h"
#include "synch.h"
#include "syscall.h"

//static int threadCounter = 1;
//static Semaphore *semThread = new Semaphore ("semaphore_thread_counter", 1);

static void
StartUserThread (void *schmurtz)
{
    DEBUG ('t', "come in startUserThread\n");
    struct Schmurtz *threadSchmurtz;
    threadSchmurtz = (struct Schmurtz *) schmurtz;

    DEBUG ('t', "threadSchmurtz is\"%d\"\n", threadSchmurtz);

    int i;
    for (i = 0; i < NumTotalRegs; i++)
      {
	  machine->WriteRegister (i, 0);
      }

    // initial program counter : fonction f
    machine->WriteRegister (PCReg, threadSchmurtz->function);
    DEBUG ('t', "PCReg = %d\n", machine->ReadRegister (PCReg));

    // Write argument in register 4
    machine->WriteRegister (4, threadSchmurtz->arg);

    // Add 4 padding by security
    machine->WriteRegister (NextPCReg, machine->ReadRegister (PCReg) + 4);
    DEBUG ('t', "NextPCReg = %d\n", machine->ReadRegister (NextPCReg));

    // Magic function to get free memory space
    int memAddr = currentThread->space->AllocateUserStack ();
    DEBUG ('t', "Allocate memory at: %d\n", memAddr);

    // Write new memory stack
    machine->WriteRegister (StackReg, memAddr);

    DEBUG ('t', "machine run after all threads things\n");
    // Dump memory to see threads
    machine->DumpMem ("threads.svg");
    machine->Run ();
}

extern int
do_ThreadCreate (int function, int arg)
{

    struct Schmurtz *schmurtz = new struct Schmurtz;
    schmurtz->function = function;
    schmurtz->arg = arg;

    currentThread->space->semThread->P ();
    currentThread->space->threadCounter++;
    currentThread->space->semThread->V ();

    Thread *newThread = new Thread ("Thread");

    newThread->Start (StartUserThread, (void *) schmurtz);

    return 0;
}

int
do_ThreadExit ()
{
    currentThread->space->semThread->P ();
    currentThread->space->threadCounter--;
    currentThread->space->semThread->V ();
    DEBUG ('t', "Surviving threads number:  %d\n", currentThread->space->threadCounter);

    if (currentThread->space->threadCounter > 0)
      {
	  int addr = machine->ReadRegister (StackReg);
	  DEBUG ('t', "The next addr will be unallocated:  %d\n", addr);
	  currentThread->space->UnAllocateUserStack(addr);
	  currentThread->Finish ();
      }
    else
      {
	  interrupt->Halt ();
      }
    return 0;
}

void StartForkThread(void *)
{

    currentThread->space->InitRegisters ();	// set the initial register values
    currentThread->space->RestoreState ();	// load page table register

    machine->DumpMem ("memory.svg");
    machine->Run ();		// jump to the user progam
    //Doupt
    ASSERT (FALSE);		// machine->Run never returns;
}

int ForkExec(const char*filename)
{
    OpenFile *executable = fileSystem->Open(filename);

    // Crash if invalid filename
    if (executable == NULL)
    {
        SetColor (stdout, ColorRed);
        SetBold (stdout);
        printf ("Unable to open file %s\n", filename);
        ClearColor (stdout);
        return 1;
    }
    // Create new mem space for fork
    AddrSpace *space;
    space = new AddrSpace (executable);

    // Create new thread
    Thread *fork = new Thread ("Thread fork");
    if (fork == NULL) {
        DEBUG ('t', "No way to create thread\n");
        return -1;
    }
    fork->space = space;

    //Start fork thread
    fork->Start (StartForkThread, NULL);

    currentThread->space->semThread->P ();
    currentThread->space->threadCounter++;
    currentThread->space->semThread->V ();


    delete executable;

    return currentThread->space->threadCounter;
}


#endif // CHANGED
