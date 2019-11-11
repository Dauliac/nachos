#ifdef CHANGED

#include "syscall.h"
// To increase threads number:
// edit UserStacksAreaSize in addspace.h
#define THREAD_NUMBER 300
#define LOOP_NUMBER 3

// Without bitmap: Print THREAD_NUMBER+LOOP_NUMBER char 'b'
// With bitmap: print THREAD_NUMBER*LOOP_NUMBER char 'b'
void threadator(void *arg) {
    int i;
    int x = *((int *)arg);
    for (i = 0; i < LOOP_NUMBER; i++) {
        PutChar('b');
    }
    ThreadExit();
}

int main() {
    int n;
    void* args[THREAD_NUMBER];
    for(n = 0; n < THREAD_NUMBER; n++) {
        args[n] = &n;
        ThreadCreate(threadator, args[n]);
    }
    ThreadExit();
    return 0;
}

#endif
