#include <stdio.h>
#include "GJB_1_1_18.h"

#define static_p(x) x >= 0 ? x : -x

void test_p(void){
    unsigned int result;
    int a = 6, b = 5;
    /*...*/
    result = static_p(a - b);
    result = static_p(a) + 1;
    /*...*/
}