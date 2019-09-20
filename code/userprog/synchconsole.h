fdef CHANGED
#ifndef SYNCHCONSOLE_H
#define SYNCHCONSOLE_H
#endif // CHANGED
Notez que les sémaphores doivent être partagés entre les objets de classe SynchConsole et ceux de
classe Console. Ils doivent donc être des fonctions C et non C++, à moins d’utiliser des fonctionnalités
évoluées de C++ (SynchConsole devrait en fait être une classe fille de Console). Le fichier userprog/
synchconsole.cc doit donc avoir la structure suivante :
#ifdef CHANGED
#include
#include
#include
#include
"copyright.h"
"system.h"
"synchconsole.h"
"synch.h"
static Semaphore *readAvail;
static Semaphore *writeDone;
static void ReadAvailHandler(void *arg) { (void) arg; readAvail->V(); }
static void WriteDoneHandler(void *arg) { (void) arg; writeDone->V(); }
SynchConsole::SynchConsole(const char *in, const char *out)
{
    readAvail = new Semaphore("read avail", 0);
    writeDone = new Semaphore("write done", 0);
    console = ...
}
SynchConsole::~SynchConsole()
{
    delete console;
    delete writeDone;
    delete readAvail;
}
#include "copyright.h"
#include "utility.h"
#include "console.h"
class SynchConsole:dontcopythis {
    public:
        SynchConsole(const char *readFile, const char *writeFile);
        // initialize the hardware console device
        // ~SynchConsole();
        // // clean up console emulation
        void SynchPutChar(int ch); // Unix putchar(3S)
        int SynchGetChar(); // Unix getchar(3S)
        void SynchPutString(const char *s); // Unix fputs(3S)
        void SynchGetString(char *s, int n); // Unix fgets(3S)
    private:
        Console *console;
};
#endif // SYNCHCONSOLE_H
#endif // CHANGED
