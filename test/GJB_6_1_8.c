#include <stdbool.h>

typedef int INT_32;

void static_p(void){
    unsigned long d;
    d = 2.0;

    short s = 1;
    d = s;
    s = d;

    bool b = s;

    float f = 1.0;

    double db1 = 3;

    INT_32 i = d;
}
