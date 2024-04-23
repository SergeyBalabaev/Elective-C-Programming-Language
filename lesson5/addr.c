#include <unistd.h>

int main()
{
    char str[] = "Hello, world!\n";
    write(1, &str+1, 5000);
    _exit(0);
}
