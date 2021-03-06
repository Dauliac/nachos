#ifdef CHANGED
#include "copyright.h"
#include "system.h"
#include "synchconsole.h"
#include "synch.h"

static Semaphore *readAvail;
static Semaphore *writeDone;

static Semaphore *semaphoreGetChar;
static Semaphore *semaphorePutChar;

static void
ReadAvailHandler (void *arg)
{
    (void) arg;
    readAvail->V ();
}

static void
WriteDoneHandler (void *arg)
{
    (void) arg;
    writeDone->V ();
}

SynchConsole::SynchConsole (const char *in, const char *out)
{
    readAvail = new Semaphore ("read avail", 0);
    writeDone = new Semaphore ("write done", 0);

    semaphorePutChar = new Semaphore ("putChar", 1);
    semaphoreGetChar = new Semaphore ("getChar", 1);

    console = new Console (in, out, ReadAvailHandler, WriteDoneHandler, 0);
}

SynchConsole::~SynchConsole ()
{
    delete console;
    delete writeDone;
    delete readAvail;
}

void
SynchConsole::SynchPutChar (int ch)
{
    semaphorePutChar->P ();
    console->PutChar (ch);
    writeDone->P ();
    semaphorePutChar->V ();
}

int
SynchConsole::SynchGetChar ()
{
    semaphoreGetChar->P ();
    readAvail->P ();		// wait for character to arrive
    int ch = (int) console->GetChar ();
    semaphoreGetChar->V ();
    return ch;
}

void
SynchConsole::SynchPutString (const char s[])
{
    int i = 0;
    while (s[i] != '\0')
      {
	  SynchPutChar (s[i]);
	  i++;
      }
}

void
SynchConsole::SynchGetString (char *s, int n)
{
    int result;
    int i = 0;
    while ((i < n) && (result = SynchGetChar ()) && ((char) result != '\0')
	   && ((char) result != '\n') && ((char) result != EOF))
      {
	  s[i] = (char) result;
	  i++;
      }
    s[i] = '\0';
}

int
SynchConsole::copyStringFromMachine (int from, char *to, unsigned size)
{
    unsigned i = 0;
    int res;
    while ((i < size) && (machine->ReadMem (from + i, 1, &res))
	   && ((char) res != '\0'))
      {
	  to[i] = (char) res;
	  i++;
      }
    to[i] = '\0';
    return i;
}

int
SynchConsole::copyStringToMachine (char *from, int to, unsigned size)
{
    unsigned i = 0;
    int res;
    while ((i < size) && (from[i] != '\0'))
      {
	  res = (int) from[i];
	  machine->WriteMem (to + i, 1, res);
	  i++;
      }
    machine->WriteMem (to + i, 1, '\0');
    return i;
}

void
SynchConsole::SynchPutInt (int n)
{
    char *result = new char[MAX_STRING_SIZE];
    snprintf (result, MAX_STRING_SIZE, "%d", n);
    SynchPutString (result);
    delete[]result;
}

#endif // CHANGED
