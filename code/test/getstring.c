#include "syscall.h"
int
main()
{
	int n = 100;
	char s[n];
	
	GetString(s,n);

	PutString(s);

	return 0;
}
