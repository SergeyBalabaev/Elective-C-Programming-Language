#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

const int N = 5;

class SimpleClass {
public:
SimpleClass()
{
this->x = 0;
this->y = 0;
cout << "Hello!" << endl;
}
void GetX()
{
cout << x << endl;
}
~SimpleClass() {
cout << "Goodbye!" << endl;
}

private:
int x;
int y;
};

int main()
{
//SimpleClass* p = (SimpleClass*)malloc(sizeof(SimpleClass));
//p->GetX();
//free(p);
SimpleClass* p = new SimpleClass();
p->GetX();
delete(p);
return 0;
}
