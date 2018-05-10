#include <stdlib.h>

void foo(unsigned int p_1, unsigned short p_2) { }

void test(void(*pfun)(unsigned int, unsigned short)){
    pfun(1, 2);
}

int mycheck() { }

void static_p(void){
    void(*proc_pointer)(unsigned int, unsigned short) = foo;
    proc_pointer(1u, 1);

    void(*pro_ter)(unsigned int, unsigned short);
    pro_ter = foo;
    proc_pointer(1u, 1);
    test(proc_pointer);

    char * result;
    int length = 10;
    result = (char *) malloc (length);
    foo(1, 2);

    int(*p_fun)();
    p_fun = mycheck;
    int val;
    val = mycheck();
}
