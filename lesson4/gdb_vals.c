#pragma pack(push, 1)
struct str
{
	int a;//4
	char b;//1
	double c;//8
};
#pragma pack(pop)

union code
{
    int a;
    char b;
    double c;
};

int main()
{
    int x_1;
    extern int x_2;
    int a = 1024;
    char b = 'b';	//ascii "98", 0x62
    int c[4] = {1,2,3,4};
    int *d = &a;
    int **d1 = &d;
    double e = 3.14;
    char g[4] = {1,2,3,4};
    struct str f;
    f.a = 1;
    f.b = '2';
    f.c = 3;
    union code h;
    h.c = 3;
    h.b = '2';
    h.a = 1;
    return 0;
}
