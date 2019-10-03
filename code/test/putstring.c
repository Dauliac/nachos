#include "syscall.h"
int 
main()
{
	PutString("Salut\ne");
	//PutString("Voilà une deuxième phrase\n");
	//PutString("Une dernière et je quitte le programme\n");
	Halt();
	return 0;
}
