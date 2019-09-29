#ifdef CHANGED
#include "copyright.h"
#include "system.h"
#include "synchconsole.h"
#include "synch.h"

static Semaphore *readAvail;
static Semaphore *writeDone;
static void ReadAvailHandler(void *arg) { (void) arg; readAvail->V(); }
static void WriteDoneHandler(void *arg) { (void) arg; writeDone->V(); }
SynchConsole::SynchConsole(const char *in, const char *out)
{
    readAvail = new Semaphore("read avail", 0);
    writeDone = new Semaphore("write done", 0);
    console = new Console (in, out, ReadAvailHandler, WriteDoneHandler, 0);
    //machine = new Machine(TRUE);
}
SynchConsole::~SynchConsole()
{
    delete console;
    delete writeDone;
    delete readAvail;
}
void SynchConsole::SynchPutChar(int ch)
{
    console->PutChar(ch);
    writeDone->P();
}
int SynchConsole::SynchGetChar()
{
    readAvail->P (); // wait for character to arrive
    return console->GetChar ();
}
void SynchConsole::SynchPutString(const char s[])
{
    int l = strlen(s);
    for(long i = 0; i < l; i++)
        SynchPutChar(s[i]);
}
void SynchConsole::SynchGetString(char *s, int n)
{
// ...
}
int SynchConsole::copyStringFromMachine(int from,char *to, unsigned size)
{
    unsigned i = 0;
	int res;
	
	while((i<size) && (machine->ReadMem(from+i,1,&res)) && ((char)res!='\0'))
	{
		to[i] = (char)res;
		i++;
	}
	
	to[i] = '\0';

	return i+2;
}

#endif // CHANGED
