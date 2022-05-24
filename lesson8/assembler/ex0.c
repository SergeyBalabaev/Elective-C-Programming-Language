#include <unistd.h>

int main()
{
	char str[] = "Hello, MIET!\n";
	write(1, str, sizeof(str) - 1);
	_exit(0);
}
