#include "syscall.h"

int main() {
    int i;
    int MAX = 15;
    for (i = 0; i < MAX; i++)
      {
        PutChar('a');
      }
      ThreadExit();
}
