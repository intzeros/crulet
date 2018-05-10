#include <stdbool.h>

typedef int INT_32;

void static_p(void){
    unsigned long d;
    d = 2.0;

    short s = 1;
    d = s;
    s = d;

    bool b = s;
    b = true;

    float f = 1.0;

    double db1 = 3;

    INT_32 i = d;

    char c = 'b';

    unsigned int n = sizeof(int);
    int m = 64 * sizeof (int) / 4;
}
