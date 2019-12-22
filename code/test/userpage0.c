#include "syscall.h"

int main() {
    int i;
    int MAX = 5;
    for (i = 0; i < MAX; i++)
      {
        PutChar('a');
      }
      ThreadExit();
    return 0;
}
