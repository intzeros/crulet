#include <stdbool.h>

void static_p(void){
    int a = 6;
    a |= 2;
    a = ~a;

    unsigned int b = 6;
    a = b & 2;
    b = b >> a;

    int arr[3] = {-1, 2, 10};
    arr[0] <<= a;
    arr[0] = arr[1] << b;

    bool flag = false;
    flag = !flag;

    int options = 1;
    if(!(options & 2 & 3 & 4)){

    }
}