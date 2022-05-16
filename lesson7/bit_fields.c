#include <stdio.h>
typedef struct Student_b {
	char name[20];
	int Russian : 3;
	int Literature : 3;
	int Physics : 3;
	int English : 3;
	int Science : 3;
	int Mathematics : 3;
	int History : 3;
	int Geography : 3;
	int Social_Studies : 3;
	int Chemistry : 3;
	int Biology : 3;
	int Economics : 3;
	int Art : 3;
	int IT : 3;
} St_b;

typedef struct Student {
	char name[20];
	int Russian;
	int Literature;
	int Physics;
	int English;
	int Science;
	int Mathematics;
	int History;
	int Geography;
	int Social_Studies;
	int Chemistry;
	int Biology;
	int Economics;
	int Art;
	int IT;
} St;


int main()
{
	St stud_1;
	St_b stud_2;
	stud_1.Art = 5;
	stud_2.Art = 3;
	printf("%lu\n", sizeof(stud_1));
	printf("%lu\n", sizeof(stud_2));
	return 0;
}
