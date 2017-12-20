#include <stdbool.h>

void static_p(void){
    bool flag = false;
    if(flag == !1){
        /*...*/
    }

    int x = 1;
    if(flag == !x){
        /*...*/
    }
}