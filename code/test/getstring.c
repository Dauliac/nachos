#include "syscall.h"
int
main()
{
	int n = 10;
	char s[n];
	
	GetString(s,n);

	PutString(s);

	return 0;
}
