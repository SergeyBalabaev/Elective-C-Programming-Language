#include <stdio.h>

void bin(long unsigned int k, long unsigned int size)
{
    long unsigned int i;
 
    for (i = size * 8; i > 0; --i) {
        printf("%d", (k & (1 << (i-1))) ? 1 : 0);
    }
    printf("\n");
}

struct byte_s {
	    unsigned a0: 1;
	    unsigned a1: 1;
	    unsigned a2: 1;
	    unsigned a3: 1;
	    unsigned a4: 1;
	    unsigned a5: 1;
	    unsigned a6: 1;
	    unsigned a7: 1;
	};

union code
{
    unsigned char letter;
    struct byte_s bitfield;
    
}byte;

int main()
{
	union code a;
	a.bitfield.a0 = 1;
	a.bitfield.a1 = 1;
	a.bitfield.a2 = 1;
	a.bitfield.a3 = 1;
	a.bitfield.a4 = 0;
	a.bitfield.a5 = 1;
	a.bitfield.a6 = 1;
	a.bitfield.a7 = 1;
	
	union code b;
	b.bitfield.a0 = 0;
	b.bitfield.a1 = 0;
	b.bitfield.a2 = 0;
	b.bitfield.a3 = 1;
	b.bitfield.a4 = 0;
	b.bitfield.a5 = 0;
	b.bitfield.a6 = 0;
	b.bitfield.a7 = 0;
	printf("b.letter = %d\n",b.letter);
	printf("b.letter << 1 = %d\n",b.letter << 1);
	printf("b.letter >> 1 = %d\n",b.letter >> 1);
	printf("a.letter\t\t");
	bin(a.letter, sizeof(a.letter));
	printf("b.letter\t\t");
	bin(b.letter, sizeof(b.letter));
	printf("b.letter << 1\t\t");
	bin(b.letter << 1, sizeof(b.letter));
	printf("b.letter >> 1\t\t");
	bin(b.letter >> 1, sizeof(b.letter));
	printf("~b.letter\t\t");
	bin(~b.letter, sizeof(b.letter));
	printf("b.letter & a.letter\t");
	bin(b.letter & a.letter, sizeof(b.letter));
	printf("b.letter | a.letter\t");
	bin(b.letter | a.letter, sizeof(b.letter));
	printf("b.letter ^ a.letter\t");
	bin(b.letter ^ a.letter, sizeof(b.letter));
	b.letter |= 1 << 5;
	printf("\nb.letter\t\t");
	bin(b.letter, sizeof(b.letter));
	return 0;
}
