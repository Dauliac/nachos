#ifdef CHANGED
#include "syscall.h"

void f(void *arg) {
    int x = *((int *)arg);
    PutString("\nAnd the thread number is ...\n:");
    PutInt(x);
    PutString("\n");
    ThreadExit();
}
int main() {
    int n1 = 2;
    int n2 = 3;
    ThreadCreate(f, &n1);
    ThreadCreate(f, &n2);
    ThreadExit();
    return 0;
}
#endif
