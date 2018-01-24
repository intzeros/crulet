struct foo0 {};

union foo1 {};

struct foo2 {
    union {};
};

typedef union {} foo3;

void foo4(void)
{
    union {} foo5;
}
