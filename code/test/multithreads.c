#ifdef CHANGED

#include "syscall.h"
#define THREAD_NUMBER 1

void what_thread(void *arg) {
    int x = *((int *)arg);
    /* PutString("\nThread N°"); */
    PutChar(x);
    ThreadExit();
}

int main() {
    int i;
    void* args[THREAD_NUMBER];
    char c = 'd';
    char c2 = 'f';
    PutChar(c);
    /* for(i = 0; i < THREAD_NUMBER; i++) { */
    /*     args[i] = &i; */
    /* } */
    ThreadCreate(what_thread, c2);
    ThreadExit();
}

#endif
