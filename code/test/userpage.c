#include "syscall.h"

const int N = 10;

int main(){
    int i = 0;
    for (i; i < N; i++) {
        ForkExec("test/userpage0");
        ForkExec("test/userpage1");
    }
    while(1);
}