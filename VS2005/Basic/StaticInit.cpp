#include "A.h"

class B
{
public:
    B();
};

class C
{
public:
    static B b;
};

B C::b;

B::B()
{
    A::x[1] = 2;
}

void main()
{
    A::x[3] = 3;
}
