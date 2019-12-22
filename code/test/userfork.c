#include "syscall.h"

int main(){
    ForkExec("test/userpage0");
    ForkExec("test/userpage1");
}
