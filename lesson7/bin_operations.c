#include <stdio.h>

void bin(long unsigned int k, long unsigned int size)
{
	long unsigned int i;
	for (i = size * 8; i > 0; --i) {
		printf("%d", (k & (1 << (i - 1))) ? 1 : 0);
	}
	printf("\n");
}

struct byte_s {
	unsigned a0 : 1;
	unsigned a1 : 1;
	unsigned a2 : 1;
	unsigned a3 : 1;
	unsigned a4 : 1;
	unsigned a5 : 1;
	unsigned a6 : 1;
	unsigned a7 : 1;
};

union code
{
	unsigned char letter;
	struct byte_s bitfield;
}byte;

int setbit(const int value, const int position) {
	return (value | (1 << position));
}
int unsetbit(const int value, const int position) {
	return (value & ~(1 << position));
}
int switchbit(const int value, const int position) {
	return (value ^ (1 << position));
}
int checkbit(const int value, const int position) {
	return ((value & (1 << position)) != 0);
}


int main()
{
	union code a, b;
	a.letter = 0b00000000;
	b.letter = 0b11111111;
	a.letter = setbit(a.letter, 5);
	bin(a.letter, sizeof(a.letter));
	return 0;
}
