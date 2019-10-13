#ifdef CHANGED
#include "copyright.h"
#include "system.h"
#include "synchconsole.h"
#include "synch.h"

static Semaphore *readAvail;
static Semaphore *writeDone;
// static Semaphore *semaphoreSynchPutChar;
// static Semaphore *semaphoreSynchGetChar;

static void ReadAvailHandler(void *arg) { (void) arg; readAvail->V(); }
static void WriteDoneHandler(void *arg) { (void) arg; writeDone->V(); }

SynchConsole::SynchConsole(const char *in, const char *out)
{
    readAvail = new Semaphore("read avail", 0);
    writeDone = new Semaphore("write done", 0);
    // semaphoreSynchPutChar = new Semaphore("SynchPutChar", 1);
    // semaphoreSynchGetChar = new Semaphore("SynchGetChar", 1);

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
    // semaphoreSynchPutChar->P();
    console->PutChar(ch);
    writeDone->P();
    // semaphoreSynchPutChar->V();
}
int SynchConsole::SynchGetChar()
{
    // semaphoreSynchGetChar->P();
    readAvail->P (); // wait for character to arrive
    int ch = (int)console->GetChar();
    // semaphoreSynchGetChar->V();
    return ch;
}
void SynchConsole::SynchPutString(const char s[])
{
    int l = strlen(s);
	int i =0;
	while((char)s[i] != '\0')
	{
		SynchPutChar(s[i]);
		i++;
	}
	
}
void SynchConsole::SynchGetString(char *s, int n)
{
	int result;
	int i =0;
	while((i<n) && (result=SynchGetChar()) && ((char)result!='\0') && ((char)result!='\n') && ((char)result!=EOF))
	{
		s[i] = (char)result;
		i++;
	}
	s[i] = '\0';
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
    return i;
}

int SynchConsole::copyStringToMachine(char *from, int to,unsigned size)
{
	unsigned i = 0;
	int res;
	while((i<size) && (from[i] != '\0') && (from[i] != '\n'))
	{
		res = (int)from[i];
		machine->WriteMem(to+i,1,res);
		i++;
	}
	machine->WriteMem(to+i,1,'\0');
	return i;
}

#endif // CHANGED
