#include "syscall.h"
int
main ()
{
    // String lower than MAXSTRING_SIZE
    PutString ("1\n");
    // String that contain \0 and \n
    PutString ("a\nbl\0\n");
    // String bigger than MAX_STRING_SIZE
    PutString ("abcdefghijkl\n");
    return 0;
}
