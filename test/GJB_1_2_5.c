#define GLOBAL

int foo(void)
{
#define LOCAL 0
    return LOCAL;
}

int bar(void)
{
    return LOCAL;
#undef LOCAL
}

#undef GLOBAL

int vaild(void)
{
#define VAILD 0
    return VAILD;
#undef VAILD
}
