#ifdef CHANGED
#ifndef USERTHREAD_H
#define USERTHREAD_H
#include "copyright.h"
#include "utility.h"
#include "console.h"
#include "synch.h"

struct Schmurtz
{
    int function;
    int arg;
};

extern Semaphore *semNbProcess;

extern int do_ThreadCreate (int function, int arg);
extern int do_ThreadExit ();
extern int nbProcess;
int ForkExec(const char*filename);
#endif // USERTHREAD_H
#endif // CHANGED
